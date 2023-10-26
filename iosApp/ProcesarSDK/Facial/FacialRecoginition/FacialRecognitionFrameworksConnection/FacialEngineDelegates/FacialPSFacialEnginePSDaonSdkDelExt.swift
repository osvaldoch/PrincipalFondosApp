import DaonDocument
import AVFoundation
import PS_Facial_Engine
extension FacialSDKManager: PSFacialEngineDaonSDKDelegate {


    //MARK:- 3d
    
    func existsDeviceAuthenticator(authenticatorAaid: String, completion: @escaping (NSError?, Bool) -> ()) {
        Fido.shared.existsDeviceAuthenticator(authenticatorAaid: authenticatorAaid,
                                              completion: completion)
    }
    
    func show3dCameraInView(view: UIView){
        PSDKLiveness3DManager
            .instance
            .configureFaceController(withPreviewView: view,
                                     context: PSDKSingleAuthenticatorContextManager
                                        .intance
                                        .singleAuthenticatorContext)
    }
    
    func start3dFaceController(){
        PSDKLiveness3DManager.instance.faceController?.start()
    }
    
    func resumeFaceController(image: UIImage) {
        //PSDKLiveness3DManager.instance.faceController?.resume()
        PSDKLiveness3DManager.instance.faceController?.register(image: image)
    }
    
    func startRegistration3DLiveness( threeDViewController: UIViewController, userId: String, firstName: String, lastName: String) {
        PSDKLiveness3DManager.instance.startRegistration3DLiveness( threeDViewController: threeDViewController, userId: userId, firstName: firstName, lastName: lastName)
    }
    
    func startAuth3DLiveness( threeDViewController: UIViewController, userId: String) {
        PSDKLiveness3DManager.instance.startAuth3DLiveness( threeDViewController: threeDViewController, userId: userId)
    }
    
    func getLivenessTrackingDuration() -> Float {
        return 0.0
//        return PSDKLiveness3DManager
//        .instance
//        .faceController!
//        .livenessTrackingDuration()
    }
    
    func isReadyFor3D(psFacialEngine: PSFacialEngine) -> Bool{
        return PSDKLiveness3DManager.instance.isReadyFor3D()
    }
    
    func takeSelfieImage(psFacialEngine: PSFacialEngine) -> UIImage? {
        guard let image = PSDKLiveness3DManager.instance.faceController?.captureImage() else {
            return nil
        }
        let rotatedImage = image //PSFacialEngine.getInstance().psFacialEngineDaonSDKDelegate?.rotateImage(image, to: .rightMirrored)
        return rotatedImage
    }
    
    func setFaceControllerToNil(){
        PSDKLiveness3DManager.instance.faceController = nil
    }

    func startFaceController(){
        PSDKLiveness3DManager.instance.faceController?.start()
    }
    
    func handleOrientationChange(psFacialEngine: PSFacialEngine){
         PSDKLiveness3DManager.instance.faceController?.handleOrientationChange()
    }
    
    func restartFaceController(){
        PSDKLiveness3DManager.instance.faceController?.resume()
    }
    
    func cancelFaceController(){
        PSDKLiveness3DManager.instance.cancel()
    }
    
    func handleCompleteCaptureWithErrorCode(errorCode: Int){
          PSDKSingleAuthenticatorContextManager.intance.completeCaptureWithErrorCode(errorCode: errorCode)
      }
    
    //MARK:- documentes
    func resetDocumentScan() {
        PSDKCapturedDocumentManager.instance.clean()
    }
    
    func getKMexicoFrontVoterID() -> String {
        return kMexicoFrontVoterID
    }
    
    func getKMrz() -> String {
        return kMrz
    }
    
    func getKEdgeDetection() -> String {
        return kEdgeDetection
    }
    
    func getKPassport() -> String {
        return kPassport
    }
    
    func setCustomCaptureOverlay() {
        print("setCustomCaptureOverlay")
    }

    func reescann(){
        if (PSFacialEngine.getInstance().getDocumentSide() == PSFEImageDocument.DocumentType.Front)
        {
            PSDKCapturedDocumentManager.instance.manager.frontCapturedTime  = nil
            PSDKCapturedDocumentManager.instance.manager.front              = nil
        }
        else
        {
            PSDKCapturedDocumentManager.instance.manager.backCapturedTime  = nil
            PSDKCapturedDocumentManager.instance.manager.back              = nil
            PSDKCaptureManager.instance.manager?.options?.documentTypes.removeAllObjects()
            PSDKCaptureManager.instance.manager?.options?.documentTypes.add(PSDKCaptureManager.instance.backDocumentType!)
        }
        
        
   
        PSDKCaptureManager.instance.manager!.restartScanning()
          
        
        
    }
    
    func checkAllDocumentsScanned() -> Bool{
        return allDocumentsScanned()
    }

    
    //MARK:- DAON
    
    func initialize(psfeRegistrationMode: PSFERegistrationMode,
                    completion: @escaping (NSError?, Bool) -> ()){
        PSDaonSdk.instance.initialize(psdkRegistrationMode: PSDKRegistrationMode(rawValue:psfeRegistrationMode.rawValue)!,
                                      completion: completion)
    }
    
    func removeFidoAuthenticatorAndDeleteUserIfNeeded(userId: String,completion: @escaping (_ userFound:Bool, _ userDeleted:Bool, PSFEError?) -> (Void)){
        PSDaonSdk.instance.removeFidoAuthenticatorAndDeleteUserIfNeeded(userId: userId, completion: completion)
    }
    
    func cleanDaonDocumentsManager(){
        PSDKCapturedDocumentManager.instance.clean()
    }
    
    func resetFido(){
        PSDaonSdk.instance.fidoSkd.resetFido()
    }
    
}
