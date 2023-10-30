#if RELEASE
//
//  MyCustomFlow.swift
//  FacialEngineSample
//
//  Created by Administrador on 06/05/21.
//  Copyright © 2021 Daon. All rights reserved.
//

import Foundation
import UIKit
import AVFoundation
import LocalAuthentication
import PS_Facial_Engine
import PS_FacialUI


class MyCustomFlowManager: PSFEProcesarFlowManager {
    override public func start(viewController: UIViewController,
                               psfeFacialInfo: PSFEFacialInfo?,
                               mode: PSFEFacialMode,
                               showAlertError: Bool = true,
                               closeFacialAutomatically: Bool = true,
                               psFacialEngineRegistrationFlowDelegate: PSFacialEngineRegistrationFlowDelegate? = nil,
                               psFacialEngineAuthFlowDelegate: PSFacialEngineAuthFlowDelegate? = nil
    ){
        
        self.viewController = viewController
        self.showErrorAlert = showAlertError
        self.closeFacialAutomatically = closeFacialAutomatically
        self.psFacialEngineRegistrationFlowDelegate = psFacialEngineRegistrationFlowDelegate
        self.psFacialEngineAuthFlowDelegate = psFacialEngineAuthFlowDelegate
        
        self.psfeFacialInfo = psfeFacialInfo
        self.facialMode = mode
        self.setupEngine(facialMode: self.facialMode!)
        
        self.startUI()
        
    }
    
    private func startFlowDependingOnMode(mode: PSFEFacialMode){
        
        validationsBeforeFlow { (error) -> (Void) in
            
            guard error == nil else {
                self.finishFlowWithValidationError(error: error)
                return
            }
            
            switch (mode) {
            case .Minor,.ScanADoc, .ScanDocWithTutorial:
                PSFacialEngine.getInstance().documentsFlow.startDocumentsFlow(transitionDirection: .toRight)
            case .Recapture, .Register, .Enroll:
                if mode == .Recapture || mode == .Enroll {
                    PSFacialEngine.getInstance().setStageReached(PSFacialEngine.StageReached.tutorial)
                }
                PSFacialEngine
                    .getInstance()
                    .psFacialEnginePSFacialUIDelegate?
                    .openWelcomeScreen(transitionDirection: PSFEDirection.toRight)
            case .Validation:
                self.start3DLiveness(threeDViewController: self.get3DViewController())
            case .ShowCarousel:
                self.showCarousel()
            case .Timer:
                self.openTimer()
            @unknown default:
                print("fatal error")
            }
            
        }
        
    }
    
    private func startUI(){
        
        
        if let scanDocScreenSize = PSFacialEngine.getInstance().psfeFacialInfo?.scanDocumentScreenSize {
            
            FacialUIExecute.shared.psfuScanDocumentScreenSize = PSFUScanDocumentScreenSize(rawValue: scanDocScreenSize.rawValue) ?? .Normal
        }
        
        if let customScanningFrontText = PSFacialEngine.getInstance().psfeFacialInfo?.customTextScannigFront {
            FacialUIExecute.shared.psfuCustomTextScanningFront = customScanningFrontText
        }
        
        if let customScanningBackText = PSFacialEngine.getInstance().psfeFacialInfo?.customTextScanningBack {
            FacialUIExecute.shared.psfuCustomTextScanningBack = customScanningBackText
        }
        
        if let customTextDocumentScannedFront = PSFacialEngine.getInstance().psfeFacialInfo?.customTextDocumentScannedFront {
            FacialUIExecute.shared.psfuCustomTextDocumentScannedFront = customTextDocumentScannedFront
        }
        
        if let customTextDocumentScannedBack = PSFacialEngine.getInstance().psfeFacialInfo?.customTextDocumentScannedBack {
            FacialUIExecute.shared.psfuCustomTextDocumentScannedBack = customTextDocumentScannedBack
        }
        
        if (self.facialMode == PSFEFacialMode.ScanADoc){
            FacialUIExecute.shared.documentType = FacialSDKManager.instance.getPSFUDocumentTypeDepedingOnFacialEngineDocType()
        }
        let genre = PSFacialEngine.getInstance().getGenre(curp: self.psfeFacialInfo.userId)
        
        if let mode = PSFUMode(rawValue: facialMode.rawValue),
           let registerMode = PSFURegistrationMode(rawValue: PSFacialEngine.getInstance().getRegistrationMode()?.rawValue ?? ""),
           let gender = PSFUGenreType(rawValue: genre.rawValue){
            
            if (self.viewController.navigationController != nil){
                startUIWhitNavigationControllerSupport(mode: mode, psfuRegistrationMode: registerMode, gender: gender)
            }
            else{
                startUIWhitoutNavigationControllerSupport(mode: mode, psfuRegistrationMode: registerMode, gender: gender)
            }
        }
    }
    
    private func startUIWhitNavigationControllerSupport(mode: PSFUMode, psfuRegistrationMode: PSFURegistrationMode, gender: PSFUGenreType){
        
        var startFlow = PSFUFlow.Loading
        if (mode == .ScanDoc){
            startFlow = PSFUFlow.DocumentCameraScanner
        }
        
        FacialUIExecute.shared.show(self: viewController.navigationController! ,
                                    flow: startFlow,
                                    mode: mode,
                                    registrationMode: psfuRegistrationMode,
                                    genreType: gender,
                                    psfuAnyDocInfo: getPSFUAnyDocInfoFromFacialEngine(),
                                    animated: true) {
            
            if (mode != .ScanDoc){
                self.startFlowDependingOnMode(mode: self.facialMode)
            }
            
        }
    }
    
    private func startUIWhitoutNavigationControllerSupport(mode: PSFUMode, psfuRegistrationMode: PSFURegistrationMode, gender: PSFUGenreType){
        
        var startFlow = PSFUFlow.Loading
        if (mode == .ScanDoc){
            startFlow = PSFUFlow.DocumentCameraScanner
        }
        
        FacialUIExecute.shared.show(self: self.viewController ,
                                    flow: startFlow,
                                    mode: mode,
                                    registrationMode: psfuRegistrationMode,
                                    genreType: gender,
                                    psfuAnyDocInfo: getPSFUAnyDocInfoFromFacialEngine(),
                                    animated: false) {
            
            if (mode != .ScanDoc){
                self.startFlowDependingOnMode(mode: self.facialMode)
            }
        }
    }
    
    private func getPSFUAnyDocInfoFromFacialEngine() -> PSFUAnyDocInfo{
        let psfeAnyDocInfo = PSFacialEngine.getInstance().psfeFacialInfo?.anyDocInfo
        
        return PSFUAnyDocInfo(anyDocImageResource: psfeAnyDocInfo?.anyDocImageResource,
                              tutorialTitle: psfeAnyDocInfo?.tutorialTitle,
                              titleForCaptureDoc: psfeAnyDocInfo?.titleForCaptureDoc,
                              messageAfterCapture: psfeAnyDocInfo?.messageAfterCapture,
                              scanningDescriptionText: psfeAnyDocInfo?.scanningDescriptionText,
                              couldNotScanDocTxt: psfeAnyDocInfo?.couldNotScanDocText)
    }
    
    
    private func finishFlowWithValidationError(error: PSFEError?){
        PSFacialEngine.getInstance()
            .psFacialEnginePSFacialUIDelegate?
            .showErrorCancel(error: error!.nsError,
                             completion: { (tag, str) in
                
                //en validacion no se muestra la alerta de el lado de el sdk
                if (self.facialMode == .Validation){
                    
                    let selfie = PSFacialEngine.getInstance().getFaceImage()
                    
                    if self.closeFacialAutomatically {
                        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                            self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: error)
                        })
                    }
                    else {
                        self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: error)
                    }
                    
                }else{
                    
                    //en registro, menor o recaptura se muestra la alerta de el lado de el sdk y despues se cierra
                    if self.closeFacialAutomatically {
                        PSFacialEngine
                            .getInstance()
                            .psFacialEnginePSFacialUIDelegate?
                            .closeUI()
                    }
                   
                    self.psFacialEngineRegistrationFlowDelegate?
                        .onRegistrarionFlowFinished(capturedImagesBase64: [],
                                                    documentType: nil,
                                                    psfeImageResult: nil,
                                                    error: error)
                }
                
                //tag 2 Boton aceptar, se envia a configuracion de la camara
                if tag == 2{
                    guard let url = URL(string: UIApplication.openSettingsURLString) else {
                        return
                    }
                    UIApplication.shared.open(url, options: [:], completionHandler: nil)
                }
            })
    }
    
    private func get3DViewController() -> PSFU3DLivenessViewController{
        return FacialUIExecute.shared.getPSFU3DLivenessVC()
    }
    
    private func showCarousel(){
        FacialUIExecute.shared.showCarousel()
    }
    
    private func openTimer(){
        FacialUIExecute.shared.openTimer()
    }
    
    override public func handleWelcomeContinue(skipTutorial:Bool){
        handleCurrentStepReached(skipTutorial:skipTutorial)
    }
    
    
    //registro, recaptura
    override public func handleCurrentStepReached(skipTutorial:Bool){
        switch PSFacialEngine.getInstance().getStageReached()
        {
        case .fidoRegistrationComplete:
            DobsLogUtils.logDebug("FIDO registration already completed, proceed straight to document check")
            PSFacialEngine.getInstance().documentsFlow.startDocumentsFlow(transitionDirection: .toRight)
            
        case .documentRegistrationComplete:
            DobsLogUtils.logDebug("Liveness capture already completed, proceed straight to review")
            PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openReview()
            
        default:
            if skipTutorial{
                DobsLogUtils.logDebug("Start step")
                handleRegistrationOrRecaptureMode()
            }else{
                PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openMainTutorial()
            }
        }
    }
    
    override public func handleRegistrationOrRecaptureMode(){
        
        self.setupEngine(facialMode: self.facialMode!)
        
        //si es registro y la evaluacion no esta completa ni fallida y si no tenemos la selfie guardad en el motor
        if PSFacialEngine.getInstance().getFacialMode()! == .Register &&
            PSFacialEngine.getInstance().getFaceImage() != nil &&
            (PSFacialEngine.getInstance().getStageReached() != .evaluationComplete &&
             PSFacialEngine.getInstance().getStageReached() != .evaluationCheckFailed){
        
            openTimerView()
            
            return
        }
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openLoading()
        //borrar al usuario de fido y si lo encuentra tambien lo borra de la consola de daon
        PSFacialEngine.getInstance().psFacialEngineDaonSDKDelegate?.removeFidoAuthenticatorAndDeleteUserIfNeeded(userId: PSFacialEngine.getInstance().getUserId()) {
            
            (userFound, userDeleted, error) -> (Void) in
            
            guard error == nil else {
                print("Error al reiniciar fido y borrar el usuaro de identity x")
                if self.showErrorAlert {
                    PSFacialEngine
                        .getInstance()
                        .psFacialEnginePSFacialUIDelegate?
                        .showError(error: error!.nsError, completion: { (i, str) in
                            self.restartRegistrationOrRecaptureFlow()
                            self.psFacialEngineRegistrationFlowDelegate?
                                .onRegistrarionFlowFinished(capturedImagesBase64: [],
                                                            documentType: nil,
                                                            psfeImageResult: nil,
                                                            error: error)
                        })
                }
                else {
                    if self.closeFacialAutomatically {
                        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                            //notifica a la app que ocurrio un error
                            self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: error)
                        })
                    }
                    else {
                        //notifica a la app que ocurrio un error
                        self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: error)
                    }
                   
                }
                return
            }
            
            self.setupEngine(facialMode: self.facialMode!)
            
            self.openTimerView()
            
        }
        
    }
    
    override public func restartRegistrationOrRecaptureFlow(){
        //se reiniciliza el viewcontroller de el 3d para que sea uno nuevo
        
        self.startFlowDependingOnMode(mode: self.facialMode)
    }
    
    override public func openTimerView() {
        FacialUIExecute.shared.setFlow(flow: .Timer)
    }
    
    override public func handleOnTimerCompleted() {
        start3DLiveness(
            threeDViewController: get3DViewController())
    }
    
    override public func handleOnTimerCanceled() {
        FacialUIExecute.shared.setFlow(flow: .Welcome)
    }
    
    override public func start3DLiveness(threeDViewController: UIViewController, forceRegister: Bool = false){
        
        PSFacialEngine
            .getInstance()
            .psfeLiveness3DManager
            .start3DLiveness(threeDViewController: threeDViewController,
                             userId: self.psfeFacialInfo!.userId,
                             firstName: self.psfeFacialInfo!.firstName,
                             lastName: self.psfeFacialInfo!.lastName ,
                             forceRegister: forceRegister) {
                error in
                
                if let error = error {
                    self.handleOn3DError(error: error)
                }
            }
        
    }
    
    override public func validationsBeforeFlow(completion: @escaping  (_ error:PSFEError?)->(Void)){
        
        //checa si tiene activo el passcode
        if (!LAContext().canEvaluatePolicy(.deviceOwnerAuthentication, error: nil)){
            completion(PSFEError(errorType: .NoPasscodeEnabled))
            return
        }
        
        AVCaptureDevice.requestAccess(for: AVMediaType.video) {(granted) in
            DispatchQueue.psfeMainAsync {
                if (!granted){
                    print("Camera Access Permission Denied. Face capture will not work properly.")
                    completion(PSFEError(errorType: .LivenessCouldNotStartCamera))
                }else{
                    completion(nil)
                }
            }
        }
        
    }
    
    override public func handleOn3DSuccess() {
        switch PSFacialEngine.getInstance().getFacialMode()! {
        case .Validation:
            
            let selfie = PSFacialEngine.getInstance().getFaceImage()
            
            if self.closeFacialAutomatically {
                PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                    self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: nil)
                })
            }
            else {
                self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: nil)
            }
           
        case .Recapture, .Register, .Enroll:
            PSFacialEngine.getInstance().setStageReached(.fidoRegistrationComplete)
            //viewController!.startDocumentCheckStep()
            if (PSFacialEngine.getInstance().getFacialMode() == .Enroll){
                onEnrollSuccess()
            }
            else {
                PSFacialEngine.getInstance().documentsFlow.startDocumentsFlow(transitionDirection: .toRight)
            }
            
        default:
            print("Unexpected handleOn3DSuccess switch value")
            break
            
        }
    }
    
    func onEnrollSuccess(){ 
        
        func notify(){
         
            let selfie = getSelfieBase64()
            guard selfie.error == nil else {
                return
            }
            self.psFacialEngineRegistrationFlowDelegate?
                .onRegistrarionFlowFinished(capturedImagesBase64: [selfie.selfie],
                                                documentType:nil,
                                                psfeImageResult: PSFacialEngine.getInstance().getImageResult(),
                                                error: nil)
            
        }
        if self.closeFacialAutomatically {
            PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                notify()
            })
        }
        else{
            notify()
        }
        
    }
    
    override public func handleOn3DError(error: Error){
        switch PSFacialEngine.getInstance().getFacialMode()! {
        case .Validation:
            if (PSFEError(error: error).nsError.code == 5 ||
                PSFEError(error: error).nsError.code == 272 ){
                self.start3DLiveness(threeDViewController: self.get3DViewController(), forceRegister: true)
                return
            }
            
            
            let selfie = PSFacialEngine.getInstance().getFaceImage()
            
            if showErrorAlert {
                PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.showError(error: error, completion: { (tag, str) in
                    if self.closeFacialAutomatically {
                        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                            self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: PSFEError(error: error))
                        })
                    }
                    else {
                        self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: PSFEError(error: error))
                    }
                })
            }
            else {
                if self.closeFacialAutomatically {
                    PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                        self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: PSFEError(error: error))
                    })
                }
                else {
                    self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: PSFEError(error: error))
                }
            }
            
        case .Recapture, .Register, .Enroll:
            if showErrorAlert {
                PSFacialEngine
                    .getInstance()
                    .psFacialEnginePSFacialUIDelegate?
                    .showError(error: error, completion: { (tag, str) in
                        //vuevle a empezar
                        self.restartRegistrationOrRecaptureFlow()
                    })
            }
            else {
                if self.closeFacialAutomatically {
                    PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                        //notifica a la app que ocurrio un error
                        self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
                    })
                }
                else {
                    self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
                }
               
            }
        default:
            break
        }
        
        //self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
    }
    override public func handleOn3DAuthCancelled(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
            print("completioncloseui")
        })
    }
    
    override public func handleOnDocumentsCapturedSuccess(){
        if (facialMode == .Minor || facialMode == .ScanADoc || facialMode == .ScanDocWithTutorial){
            
            func notify(){
                
                    var docImages: [String] = []
                    if let front = PSFacialEngine.getInstance().getDocumentImage() {
                        if let frontDocBase64 = PSFacialEngine
                            .getInstance()
                            .psFacialEngineDelegate?
                            .dmdsUtilitiesEncodeBase64Jpeg(image: front,
                                                           imageQuality: PSFacialEngine.getInstance().getDocumentImageQuality()){
                            docImages.append(frontDocBase64)
                        }
                    }
                    
                    if let back = PSFacialEngine.getInstance().getDocumentImageBack() {
                        if let backDocBase64 = PSFacialEngine
                            .getInstance()
                            .psFacialEngineDelegate?
                            .dmdsUtilitiesEncodeBase64Jpeg(image: back,
                                                           imageQuality: PSFacialEngine.getInstance().getDocumentImageQuality()){
                            docImages.append(backDocBase64)
                        }
                    }
                    
                    self.psFacialEngineRegistrationFlowDelegate?
                        .onRegistrarionFlowFinished(capturedImagesBase64: docImages, documentType:PSFacialEngine.getInstance().getDocumentType()!,
                                                    psfeImageResult: nil,
                                                    error: nil)
                
            }
            if self.closeFacialAutomatically {
                
                PSFacialEngine
                    .getInstance()
                    .psFacialEnginePSFacialUIDelegate?
                    .closeUI(completion: {
                        notify()
                    })
            }
            else {
                notify()
            }
        }
        else{
            
            PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openReview()
        }
        
    }
    override public func handleOnDocumentsError(_ error: Error){
        if showErrorAlert {
            PSFacialEngine
                .getInstance()
                .psFacialEnginePSFacialUIDelegate?
                .showError(error: PSFEError.init(error: error).nsError, completion: { (tag, str) in
                    //vuevle a empezar
                    self.restartRegistrationOrRecaptureFlow()
                    //notifica a la app que ocurrio un error
                    self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
                })
        }
        else {
            if self.closeFacialAutomatically {
                PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                    //notifica a la app que ocurrio un error
                    self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
                })
            }
            else {
                self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
            }
          
        }
        
    }
    
    override public func handleOnRandomLivenessError(error:PSFEError){
        if showErrorAlert {
            PSFacialEngine
                .getInstance()
                .psFacialEnginePSFacialUIDelegate?
                .showError(error: error.nsError, completion: { (tag, str) in
                    
                    //vuevle a empezar
                    self.restartRegistrationOrRecaptureFlow()
                    
                })
        }
        else {
            if self.closeFacialAutomatically {
                PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                    //notifica a la app que ocurrio un error
                    self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: error)
                })
            }
            else {
                //notifica a la app que ocurrio un error
                self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: error)
            }
            
        }
        
    }
    
    override public func handleOnRandomLivenessSucces(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openReview()
    }
    
    override public func handleOnTimer(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openTimer()
    }
    
    override public func handleOnReviewSuccess(){
        var faceImageData: String? = nil

        
        func notify(){
            
                
                if (PSFacialEngine.getInstance().getFacialMode()! != .Validation), let faceImage = PSFacialEngine.getInstance().getFaceImage(){
                    
                    faceImageData = faceImage.psfeResizeImage().base64EncodedString()
                    
                    let documentData = getDocumentsPhotos()
                    guard documentData.error == nil else {
                        return
                    }
                    self.psFacialEngineRegistrationFlowDelegate?
                        .onRegistrarionFlowFinished(capturedImagesBase64: [faceImageData,
                                                                           documentData.front,
                                                                           documentData.back],
                                                    documentType:documentData.type,
                                                    psfeImageResult: PSFacialEngine.getInstance().getImageResult(),
                                                    error: nil)
                }else{
                    // si es validation
                    
                    let selfie = PSFacialEngine.getInstance().getFaceImage()
                    self.psFacialEngineAuthFlowDelegate?.onAuthenticationFlowFinished(selfie, error: nil)
                }
            
        }
        if self.closeFacialAutomatically {
            PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                notify()
            })
        }
        else {
            notify()
        }
        
    }
    
    override public func handleOnReviewError(_ error: Error){
        if showErrorAlert {
            PSFacialEngine
                .getInstance()
                .psFacialEnginePSFacialUIDelegate?
                .showError(error: PSFEError(error: error).nsError, completion: { (tag, str) in
                    //vuevle a empezar
                    self.restartRegistrationOrRecaptureFlow()
                    //notifica a la app que ocurrio un error
                    self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
                })
        }
        else {
            if self.closeFacialAutomatically {
                PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.closeUI(completion: {
                    //notifica a la app que ocurrio un error
                    self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
                })
            }
            else {
                //notifica a la app que ocurrio un error
                self.psFacialEngineRegistrationFlowDelegate?.onRegistrarionFlowFinished(capturedImagesBase64: [], documentType: nil, psfeImageResult: nil, error: PSFEError(error: error))
            }
            
            
        }
        
    }
    
    override public func handleOn3DTutorialContinue(){
        if (facialMode == .Validation){
            
            self.startFlowDependingOnMode(mode: self.facialMode)
        }
        else{
            self.start3DLiveness(threeDViewController: get3DViewController())
        }
    }
    
    override public func handleFinishMainTutorial(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .ContinueMainTutorial, error: nil, cveDoc: nil)
        handleCurrentStepReached(skipTutorial:true)
    }
    
    override public func handleCaptureDocsTutorial1ContinueBtnEvent(transitionDirection: PSFEDirection){
        
        let transitionDirection = FacialSDKManager.instance.psfeTransitionDirection(transitionDirection: transitionDirection)
        
        if (PSFacialEngine.getInstance().getFacialMode() == .ScanDocWithTutorial){
            FacialUIExecute.shared.documentType = getPsfuDocumentType()
        }
        
        FacialUIExecute.shared.setFlow(flow: .ChooseDocsInstructions, transitionDirection: transitionDirection)
        
    }
    
    func getPsfuDocumentType() -> PSFUDocumentType {
        switch (PSFacialEngine.getInstance().getDocumentType()){
        case .IFE:
            return PSFUDocumentType.ine_ife
        case .BirthCertificate:
            return .acta
        case .FM2:
            return .immigration
        case .MatriculaConsular:
            return .consular
        case .Pasaporte:
            return .passport
        case .AnyDoc:
            return .anyDoc
        default:
            return .ine_ife
        }
    }
    
    override func handleOnWelcomeBackButtonPressed(){
        if PSFacialEngine.getInstance().getFacialMode() == .Enroll ||
            PSFacialEngine.getInstance().getFacialMode() == .Register {
            notifiyUserCancelError()
        }
    }
    
    override func handleOnDocumentsTutorialBackButtonPressed(){
        if PSFacialEngine.getInstance().getFacialMode() == .ScanDocWithTutorial {
            notifiyUserCancelError()
        }
    }
    
    override func handleOnDocumentsCancelButtonPressed(){
        if PSFacialEngine.getInstance().getFacialMode() == .ScanADoc {
            notifiyUserCancelError()
        }
    }
    
    override func handleOnDocumentScannedFromUI() {
        
        let selfie = getSelfieBase64()
        let documentPhotos = getDocumentsPhotos()
        guard documentPhotos.error == nil, selfie.error == nil else {
            return
        }
        
        self.psFacialEngineRegistrationFlowDelegate?.onDocumentCaptured(capturedImagesBase64: [selfie.selfie,
                                                                                               documentPhotos.front,
                                                                                               documentPhotos.back], documentType: documentPhotos.type)
    }
    
    
    private func getSelfieBase64() -> (selfie: String?, error: Error?) {
        guard let faceImage = PSFacialEngine.getInstance().getFaceImage() else {
            return (selfie: nil, error: NSError(domain: "", code: 0))
        }
        return (selfie: faceImage.psfeResizeImage().base64EncodedString(), error: nil)
    }
    
    private func getDocumentsPhotos() -> (front: String?,
                                          back: String?,
                                          type: PSFEDocumentType?,
                                          error: Error?){
        
        var documentBackData: String? = nil
        
        guard let documentFrontData = PSFacialEngine.getInstance().getDocumentImage()?.psfeResizeImage().base64EncodedString() else {
            return (nil, nil, nil, NSError(domain: "", code: 0))
        }
        
        if (PSFacialEngine.getInstance().getDocumentType() != .Pasaporte && PSFacialEngine.getInstance().getDocumentType() != .BirthCertificate){
            
            guard let guardDocumentBackData = PSFacialEngine
                .getInstance()
                .getDocumentImageBack()?
                .psfeResizeImage()
                .base64EncodedString() else {
                return (nil, nil, nil, NSError(domain: "", code: 0))
            }
            documentBackData = guardDocumentBackData
        }
        
        return (documentFrontData,
                documentBackData,
                PSFacialEngine.getInstance().getDocumentType()!,
                nil)
    }
    
}
#endif
