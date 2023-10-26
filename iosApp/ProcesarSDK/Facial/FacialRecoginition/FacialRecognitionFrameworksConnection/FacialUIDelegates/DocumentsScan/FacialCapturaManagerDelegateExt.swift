
import Foundation
import UIKit
import DaonDocument
import PS_FacialUI

extension FacialSDKManager : CaptureManagerDelegate {
 
    

    func getCameraController() -> NSObject? {
        return nil
    }

    
    func completeDocumentCapture() {
        if let childViewController = FacialSDKManager.instance.psdkDocCaptOverlayHelperViewController
        {
            childViewController.willMove(toParent: nil)
            childViewController.removeFromParent()
            childViewController.view.removeFromSuperview()
        }
        FacialSDKManager.instance.implementedDocumentCaptureVCDelegate?.onCompleteDocumentCapture()
    }
    
    //MARK:- CaptureManagerDelegate
 
    func stopScanning() {
        FacialSDKManager.instance.psdkDocCaptOverlayHelperViewController!.psDocumentCaptureOverlayViewController!.resetTimers()
        PSDKCaptureManager.instance.manager!.stopScanning()
    }

    func restartScanning() {
        PSDKCaptureManager.instance.manager!.restartScanning()
    }
}

