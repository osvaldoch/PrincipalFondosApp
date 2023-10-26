import PS_FacialUI
import PS_Facial_Engine
extension FacialSDKManager: PSFUIDocumentCaptureFirstVCDelegate {
    
    func onContinueClicked() {
        PSFacialEngine.getInstance().documentsFlow.handleContinueBtnOfFirstView(transitionDirection: .toRight)
    }
    
    func onBackButtonClicked() {
        PSFacialEngine.getInstance().documentsFlow.handleBackBtnOfFirstView()
    }
}
