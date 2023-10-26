import PS_FacialUI
import PS_Facial_Engine

extension FacialSDKManager: PSFUTimerVCDelegate {
    func onTimerCompleted(vc: PS_FacialUI.TimerViewController) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnTimerCompleted()
    }
    
    func onTimerCanceled(vc: TimerViewController) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnTimerCanceled()
    }
    
}
