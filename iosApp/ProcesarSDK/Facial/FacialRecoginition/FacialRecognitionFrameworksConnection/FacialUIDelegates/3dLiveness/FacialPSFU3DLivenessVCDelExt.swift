import PS_FacialUI
import UIKit
import PS_Facial_Engine

extension FacialSDKManager: PSFU3DLivenessVCDelegate {
    

    func onViewWillAppear(viewFor3dCamera: UIView)->Float{
        return PSFacialEngine
            .getInstance()
            .psfeLiveness3DManager
            .handle3DViewWillAppear(viewToShow3DCamera: viewFor3dCamera)
        
    }
    
    func isReadyFor3D()->Bool{
        return PSFacialEngine
            .getInstance()
            .psfeLiveness3DManager
            .isReadyFor3D()
    }
    
    func on3DViewDidAppear(){
        PSFELiveness3DManager.instance.handle3DViewDidAppear()
    }
    
    func onTakeSelfieImage() -> UIImage? {
        return PSFELiveness3DManager.instance.handleOnTakeSelfieImage()
    }
    
    func onViewWillDisappear() {
        PSFELiveness3DManager.instance.handleOn3DVCViewWillDisappear()
    }
    
    func onViewDidAppear3D(){
        PSFELiveness3DManager.instance.handleOnViewDidAppear3D()
    }
    
    func handleOrientationChange() {
        PSFELiveness3DManager.instance.handleOrientationChange()
    }
    
    func onEnrollPressed(image: UIImage) {
        PSFELiveness3DManager.instance.handleOnEnrollPressed(image: image)
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .ClickContinueSelfie, error: nil, cveDoc: nil)
    }
    
    func onRetakePhotoPressed() {
        PSFELiveness3DManager.instance.handleOnRetakePhotoPressed()
    }
    
    func onOpenTutorialPressed(){
        PSFELiveness3DManager.instance.handleOnOpen3DTutorialPressed()
    }
    
    func onDidLoadSelfiePreview(){
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .SelfiePreview, error: nil,cveDoc: nil)
    }
    
    func rotateImage(image: UIImage, orientation: UIImage.Orientation) -> UIImage {
        
        guard let image = PSFacialEngine.getInstance().psFacialEngineDaonSDKDelegate?.rotateImage(image, to: orientation) else {
            return UIImage()
        }
        
        return image
    }
    
    func onVerifingPhoto(image: UIImage) {
        PSFacialEngine.getInstance().setFaceImage(image)
    }
}
