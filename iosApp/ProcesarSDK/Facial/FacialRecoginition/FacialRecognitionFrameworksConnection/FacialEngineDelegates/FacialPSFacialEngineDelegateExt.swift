import Foundation
import UIKit
import PS_FacialUI
import DaonDocument
import PS_Facial_Engine

extension FacialSDKManager: PSFacialEngineDelegate {
    func getScanningFront() -> Bool {
        return FacialSDKManager.instance.documentCaptureOverlayDelegate!.getScanningFront()
    }
    
    func dmdsUtilitiesEncodeBase64Jpeg(image: UIImage, imageQuality: Float) -> String {
        return DMDSUtilities
            .encodeBase64Jpeg(image,
                              withQuality: imageQuality )
    }
    
    func setScannedDocumentsInPSFacialEngine(){
        let capturedDocument:PSDKCapturedDocument = PSDKCapturedDocumentManager.instance.manager.copy()
        
        let frontImage = capturedDocument.front
//        if (PSFacialEngine.getInstance().psfeFacialInfo?.scanDocumentScreenSize == .Large){
//            frontImage = capturedDocument.front?.unprocessedImage
//        }
        
        if let frontImage = frontImage {
            PSFacialEngine.getInstance().setDocumentImage(frontImage.processedImage)
            PSFacialEngine.getInstance().setUnprocessedDocumentImage(frontImage.unprocessedImage)
            PSFacialEngine.getInstance().setFrontCapturedTime(capturedDocument.frontCapturedTime!)
        }
        
        let backImage = capturedDocument.back
//        if (PSFacialEngine.getInstance().psfeFacialInfo?.scanDocumentScreenSize == .Large){
//            backImage = capturedDocument.back?.unprocessedImage
//        }
        
        if let backImage = backImage {
            PSFacialEngine.getInstance().setDocumentImageBack(backImage.processedImage)
            PSFacialEngine.getInstance().setUnprocessedDocImageBack(backImage.unprocessedImage)
            PSFacialEngine.getInstance().setBackCapturedTime(capturedDocument.backCapturedTime!)
        }

    }
}
