import Foundation
import PS_FacialUI
import PS_Facial_Engine

extension FacialSDKManager: PSWelcomeVCDelegate {
    
    func getApplicationName() -> String? {
        return PSFacialEngine.getInstance().getAppName()
    }
    
    func didAppearWelcome() {
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .StartWelcome, error: nil, cveDoc: nil)
    }
    
    
    func onContinueBtnPressed(psfuWelcomeViewController: PSFUWelcomeViewController){
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .ContinueWelcome, error: nil, cveDoc: nil)
        PSFacialEngine.getInstance().psfeProcesarFlow.handleWelcomeContinue(skipTutorial: psfuWelcomeViewController.switchOut.isOn)
    }
    
    func getSkipTutorial() -> Bool? {
        return PSFacialEngine.getInstance().getSkipTutorial()
    }

    func onChangeSkipTutorial(skip: Bool) {
        PSFacialEngine.getInstance().setSkipTutorial(skipTutorial: skip)
    }
    
    func backButtonPressed(vc: PSFUWelcomeViewController) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnWelcomeBackButtonPressed()
    }
   
}
