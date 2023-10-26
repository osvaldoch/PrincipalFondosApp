import UIKit
import PS_FacialUI
import PS_Facial_Services
import PS_Facial_Engine

class FacialSDKManager: NSObject{
    
    
    internal var serviceLibrary: PSFacialServiceViewModel?
    
    //MARK:- solo delegados implementados en las vistas de el framework facial
    var implementedDocumentCaptureVCDelegate: ImplementedDocumentCaptureVCDelegate?
    var documentCaptureOverlayDelegate: DocumentCaptureOverlayDelegate?
    var psdkDocCaptOverlayHelperViewController: PSDKDocCaptOverlayHelperViewController?
    
    
    static var instance: FacialSDKManager = FacialSDKManager()
    
    private override init() {
        super.init()
        
        DobsLogUtils.setEnabled(true)
        
        //MARK:- Delegados de el framework de el facial engine
        PSFacialEngine.getInstance().psFacialEngineDelegate = self
        PSFacialEngine.getInstance().psFacialEngineCaptureManagerDelegate = self
        PSFacialEngine.getInstance().psFacialEnginePSFacialServicesDelegate = self
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate = self
        PSFacialEngine.getInstance().psFacialEngineDaonSDKDelegate = self
        PSFacialEngine.getInstance().psFacialEngineMainAppDelegate = self
        
        
        //MARK:- Delegadaos de el framework de el facial ui
        FacialUI2.facialUI.captureManagerDelegate = self
        FacialUI2.facialUI.psfuDocumentScanHolderVCDelegate = self
        FacialUI2.facialUI.reviewVCDelegate = self
        FacialUI2.facialUI.psWelcomeVCDelegate = self
        FacialUI2.facialUI.psfuiDocumentCaptureFirstVCDelegate = self
        FacialUI2.facialUI.psfuChooseDocsInstructionsVCDelegate = self
        FacialUI2.facialUI.psfuDocumentTutorialVCDelegate = self
        FacialUI2.facialUI.psfuDocumentCaptureOverlayVCDelegate = self
        FacialUI2.facialUI.psLoadingVCDelegate = self
        FacialUI2.facialUI.psfu3DLivenessVCDelegate = self
        FacialUI2.facialUI.psfuTutorial3DVCDelegate = self
        FacialUI2.facialUI.psfuTutorialVC4Delegate = self
        FacialUI2.facialUI.psfuTimerVCDelegate = self
        
        
        //MARK:- Delegados de el framework de facial services
        PSFacialServiceViewModel.servicesDelegate = self
        
        //MARK:- Delegado de la libreria de daon
        PSDaonSdk.instance.daonSdkDelegate = self
        serviceLibrary = PSFacialServiceViewModel()
    }
    
    internal func initialize(appName: String,
                             psfeRegistrationMode: PSFERegistrationMode = PSFERegistrationMode.ThreeDAndSelfie,
                             completion: @escaping (Error?, Bool)->(Void)) {
        PSFacialEngine.getInstance().initialize(appName: appName, psfeRegistrationMode: psfeRegistrationMode) {
            (error, hasValidKeys) in
            
            completion(error, hasValidKeys)
        }
    }
    
    public func initWithViewController(viewController: UIViewController,
                                       info: PSFEFacialInfo,
                                       facialMode: PSFUMode,
                                       showAlertError: Bool = true,
                                       closeFacialAutomatically: Bool = true,
                                       psFacialEngineAuthFlowDelegate: PSFacialEngineAuthFlowDelegate?,
                                       psFacialEngineRegistrationFlowDelegate: PSFacialEngineRegistrationFlowDelegate?){
        
        
        PSFacialEngine
            .getInstance()
            .psfeProcesarFlow
            .start(viewController: viewController,
                   psfeFacialInfo: info,
                   mode: PSFEFacialMode(rawValue: facialMode.rawValue)!,
                   showAlertError: showAlertError,
                   closeFacialAutomatically: closeFacialAutomatically,
                   psFacialEngineRegistrationFlowDelegate: psFacialEngineRegistrationFlowDelegate,
                   psFacialEngineAuthFlowDelegate: psFacialEngineAuthFlowDelegate)
        
        
        
    }
    
    //MARK:- Funcion independiente para convertir tipo de documento
    internal func getPSFUDocumentTypeDepedingOnFacialEngineDocType()-> PSFUDocumentType{
        let psfeDocumentType = PSFacialEngine.getInstance().getDocumentType()
        switch psfeDocumentType{
        case .IFE:
            return .ine_ife
        case .Pasaporte:
            return .passport
        case .MatriculaConsular:
            return .consular
        case .FM2:
            return .immigration
        case .BirthCertificate:
            return .acta
        case .AnyDoc:
            return .anyDoc
        case .none:
            return .ine_ife
        case .some(_):
            return .ine_ife
        }
    }
    
    //MARK:- Funcion independiente para convertir tipo de transicion de pantalla
    internal func psfeTransitionDirection(transitionDirection: PSFEDirection)-> TransitionOptions.Direction{
        switch transitionDirection{
        case .fade:
            return .fade
        case .toTop:
            return .toTop
        case .toBottom:
            return .toBottom
        case .toLeft:
            return .toLeft
        case .toRight:
            return .toRight
        @unknown default:
            fatalError()
        }
    }
    
    internal func allDocumentsScanned() -> Bool{
        
        if (PSFacialEngine.getInstance().psfeFacialInfo?.anyDocInfo?.separatelyDocSideScan ?? false){
            
            if (PSFacialEngine.getInstance().getFacialMode() == PSFEFacialMode.ScanADoc &&
                PSDKCapturedDocumentManager.instance.manager.front != nil) ||
                (PSFacialEngine.getInstance().getFacialMode() == PSFEFacialMode.ScanADoc &&
                 PSDKCapturedDocumentManager.instance.manager.back != nil)
                
            {
                return true
            }
        }
        
        
        let backDocumentType = PSDKCaptureManager.instance.backDocumentType
        if ((PSDKCapturedDocumentManager.instance.manager.front != nil && backDocumentType == nil) || (PSDKCapturedDocumentManager.instance.manager.front != nil  && PSDKCapturedDocumentManager.instance.manager.back != nil ))
        {
            return true
        }
        
        return false
    }
}

extension FacialSDKManager: PSFUTimerVCDelegate {
    func onTimerCompleted(vc: PS_FacialUI.TimerViewController) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnTimerCompleted()
    }
    
    func onTimerCanceled(vc: TimerViewController) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnTimerCanceled()
    }
}
