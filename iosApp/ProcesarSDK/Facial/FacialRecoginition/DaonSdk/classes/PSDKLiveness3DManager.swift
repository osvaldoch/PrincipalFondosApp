#if RELEASE
import DaonAuthenticatorFace
import DaonAuthenticatorSDK
import DaonCryptoSDK
import DaonFaceSDK

import Foundation
import PS_FacialUI
import PS_Facial_Engine
import DaonFaceLiveness



class PSDKLiveness3DManager:NSObject, DASFaceControllerDelegate {
    
    weak var faceController: DASFaceControllerProtocol?
    public static var instance: PSDKLiveness3DManager = PSDKLiveness3DManager()
    var fidoSdk:Fido?
    var threeDViewController:UIViewController?
    var mutableIssues: [NSNumber]? = nil
    var hasIssues = true

    private override init(){
        print("init")
    }

    func configureFaceController(withPreviewView: UIView, context: DASAuthenticatorContext?){

        faceController = DASFaceAuthenticatorFactory.createFaceController(context:context,
                                                                          preview:withPreviewView,
                                                                          delegate:self)
        
    }

    public func isReadyFor3D() -> Bool{

//        if let requiredLivenessEvents = PSDKLiveness3DManager.instance.faceController?.requiredLivenessEvents()
//        {
//
//            return requiredLivenessEvents.contains(NSNumber(value:DASFaceLivenessEvent.threeDFaceCompleted.rawValue))
//        }
//
//        return false
        
        return true

    }

    public func startRegistration3DLiveness(
                         threeDViewController: UIViewController,
                         userId: String,
                         firstName: String,
                         lastName: String){
        self.threeDViewController = threeDViewController
        PSFacialEngine.getInstance().setStageReached(PSFacialEngine.StageReached.userIdEntered)
        let applicationId   = PSFacialEngine.getInstance().getSettingsString(.fidoApplicationId)!
        let policyId        = PSFacialEngine.getInstance().getSettingsString(.fidoRegistrationPolicyName)!
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openLoading()
        let regTask = FidoRegistrationTask(userId: userId,
                                           firstName : firstName,
                                           lastName : lastName,
                                           applicationId: applicationId,
                                           policyId: policyId,
                                           delegate: self){
                                                (context) -> (UIViewController) in
                                                return threeDViewController
                                           }
        regTask.start()
    }

    func startAuth3DLiveness(
                             threeDViewController: UIViewController,
                             userId: String){

        self.threeDViewController = threeDViewController

        let applicationId = PSFacialEngine.getInstance().getSettingsString(.fidoApplicationId)!
        let policyId = PSFacialEngine.getInstance().getSettingsString(.fidoRegistrationPolicyName)!
        PSFacialEngine.getInstance().psFacialEnginePSFacialUIDelegate?.openLoading()

        let formatter = DateFormatter()
        formatter.dateFormat = "yyyy-MM-dd HH:mm:ss"
        let dateString = formatter.string(from: Date())

        let authTask = FidoAuthenticationTask(userId: userId,
        applicationId: applicationId,
        policyId: policyId,
        description: userId + " login " + dateString,
        delegate: self)

        authTask.start()
    }

    public func cancel(){
        faceController?.cancel()
        faceController = nil
    }

    //MARK:- DASFaceControllerWrapperDelegate
    func faceControllerStartedAnalysis() {

        let requiredLivenessEvents = true //(faceController?.requiredLivenessEvents() != nil && faceController!.requiredLivenessEvents()!.count > 0)

        PSDaonSdk.instance.daonSdkDelegate?.faceControllerStartedAnalysis(
            hasRequiredLivenessEvents: requiredLivenessEvents
        )
    }

    func faceControllerCapturedImage(_ image: UIImage!) {

        PSDaonSdk.instance.daonSdkDelegate?.faceControllerCapturedImage(image)
    }

//    func faceControllerProcessedFrame(withResult imageQualityPassed: Bool, imageQualityIssues qualityIssues: [NSNumber]?) {
//
//       // PSDaonSdk.instance.daonSdkDelegate?.faceControllerProcessedFrame(withResult: imageQualityPassed, imageQualityIssues: qualityIssues, isCancelling: false)
//    }
    
    func controllerDidAnalyze(result: DFSResult, quality: Bool, issues: [NSNumber]?) {
        PSDaonSdk.instance.daonSdkDelegate?.faceControllerProcessedFrame(withResult: quality,
                                                                         imageQualityIssues: issues,
                                                                         isCancelling: false)
    }
    
    func controllerDidDetectLiveness(event: DASFaceLivenessEvent, result: DFSResult, image: UIImage?, allEventsDetected: Bool) {
        PSDaonSdk.instance.daonSdkDelegate?.faceControllerDetectedLivenessEvent(event,
                                                                                for: image,
                                                                                allRequiredLivenessEventsDetected: allEventsDetected)
    }
    
    
    func controllerDidCompleteSuccessfully() {
        PSDaonSdk.instance.daonSdkDelegate?.faceControllerCompletedSuccessfully()
    }
    
    func controllerDidFail(error: Error?, score: NSNumber?) {
        PSDaonSdk.instance.daonSdkDelegate?.faceControllerFailedWithError(error ?? NSError())
    }
    
    func controllerShouldUse(configuration: [AnyHashable : Any]) -> [AnyHashable : Any]? {
        //https://developer.identityx-cloud.com/client/face/ios/analyzers/quality/
        //https://developer.identityx-cloud.com/client/face/ios/analyzers/liveness-passive/#configuration
        return [kDFSConfigLivenessEyesOpenDetectionKey: true,
              kDFSConfigQualityThresholdEyeDistanceKey: 120]
    }
    
    func controllerShouldUseQualityCriteria(result: DFSResult) -> [NSNumber]? {
        var issues: [NSNumber] = []



        if !result.quality.hasAcceptableEyeDistance {
            issues.append(NSNumber(value: DASAuthenticatorError.faceLivenessAlertFaceNotCentered.rawValue))
        }
        return issues
    }

    public func getFidoSdk() -> Fido?{
        return fidoSdk
    }

    public func setFidoSdk(_ fidoSdk : Fido){
        self.fidoSdk = fidoSdk
    }
}

//MARK:- FidoRegistrationTaskDelegate

extension PSDKLiveness3DManager: FidoRegistrationTaskDelegate {
    func onFidoStartRegistration() {
        print("onFidoStartRegistration")
    }

    func onFidoRegistrationSuccess() {
        PSDaonSdk.instance.daonSdkDelegate?.onFidoRegistrationSuccess()
    }

    func onFidoRegistrationFailed(_ error: Error) {
        PSDaonSdk.instance.daonSdkDelegate?.onFidoRegistrationFailed(error)
    }

    func get3DViewController(_ isRegistrationContext:Bool) -> UIViewController {
        PSDaonSdk.instance.daonSdkDelegate?.get3DViewController(isRegistrationContext)
        return threeDViewController!
    }

    func get3DViewController() -> UIViewController {
        return threeDViewController!
    }

    func show3DViewController(){
        PSDaonSdk.instance.daonSdkDelegate?.show3DViewController()
    }
}

//MARK:-Authentication

extension PSDKLiveness3DManager: FidoAuthenticationTaskDelegate {
    func onFidoAuthenticationSuccess() {
        PSDaonSdk.instance.daonSdkDelegate?.onFidoAuthenticationSuccess()
    }

    func onFidoAuthenticationCancelled() {
        PSDaonSdk.instance.daonSdkDelegate?.onFidoAuthenticationCancelled()
    }

    func onFidoAuthenticationFailed(_ error: Error) {
        PSDaonSdk.instance.daonSdkDelegate?.onFidoAuthenticationFailed(error)
    }

    func get3DViewControllerForAuth(_ isRegistrationContext:Bool) -> UIViewController {
        PSDaonSdk.instance.daonSdkDelegate?.get3DViewControllerForAuth(isRegistrationContext)
        return threeDViewController!
    }

    func show3DViewControllerForAuth() {
        PSDaonSdk.instance.daonSdkDelegate?.show3DViewControllerForAuth()
    }

}
#endif
