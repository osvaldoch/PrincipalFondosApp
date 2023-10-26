import PS_FacialUI
import PS_Facial_Engine
import Foundation
extension FacialSDKManager:PSFUTutorialVC4Delegate{
    func nextButtonPressed() {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleFinishMainTutorial()
    }
    func didLoad(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .StartMainTutorial, error: nil, cveDoc: nil)
    }
}
