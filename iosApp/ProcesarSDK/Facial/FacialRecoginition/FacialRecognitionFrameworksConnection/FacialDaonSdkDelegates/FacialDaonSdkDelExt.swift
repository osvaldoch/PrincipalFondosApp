import DaonAuthenticatorFace
import Foundation
import UIKit
import PS_Facial_Engine

extension FacialSDKManager: PSDaonSdkDelegate{
    
    func faceControllerStartedAnalysis(hasRequiredLivenessEvents: Bool) {
        PSFacialEngine
            .getInstance()
            .psfeLiveness3DManager
            .handleFaceControllerStartedAnalysis(hasRequiredLivenessEvents: hasRequiredLivenessEvents)
    }
    
    func faceControllerCapturedImage(_ image: UIImage!) {
        PSFacialEngine.getInstance().psfeLiveness3DManager.handleFaceControllerCapturedImage(image)
    }
    
    func faceControllerProcessedFrame(withResult imageQualityPassed: Bool, imageQualityIssues qualityIssues: [NSNumber]?, isCancelling:Bool) {
        PSFacialEngine.getInstance().psfeLiveness3DManager.handleFaceControllerProcessedFrame(withResult: imageQualityPassed, imageQualityIssues: qualityIssues,isCancelling:isCancelling)
    }
    
    func faceControllerDetectedLivenessEvent(_ event: DASFaceLivenessEvent, for image: UIImage!, allRequiredLivenessEventsDetected: Bool) {
        PSFacialEngine.getInstance().psfeLiveness3DManager.handleFaceControllerDetectedLivenessEvent(PSFELiveness3DManager.PSFEFaceLivenessEvent(rawValue: event.rawValue)!, for: image, allRequiredLivenessEventsDetected: allRequiredLivenessEventsDetected)
    }
    
    func faceControllerCompletedSuccessfully() {
        PSFacialEngine.getInstance().psfeLiveness3DManager.handleFaceControllerCompletedSuccessfully()
    }
    
    func faceControllerFailedWithError(_ error: Error) {
        PSDKSingleAuthenticatorContextManager.intance.completeCaptureWithErrorCode(errorCode: (error as NSError).code)
    }
    
    func isDarkModeEnabled()->Bool{
        return DASUtils.isDarkModeEnabled()
    }
    
    func rotateImage(_ image: UIImage, to: UIImage.Orientation) -> UIImage?{
        return DASUtils.rotateImage(image, to: to)
    }
    
    func loadImageNamed(_ imageName: String) -> UIImage?{
        return DASUtils.loadImageNamed(imageName)
    }
    
    func setStageReached(_ stageReached:SdkStageReached){
        PSFacialEngine.getInstance().setStageReached(PSFacialEngine.StageReached(rawValue: stageReached.rawValue)!)
    }
    
    func setIdxUserId(_ idxUserId : String){
        PSFacialEngine.getInstance().setIdxUserId(idxUserId)
    }
    
    func eventAnalitycs(flow:String, event: PSDKAnalitycsEvent, error: Error?, cveDoc:String?){
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: PSFEAnalitycsEvent(rawValue: event.rawValue)!, error: error, cveDoc: cveDoc)
    }
    func getFlowId() -> String?{
        PSFacialEngine.getInstance().getFlowId()
    }
    
    func reset(resetFido:Bool){
        PSFacialEngine.getInstance().reset(resetFido: resetFido)
    }
    
    func onFidoRegistrationSuccess(){
        PSFacialEngine.getInstance().psFacialEngineMainAppDelegate?.on3DRegistrationSuccess()
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .FacialSelfieValidation, error: nil, cveDoc: nil)
    }
    
    func onFidoRegistrationFailed(_ error: Error) {
        PSFacialEngine.getInstance().psFacialEngineMainAppDelegate?.on3DRegistrationFailed(PSFEError(error: error))
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: error, cveDoc:  nil)
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .FacialSelfieAttempt, error: nil, cveDoc: nil)
    }
    
    func get3DViewController(_ isRegistrationContext:Bool){
        get3DViewControllerForAuth(isRegistrationContext)
    }
    
    func show3DViewController(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.open3DLiveness()
    }
    
    func onFidoAuthenticationSuccess() {
        PSFacialEngine.getInstance().psFacialEngineMainAppDelegate?.onReviewSuccess()
    }
    
    func onFidoAuthenticationCancelled() {
        PSFacialEngine.getInstance().psFacialEngineMainAppDelegate?.on3DAuthCancelled()
    }
    
    func onFidoAuthenticationFailed(_ error: Error) {
        PSFacialEngine.getInstance().psFacialEngineMainAppDelegate?.on3DAuthFailed(PSFEError(error: error))
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
    }
    
    func get3DViewControllerForAuth(_ isRegistrationContext:Bool){
        PSFacialEngine
            .getInstance()
            .psFacialEnginePSFacialUIDelegate?
            .onRegistrationContext(isRegistrationContext: isRegistrationContext)
        PSFacialEngine.getInstance().psfeLiveness3DManager.isRegistrationContext = isRegistrationContext
    }
    
    func show3DViewControllerForAuth() {
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.open3DLiveness()
    }
    
    func getDasErrorsDict(errorCode:String)->String?{
        PSFacialEngine.getInstance().getDasErrorsDict(errorCode: errorCode)
    }
    
  
    
}


