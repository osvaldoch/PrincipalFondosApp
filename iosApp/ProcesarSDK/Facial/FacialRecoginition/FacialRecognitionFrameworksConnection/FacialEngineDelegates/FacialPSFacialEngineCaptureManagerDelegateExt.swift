import Foundation
import UIKit
import PS_Facial_Engine

extension FacialSDKManager: PSFacialEngineCaptureManagerDelegate {
    
    func documentDetected(upperLeft: CGPoint, upperRight: CGPoint, lowerLeft: CGPoint, lowerRight: CGPoint , documentFillsScanningArea: Bool) {
        FacialSDKManager.instance.documentCaptureOverlayDelegate!.documentDetected(upperLeft: upperLeft, upperRight: upperRight, lowerLeft: lowerLeft, lowerRight: lowerRight, documentFillsScanningArea: documentFillsScanningArea)
    }
    
    func mrzDetected(upperLeft: CGPoint, upperRight: CGPoint, lowerLeft: CGPoint, lowerRight: CGPoint) {
        FacialSDKManager.instance.documentCaptureOverlayDelegate!.mrzDetected(upperLeft: upperLeft, upperRight: upperRight, lowerLeft: lowerLeft, lowerRight: lowerRight)
    }
    
    func documentScanned(image: UIImage) {
        FacialSDKManager.instance.documentCaptureOverlayDelegate?.documentScanned(image: image)
    }
}
