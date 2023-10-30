#if RELEASE
import PS_FacialUI
import UIKit
import Foundation
import PS_Facial_Services
import DaonFIDOSDK
import PS_Facial_Engine

extension FacialSDKManager: ReviewVCDelegate {
    
    func getFaceImage() -> UIImage? {
        return PSFacialEngine.getInstance().getFaceImage()
    }
    
    func getDocumentImage() -> UIImage? {
        return PSFacialEngine.getInstance().getDocumentImage()
    }
    
    func getDocumentImageBack() -> UIImage? {
        return PSFacialEngine.getInstance().getDocumentImageBack()
    }
    
    func getIdxUserId() -> String?{
        return  PSFacialEngine.getInstance().getIdxUserId()
    }
    
    func getIdCheckId() -> String?{
        return PSFacialEngine.getInstance().getIdCheckId()
    }
    
    func getDocumentIds() -> [String]?{
        return PSFacialEngine.getInstance().getDocumentIds()
    }
    
    func getLivenessVideoIds() -> [String]?{
        return PSFacialEngine.getInstance().getLivenessVideoIds()
    }
    
    func evaluationWithError(error: Error?) {
        PSFacialEngine.getInstance().setStageReached(.evaluationCheckFailed)
    }
    
    func onApplyReview(){
        PSFacialEngine.getInstance().executeReview()
    }
    

    func willAppearReview() {
        //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .StartRandom, error: nil,cveDoc: nil)
    }
    
    func finishReview(error: Error?) {
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
    }

}
#endif
