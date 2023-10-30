#if RELEASE
import UIKit
import DaonAuthenticatorFace
public protocol PSDaonSdkDelegate{
    
    //MARK:- FACEControllerManager
    func faceControllerStartedAnalysis(hasRequiredLivenessEvents: Bool)
    func faceControllerCapturedImage(_ image: UIImage!)
    func faceControllerProcessedFrame(withResult imageQualityPassed: Bool, imageQualityIssues qualityIssues: [NSNumber]?,isCancelling:Bool)
    func faceControllerDetectedLivenessEvent(_ event: DASFaceLivenessEvent, for image: UIImage!, allRequiredLivenessEventsDetected: Bool)
    func faceControllerCompletedSuccessfully()
    func faceControllerFailedWithError(_ error: Error)
    func isDarkModeEnabled()->Bool
    func rotateImage(_ image: UIImage, to: UIImage.Orientation) -> UIImage?
    func loadImageNamed(_ imageName: String) -> UIImage?
    func setStageReached(_ stageReached:SdkStageReached)
    func setIdxUserId(_ idxUserId : String)
    func eventAnalitycs(flow:String, event: PSDKAnalitycsEvent, error: Error?, cveDoc:String?)
    func getFlowId() -> String?
    func reset(resetFido:Bool)
    func onFidoRegistrationSuccess()
    func onFidoRegistrationFailed(_ error: Error)
    func get3DViewController(_ isRegistrationContext:Bool)
    func show3DViewController()
    func onFidoAuthenticationSuccess()
    func onFidoAuthenticationCancelled()
    func onFidoAuthenticationFailed(_ error: Error)
    func get3DViewControllerForAuth(_ isRegistrationContext:Bool)
    func show3DViewControllerForAuth()
    func getDasErrorsDict(errorCode:String)->String?
}
#endif
