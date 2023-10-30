#if RELEASE
import PS_FacialUI
import DaonDocument
import PS_Facial_Engine
import UIKit


extension FacialSDKManager: PSFacialEnginePSFacialUIDelegate {
    
    //MARK:- tutorial
    func openWelcomeScreen(transitionDirection: PSFEDirection){
        let transitionDirection = psfeTransitionDirection(transitionDirection: transitionDirection)
        FacialUIExecute.shared.setFlow(flow: .Welcome, transitionDirection:transitionDirection )
    }
    func openMainTutorial(){
        FacialUIExecute.shared.setFlow(flow: .Tutorial)
    }
    
    //MARK:- 3D liveness FLOW
    func get3DViewController() -> UIViewController{
        return FacialUIExecute.shared.getPSFU3DLivenessVC()
    }
    
    func open3DLiveness(){
        FacialUIExecute.shared.setFlow(flow: .Show3DNew)
    }
    /*
     * indica si el context de fido es tipo registro si no lo es entonces es tipo authenticacion
     */
    func onRegistrationContext(isRegistrationContext: Bool) {
        FacialUIExecute.shared.psfu3DFlowManager.isRegistrationContext = isRegistrationContext
    }
    
    func onFaceControllerStartedAnalysis(hasRequiredLivenessEvents: Bool) {
        FacialUIExecute
            .shared
            .psfu3DFlowManager
            .handleFaceControllerStartedAnalysis(hasRequiredLivenessEvents: hasRequiredLivenessEvents)
    }
    // prueba de vida completada satisfactoriamente
    func onFaceControllerCompletedSuccessfully() {
        PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext!.completeCapture()
        FacialUIExecute.shared.psfu3DFlowManager.psfu3DLivenessViewController?.handleFaceControllerCompletedSuccessfully()
    }
    func onFaceControllerCapturedImage(_ image: UIImage?) {
        FacialUIExecute.shared.psfu3DFlowManager.handleFaceControllerCapturedImage(image: image)
    }
    
    func onFaceControllerProcessedFrame(withResult: Bool, imageQualityIssues: [NSNumber]?, isCancelling: Bool) {
        
        var imageQI: [NSNumber] = []
        
        if let imageQualityIssues = imageQualityIssues {
            imageQI = imageQualityIssues
        }
        FacialUIExecute.shared.psfu3DFlowManager.handleFaceControllerProcessedFrame(withResult: withResult, imageQualityIssues: imageQI, isCancelling: isCancelling)
       
    }
    
    func onFaceControllerDetectedLivenessEvent(_ event: PSFELiveness3DManager.PSFEFaceLivenessEvent, for image: UIImage!, allRequiredLivenessEventsDetected: Bool) {
        FacialUIExecute.shared.psfu3DFlowManager.psfu3DLivenessViewController?.handleFaceControllerDetectedLivenessEvent(PSFU3DLivenessViewController.PSFUFaceLivenessEvent(rawValue: event.rawValue)!, for: image, allRequiredLivenessEventsDetected: allRequiredLivenessEventsDetected)
    }
    func onFaceControllerUpdatePositionIndicator(isUpright:Bool){
        FacialUIExecute.shared.psfuRandomManager.psfuRandomLivenessViewController?.updatePositionIndicator(isUpright: isUpright)
    }
    
    func open3DTutorial(){
        FacialUIExecute.shared.setFlow(flow: PSFUFlow.ThreeDTutorialForAuth)
    }
    
    //MARK:- Documents
    func openDocumentCaptureFirstView(transitionDirection: PSFEDirection){
        let transitionDirection = psfeTransitionDirection(transitionDirection: transitionDirection)
        FacialUIExecute.shared.setFlow(flow: .FirstDocumentCapture,transitionDirection: transitionDirection)
    }
    
    func openChooseDocumentInstructions(transitionDirection: PSFEDirection){
       
        PSFacialEngine.getInstance().psfeProcesarFlow.handleCaptureDocsTutorial1ContinueBtnEvent(transitionDirection: transitionDirection)
    
    }
    
    func openDocumentTutorial(){
        FacialUIExecute.shared.documentType = getPSFUDocumentTypeDepedingOnFacialEngineDocType()
        FacialUIExecute.shared.setFlow(flow: .DocumentTutorial)
    }
    
    func openDocumentCameraScanner(){
        FacialUIExecute.shared.setFlow(flow: .DocumentCameraScanner)
    }

    
    func closeUI(){
        FacialUIExecute.shared.close()
    }
    
    func closeUI(animated: Bool){
        FacialUIExecute.shared.close(animated: animated, completion: nil)
    }
    func openLoading() {
        FacialUIExecute.shared.setFlow(flow: .Loading)
    }
    func getCameraView()->UIView{
        return FacialUIExecute.shared.psfuRandomManager.getCameraView()
    }
    
    func onCameraStarted(){
        FacialUIExecute.shared.psfuRandomManager.psfuRandomLivenessViewController?.onCameraStarted()
    }
    
    
    //REVIEW
    func openReview() {
        FacialUIExecute.shared.setFlow(flow: PSFUFlow.Review, transitionDirection: .toRight)
    }
    
    //TIMEER
    func openTimer() {
        FacialUIExecute.shared.setFlow(flow: PSFUFlow.Timer, transitionDirection: .toRight)
    }
    
    //MARK:-Carousel
    func closeWaitCarousel() {
        if PSFacialEngine.getInstance().psfeProcesarFlow.closeFacialAutomatically || PSFacialEngine.getInstance().getFacialMode() == .ShowCarousel {
            FacialUIExecute.shared.closeCarousel()
        }
    }
    func showWaitCarousel() {
        FacialUIExecute.shared.showCarousel()
    }
    
    //MARK:- Others
    func showError(error: Error, completion: ((Int, String) -> Void)? ){
        FacialUIExecute.shared.showAlertError(error: error, completion: completion)
    }
    
    func showErrorCancel(error: Error, completion: ((Int, String) -> Void)?) {
        FacialUIExecute.shared.showAlertErrorCancel(error: error, completion: completion)
    }
    
    func closeUI(completion: (() -> Void)?) {
        FacialUIExecute.shared.close(completion: completion)
    }
    
}
#endif
