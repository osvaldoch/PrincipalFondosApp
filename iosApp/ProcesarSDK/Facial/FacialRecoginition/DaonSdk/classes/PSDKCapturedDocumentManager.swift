#if RELEASE
import Foundation
import PS_FacialUI

public class PSDKCapturedDocumentManager: NSObject {
    
    public static var instance: PSDKCapturedDocumentManager = PSDKCapturedDocumentManager()
    
    internal var manager = PSDKCapturedDocument()
    
    func rescan(scanningFront: Bool, backDocumentType: String){
        
        if (scanningFront)
        {
            PSDKCapturedDocumentManager.instance.manager.frontCapturedTime  = nil
            PSDKCapturedDocumentManager.instance.manager.front              = nil
        }
        else
        {
            PSDKCapturedDocumentManager.instance.manager.backCapturedTime  = nil
            PSDKCapturedDocumentManager.instance.manager.back              = nil
            
            PSDKCaptureManager.instance.manager?.options?.documentTypes.removeAllObjects()
            PSDKCaptureManager.instance.manager?.options?.documentTypes.add(backDocumentType)
        }
        
        PSDKCaptureManager.instance.manager!.restartScanning()
    }
    
    func clean(){
        PSDKCapturedDocumentManager.instance.manager.frontCapturedTime = nil
        PSDKCapturedDocumentManager.instance.manager.front = nil
        PSDKCapturedDocumentManager.instance.manager.backCapturedTime = nil
        PSDKCapturedDocumentManager.instance.manager.back = nil
    }

}
#endif
