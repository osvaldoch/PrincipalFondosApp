import Foundation
import UIKit
import PS_Facial_Engine
import PS_FacialUI

extension FacialSDKManager: PSFUDocumentScanHolderVCDelegate {
    func onCaptureError(stageName: String, error: Error) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnDocumentsError(error)
    }
    
    func setImplementedDocumentCaptureVCDelegate(implementedDocumentCaptureVCDelegate: ImplementedDocumentCaptureVCDelegate) {
        self.implementedDocumentCaptureVCDelegate = implementedDocumentCaptureVCDelegate
    }
    
    
    func giveMeCustomViewForCaptureDocuments(completionHandler: (_ customViewForCaptureDocsVC: UIViewController?, Error?) -> Void){
        let bundle = Bundle(for: type(of: self))
        let storyboard = UIStoryboard(name: "DocumentCapture", bundle: bundle)
        let psdkDocCaptOverlayHelperViewController = storyboard.instantiateViewController(withIdentifier: "PSDKDocCaptOverlayHelperViewController") as? PSDKDocCaptOverlayHelperViewController
        FacialSDKManager.instance.psdkDocCaptOverlayHelperViewController = psdkDocCaptOverlayHelperViewController
        let psfeDocumentType = PSFacialEngine.getInstance().getDocumentType()!
        let psfeIdDocument = PSFacialEngine
            .getInstance()
            .documentsFlow
            .getPSFEIdDocument(psfeDocumentType: psfeDocumentType)
        PSDKCaptureManager.instance.backDocumentType = psfeIdDocument.back?.docType
        psdkDocCaptOverlayHelperViewController!.completionHandler = {
            (capturedDocument) in
            FacialSDKManager.instance.completeDocumentCapture()
        }
        if let psdkDocVC = psdkDocCaptOverlayHelperViewController{
            PSDKCaptureManager
                .instance
                .setCustomCapture(withOverlay: psdkDocVC,
                                  idDocument: psfeIdDocument) {
                                    (error) in
                                    guard error == nil else {
                                        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .ClickContinueFrontDoc, error: nil, cveDoc: nil)
                                        
                                        completionHandler(nil, error!)
                                        return
                                    }
                    if let camera = PSDKCaptureManager.instance.manager?.cameraController{
                        completionHandler(camera, error)
                    }
            }
        }
        
    }
    
    func onAllDocumentsScanned() {
        PSFacialEngine.getInstance().documentsFlow.handleAllDocumentsScanned()
    }
    
    func cancelScanDocuments() {
        PSFacialEngine.getInstance().documentsFlow.handleCancelScann(transitionDirection: .toLeft)
    }
}

