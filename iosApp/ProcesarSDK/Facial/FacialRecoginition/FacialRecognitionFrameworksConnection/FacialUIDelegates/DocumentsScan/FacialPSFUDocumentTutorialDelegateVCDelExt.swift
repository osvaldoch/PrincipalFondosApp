#if RELEASE
import PS_FacialUI
import PS_Facial_Engine
extension FacialSDKManager: PSFUDocumentTutorialVCDelegate{
    func onActivateCamera(){
        PSFacialEngine.getInstance().documentsFlow.handleOnActivateCamera()
    }
    func backInstructionsBtnClicked() {
        PSFacialEngine.getInstance().documentsFlow.handleContinueBtnOfFirstView(transitionDirection: .toLeft)
    }
}
#endif
