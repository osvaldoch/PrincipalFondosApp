import PS_FacialUI
import PS_Facial_Engine
extension FacialSDKManager: PSFUTutorial3DVCDelegate{
    func didTapContinue(tutorialViewController: PS_FacialUI.TutorialViewController){
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOn3DTutorialContinue()
    }
    
}
