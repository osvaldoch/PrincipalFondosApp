
import Foundation
import PS_Facial_Engine
import PS_Facial_Services
import UIKit
import PS_Core

class CustomFlowEnrollByURLManager{
    
    static let shared = CustomFlowEnrollByURLManager()
    
    private init(){
        PSFacialServiceViewModel.servicesDelegate = self
    }
    
    internal func start(mode:PSFEFacialMode){
        
        switch (mode) {
            case .Register:
                self.startWithRegistrationMode()
            case .Validation:
                self.startWithAuthenticationMode()
            default:
                break
            
        }
    }
    
    private func startWithRegistrationMode(){
        PSFacialEngine
            .getInstance()
            .psfeUrlEnrollmentManager
            .setDelegates(servicesDelegate: self,
                          enventsDelegate: self,
                          uiDelegates: self)
            .startWithRegistrationMode()
    }
    
    private func startWithAuthenticationMode(){
        PSFacialEngine
            .getInstance()
            .psfeUrlEnrollmentManager
            .setDelegates(servicesDelegate: self,
                          enventsDelegate: self,
                          uiDelegates: self)
            .startWithAuthMode()
    }
    
    func getDataSelfie() -> Data{
       
        return  UIImage(named: "01")!.jpegData(compressionQuality: 0.5) ?? Data()
    }
    
    func getDataSelfieForVerifyUser() -> Data{
       
        return  UIImage(named: "a01")!.jpegData(compressionQuality: 0.5) ?? Data()
    }
    
    func getDataFront() ->Data{
        
        return  UIImage(named: "02")!.jpegData(compressionQuality: 0.5) ?? Data()
    }
    
    func getDataBack() -> Data{
        
        return  UIImage(named: "03")!.jpegData(compressionQuality: 0.5) ?? Data()
    }
}


//MARK: Engine delegates
extension CustomFlowEnrollByURLManager: PSFEURLEnrollmentManagerServicesDelegate{
   

    
    func setupServices(daonServerUrl: String, registerByUrlHostName: String, serverUser: String, serverPassword: String) {
        PSFSConfigManager
            .shared
            .setup()
            .withDaonServerUrl(daonServerUrl: daonServerUrl)
            .withUser(daonUser: serverUser)
            .withPassword(daonPassword: serverPassword)
            .withRegisterByUrlHostName(registerByUrlHostName: registerByUrlHostName)
            .build()
    }
    
    
    func giveMeUserIdxId(curp: String, completion: @escaping (String?, NSError?) -> ()) {
        let serviceLibrary = PSFacialServiceViewModel()
        
        serviceLibrary.onSuccessSearchUser = {
            (_ response: PSFSGetUserResponse) -> Void in
            
            if let id = response.items?[0].id{
                completion(id, nil)
            }
        }
        
        serviceLibrary.onServiceError = {
             (_ err: Error)  -> Void in
            
            completion(nil, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: err.localizedDescription]))
                       
        }
        serviceLibrary.perfomSearchUser(userId: curp)
    }
    
    func createIdCheckForUser(userIdxId: String, livenessPolicyName: String, idCheckReferenceId: String, completion: @escaping (String?, NSError?) -> ()) {
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        serviceLibrary.onSuccessCreateIDCheckWithLivenessPolicy = {
            (_ response: PSFSCreateIdCheckResponse) -> Void in
                completion(response.id, nil)
        }
        
        serviceLibrary.onServiceError = {
             (_ err: Error)  -> Void in
            
            completion(nil, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: err.localizedDescription]))
                       
        }
        serviceLibrary.performCreateIDCheckWithLivenessPolicy(userID: userIdxId,
                                                              livenessPolicyName: livenessPolicyName,
                                                              guid: idCheckReferenceId)
    }
    
 
    func uploadDocsToIdCheck(userIdIdx:String, idCheck: String, documents docs: [Data], capturedTime: Date, completion: @escaping (NSError?) -> ()) {
        
        var documentImages: [PSFSSDocumentImage] = []
        for (index, psfeImageDocument) in docs.enumerated() {
            var type = PSFEImageDocument.DocumentType.Front
            if (index == 1){
                type = PSFEImageDocument.DocumentType.Back
            }
            
            if let imageBase64 = UIImage(data: psfeImageDocument)?.psfeResizeImage().base64EncodedString() {
                documentImages.append(PSFSSDocumentImage(imageFormat: "JPG",
                                                        value: imageBase64,
                                                        type: type.rawValue))
            }
        }
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        serviceLibrary.onSuccessAddDocumentToTheIdCheck = { (_ frontDocument:PSFSCreateDocumentResponse) -> Void in
            completion(nil)
        }
        
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            DobsLogUtils.logError("Create documents error: " + err.localizedDescription + ", code: " + String(err._code))
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            completion(NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: err.localizedDescription]))
        }
        
        serviceLibrary.perfomAddDocumentToTheIdCheck(
            userId: userIdIdx,
            idcheckid: idCheck,
            capture: capturedTime,
            processedImageBase64: nil,
            images: documentImages)
    }
    
    func doAlreadyExistsTheBestFrame(userIdxId: String, idCheck: String, completion: @escaping (Bool, NSError?) -> ()) {
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessGetFaceLivenessResponse = {(_ response:PSFSGetFaceLivenessResponse) -> Void in
            if (response.items == nil || response.items!.count == 0){
                completion(false, nil)
            }
            else{
                completion(true, nil)
            }
        }
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            completion(false, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: err.localizedDescription]))
        }
        serviceLibrary.performGetFaceLiveness(userId: userIdxId,
                                              idCheck: idCheck)
    }
    
    func uploadBestFrameToIdCheck(userIdxId: String, idCheck: String, completion: @escaping (NSError?) -> ()) {
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessAddFaceLivenessResponse = { (_ response:PSFSCreateFaceLivenessResponse) -> Void in
            completion(nil)
        }
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            DispatchQueue.psfeMainAsync {
                //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
                if (err as NSError).code == 409{
                    completion(nil)
                    return
                }
                completion(NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: err.localizedDescription]))
            }
        }
        
        
        if let image = PSFacialEngine.getInstance().getFaceImage(){
            serviceLibrary.performAddFaceLiveness(userId: userIdxId,
                                                  idCheck: idCheck,
                                                  subtype: PSFSEvaluationUtil.checkLivenessProofVSSelfieSubtype,
                                                  capture: Date(),
                                                  imageBase64: image.psfeResizeImage().base64EncodedString())
        }
            
    }
    
    func checkDocumentsProcessed(userIdxId: String, idCheck: String, completion: @escaping (Bool, NSError?) -> ()) {
        let serviceLibrary = PSFacialServiceViewModel()
        
        serviceLibrary.onSuccessGetCheckAllDocuments = { [weak self] (_ response: PSFSGetAllDocumentsResponse) -> Void in
            
            guard self != nil else { return }
            
            PSFSDocumentsUtil.evaluateDocumentStatus(documentResponse: response) { isProcessing, error in
                if let error = error {
                    completion(isProcessing, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: error.localizedDescription]))
                }
                else {
                    completion(isProcessing, nil)
                }
                
            }
        }
        
        serviceLibrary.onServiceError = { [weak self] (_ err: Error)  -> Void in
            
            guard self != nil else { return }
            
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "",event: .Default, error: err, cveDoc: nil)
            completion(false, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: err.localizedDescription]))
        }
        serviceLibrary.perfomCheckAllProcessedDocs(userId: userIdxId, idcheckid: idCheck)
    }
    
    func executeEvaluation(userIdxId: String, idCheck: String, evaluationPolicyName: String,selectedDocumentType:String, completion: @escaping (PSFEImageResult?,NSError?) -> ()) {
        
        
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessCreateEvaluation = { (_ response:PSFSCreateEvaluationResponse, _ jsonStr: String?) -> Void in
            
            let error = PSFSEvaluationUtil.validateEvaluationResponse(response: response, selectedDocumentType: selectedDocumentType)
            
            if let error = error {
                completion(nil, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: error.localizedDescription]))
                return
            }
            
            
            //obtiene el resultado de la cara y la credencial
            let psfsImageResult = PSFSEvaluationUtil.getImageResultFromEvaluationResponse(response: response)
            //convierte el resultado de la cara y la credencial de un objeto de el framewok de los servivcio
            //a un objeto de el motor
            if let psfsImageResult = psfsImageResult {
                //convierte el resultado de servicio a resultado para motor
                let psfeImageResult = PSFEImageResult(fmr: psfsImageResult.fmr,
                                                      result: psfsImageResult.result,
                                                      score: psfsImageResult.score,
                                                      threshold: psfsImageResult.threshold)
                
                completion(psfeImageResult, nil)
             
            }
            
        }
        
        serviceLibrary.onServiceError = {(_ error:Error)  -> Void in
            completion(nil, NSError(domain: "", code: -1, userInfo: [NSLocalizedDescriptionKey: error.localizedDescription]))
        }
        serviceLibrary.perfomCreateEvaluation(userId: userIdxId,
                                              idcheckid: idCheck,
                                              evaluationPolicyName: evaluationPolicyName)
    }
    
    func beSureUserIsSignedOut(curp:String, completion: @escaping (Bool?, NSError?) -> ()) {
        RegisterByURLServiceUtil.logout(curp: curp, completion: {
            error  in

            if let error = error{
                completion(nil, error)
                return
            }
            
            completion(true, nil)
        
        })
    }
    
    func generateToken(curp:String, encryptedPassword:String, completion: @escaping (String?, NSError?) -> ()) {
        RegisterByURLServiceUtil.login(curp: curp,
                                       encryptedPassword: encryptedPassword,
                                       completion: {
            token, error  in

            if let error = error{
                completion(nil, error)
                return
            }
            
            completion(token, nil)
        
        })
    
    }
    
    func enrollUserWithSelfieAndDocs(token: String?, userData: PSFEURLEnrollmentManager.UserDataToEnrollAnUser, selfieAndDocs: [Data], completion: @escaping (NSError?) -> ()) {
        
        let req = PSEnrollWithDocsRequest()
        
        req.token = token
        
        let inp = PSEnrollWithDocsRequest.EnrollWithDocsInput()
        inp.nombre = userData.nombre
        inp.apellidoPaterno = userData.apellidoPaterno
        inp.apellidoMaterno = userData.apellidoMaterno
        inp.curp = userData.curp
        inp.cveAfore = userData.cveAfore
        inp.cveImagen = userData.cveImagen
        inp.operacion = userData.operacion
        inp.enrolar = userData.enrolar
        
        req.input = inp
        
        req.files.append(PSEnrollWithDocsRequest.Files(fileName: "01.jpg", imageData: selfieAndDocs[0]))
        req.files.append(PSEnrollWithDocsRequest.Files(fileName: "02.jpg", imageData: selfieAndDocs[1]))
        req.files.append(PSEnrollWithDocsRequest.Files(fileName: "03.jpg", imageData: selfieAndDocs[2]))
        
        RegisterByURLServiceUtil.enrollUserWithDocs(psEnrollWithDocsRequest: req) {
            error in
            
            completion(error)
            
        }
        
    }
    
    
    func verifyFacialAuthWithSelfie(token: String?, userData: PSFEURLEnrollmentManager.UserDataToVerifyAnUser, selfie: [Data], completion: @escaping (NSError?) -> ()) {
        
        let req = PSVerifyUserWithSelfieRequest()
        
        req.token = token
        
        let inp = PSVerifyUserWithSelfieRequest.VerifyWithSelfieInput()
        inp.curp = userData.curp
        inp.cveAfore = userData.cveAfore
        inp.cveImagen = userData.cveImagen
        inp.operacion = userData.operacion
        inp.enrolar = userData.enrolar
        
        req.input = inp
        
        req.files.append(PSVerifyUserWithSelfieRequest.Files(fileName: "01.jpg", imageData: selfie[0]))
        
        RegisterByURLServiceUtil.verifyUserWithSelfie(psVerfifyUserWithSelfieRequest: req) {
            error in
            
            completion(error)
            
        }
    }
    
    
}

extension CustomFlowEnrollByURLManager: PSFEURLEnrollmentManagerUIDelegate{
    func giveMeUserSelfieForAuth(completion: @escaping ([Data]) -> ()) {
        completion([getDataSelfieForVerifyUser()])
    }
    
    func shouldOpenWaitForReviewUI() {
        //TODO: open ui wait review
        print("open wait")
    }
    
    func giveMeUserSelfieAndDocs(completion: @escaping ([Data]) -> ()) {
        completion( [getDataSelfie(), getDataFront(), getDataBack()])
    }
}

extension CustomFlowEnrollByURLManager: PSFEURLEnrollmentManagerEventsDelegate{
    
    func giveMeDocumentType() -> PSFEDocumentType {
        return PSFEDocumentType.IFE
    }
    
    func giveMeUserPassword() -> String {
        return "qwertyui"
    }
    
    func giveMeUserDataToVerifyAuth() -> PSFEURLEnrollmentManager.UserDataToVerifyAnUser.UserDataToVerifyAnUserBuild {
        return PSFEURLEnrollmentManager
            .UserDataToVerifyAnUser()
            .withCurp(curp: "MIFN871010HCHRRX02")
            .withEnrrolar(enrolar: "0")
            .withOperacion(operacion: "06")
            .withCveAfore(cveAfore: "556")
            .withCveImage(cveImagen: ["01"])
            .build()!
    }
    
    func onAuthSuccess() {
        print("success authentication")
    }
    
    func onEvaluationSuccess() {
        print("facial registration OK :)")
    }
    
    func giveMeUserDataToEnrollIt() -> PSFEURLEnrollmentManager.UserDataToEnrollAnUser.UserDataToEnrollAnUserBuild {
        return PSFEURLEnrollmentManager
            .UserDataToEnrollAnUser()
            .withCurp(curp: "MIFN871010HCHRRX02")
            .withNombre(nombre: "NOE ISRAEL")
            .withApellidoPaterno(apellidoPaterno: "MIRANDA")
            .withApellidoMaterno(apellidoMaterno: "FRANCO")
            .withEnrrolar(enrolar: "1")
            .withOperacion(operacion: "06")
            .withCveAfore(cveAfore: "556")
            .withCveImage(cveImagen: ["01", "02", "03"])
            .build()!
    }
    
    func handleError(error: NSError) {
        print("error enrroll user")
    }
    
    func userEnrolledSuccess() {
        print("user enrolled ")
    }
    
}

//MARK: Services delegates
extension CustomFlowEnrollByURLManager: PSFSFacialServicesDelegate {
    func getEncyptedText(text: String) -> String {
        let encryptWithCore = PSEncryptDecript.encrypt(data: text, keyDataString: PSCore.shared.passwordComplete) ?? ""
        
        return encryptWithCore.base64EncodedString
    }
    
    func configureServices() {
        PSFSConfigManager
            .shared
            .setup()
            .withDaonServerUrl(daonServerUrl: PSFacialEngine.getInstance().getServerUrl())
            .withUser(daonUser: PSFacialEngine.getInstance().getSettingsString(.onboardingServerUsername)!)
            .withPassword(daonPassword: PSFacialEngine.getInstance().getSettingsString(.onboardingServerPassword)!)
            .build()
    }
    
    func getUserIdx() -> String {
        return ""
    }
    
    func getIdChekcs() -> String {
        return ""
    }
    
    

}
extension String {
    
    ///base64EncodedString
    var base64EncodedString:String{
        if let data = data(using: .utf8){
            return data.base64EncodedString()
        }
        return ""
    }
    
}
