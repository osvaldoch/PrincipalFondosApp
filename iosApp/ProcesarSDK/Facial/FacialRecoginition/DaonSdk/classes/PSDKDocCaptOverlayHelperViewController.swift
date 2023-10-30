#if RELEASE
import UIKit
import DaonDocument
import PS_FacialUI
import PS_Facial_Engine

class PSDKDocCaptOverlayHelperViewController: UIViewController, DMDSCustomScanDelegate
{

    public var completionHandler : ((PSDKCapturedDocument) -> ())?
    public var psDocumentCaptureOverlayViewController: PSFUDocumentCaptureOverlayViewController? = FacialUIExecute.shared.getPSDocumentCaptureOverlayViewController()
    //private let capturedDocument = CapturedDocument()
    
    // MARK:- View Lifecycle
    
    override func viewDidLoad()
    {
        super.viewDidLoad()

        psDocumentCaptureOverlayViewController!.completionHandler = {
            () in
            //self.onCompleteDocumentCapture(capturedDocument)
            FacialSDKManager.instance.completeDocumentCapture()
        }
        
        self.addChild(psDocumentCaptureOverlayViewController!)
        self.view.addSubview(psDocumentCaptureOverlayViewController!.view)
        
 
    }
    
    // MARK:- DMDSCustomScanDelegate
    func documentScanned(with scanningResult: DMDSResult)
    {
        if (PSFacialEngine.getInstance().getDocumentSide() == PSFEImageDocument.DocumentType.Front)
        {
            PSDKCapturedDocumentManager.instance.manager.frontCapturedTime  = Date()
            PSDKCapturedDocumentManager.instance.manager.front              = scanningResult.document
        }
        else
        {
            PSDKCapturedDocumentManager.instance.manager.backCapturedTime  = Date()
            PSDKCapturedDocumentManager.instance.manager.back              = scanningResult.document
        }
        let allDocumentsScanned = FacialSDKManager.instance.allDocumentsScanned()
        
        var scannedImage: UIImage = scanningResult.document.processedImage
        if let image = scanningResult.document.unprocessedImage, PSFacialEngine.getInstance().psfeFacialInfo?.scanDocumentScreenSize == .Large {
            scannedImage = image
        }
        //let croppedImage = DMDSUtilities.cropImage(unprocessedImage, withCoordinates: scanningResult.document.processedDocumentCoordinates) ?? UIImage()
        
        psDocumentCaptureOverlayViewController!.documentScanned(with: scannedImage, allFinished: allDocumentsScanned)
    }
    
    func mrzDetected(_ mrzDetected: DMDSMrzDetectionMetadata)
    {
        psDocumentCaptureOverlayViewController!.startScanningTimer()
        
        if (psDocumentCaptureOverlayViewController!.mrtzShapeLayer != nil)
        {
            psDocumentCaptureOverlayViewController!.mrtzShapeLayer?.removeFromSuperlayer()
        }
        
        psDocumentCaptureOverlayViewController!.mrtzShapeLayer = psDocumentCaptureOverlayViewController!.createBorderLayer(upperLeft: mrzDetected.detectionLocation.upperLeft, upperRight: mrzDetected.detectionLocation.upperRight, lowerLeft: mrzDetected.detectionLocation.lowerLeft, lowerRight: mrzDetected.detectionLocation.lowerRight, color: UIColor.yellow, isSolid: true)
        
        
        if (psDocumentCaptureOverlayViewController!.removeMRTZBorderLayerTimer != nil)
        {
            psDocumentCaptureOverlayViewController!.removeMRTZBorderLayerTimer!.invalidate()
        }
        
        psDocumentCaptureOverlayViewController!.removeMRTZBorderLayerTimer = Timer.scheduledTimer(timeInterval: 0.2, target: self, selector: #selector(psDocumentCaptureOverlayViewController!.removeMRTZBorderLayer(timer:)), userInfo: nil, repeats: false)
    }
    
    func documentScanFailedWithError(_ error: Error) {
        DobsLogUtils.logError("Error al escanear el documento, error: " + error.localizedDescription)
    }
    
    func documentDetected(_ documentDetected: DMDSDocumentDetectionMetadata)
    {
        psDocumentCaptureOverlayViewController!.startScanningTimer()
        
        if (psDocumentCaptureOverlayViewController!.documentShapeLayer != nil)
        {
            psDocumentCaptureOverlayViewController!.documentShapeLayer?.removeFromSuperlayer()
        }
        
        psDocumentCaptureOverlayViewController!.documentShapeLayer = psDocumentCaptureOverlayViewController!.createBorderLayer(upperLeft: documentDetected.detectionLocation.upperLeft, upperRight: documentDetected.detectionLocation.upperRight, lowerLeft: documentDetected.detectionLocation.lowerLeft, lowerRight: documentDetected.detectionLocation.lowerRight, color: UIColor.yellow, isSolid: false)
        
        
        if (psDocumentCaptureOverlayViewController!.removeBorderLayerTimer != nil)
        {
            psDocumentCaptureOverlayViewController!.removeBorderLayerTimer!.invalidate()
        }
        
        psDocumentCaptureOverlayViewController!.removeBorderLayerTimer = Timer.scheduledTimer(timeInterval: 0.2, target: self, selector: #selector(removeDocumentBorderLayer(timer:)), userInfo: nil, repeats: false)
    
    }
    
    @objc public func removeDocumentBorderLayer(timer: Timer)
    {
    psDocumentCaptureOverlayViewController!.removeLayerWithAnimation(psDocumentCaptureOverlayViewController!.documentShapeLayer)
    }

    
    func detectionTimeoutWithError(_ error: Error) {
        
        if (!Thread.isMainThread) {
            DispatchQueue.main.sync {
                detectionTimeoutWithError(error)
            }
            return
        }
        
        self.psDocumentCaptureOverlayViewController!.scanningRegion.showNoDetectedBorder()
        
        UIView.transition(with: psDocumentCaptureOverlayViewController!.messageDetail,
                          duration: 0.3,
                          options: .transitionCrossDissolve,
                          animations: {
            
            if  let couldNotScanDocTxt = FacialUIExecute.shared.psfuAnyDocInfo?.couldNotScanDocTxt {
                
                self.psDocumentCaptureOverlayViewController!.messageDetail.text = couldNotScanDocTxt
                            }
            else{
                self.psDocumentCaptureOverlayViewController!.messageDetail.text = "No se puede capturar el documento en el tiempo asignado."
            }

            self.psDocumentCaptureOverlayViewController!.rescanButton.isHidden = false
            
        }, completion: nil)

        // Invalidate timer to prevent race conditions that would hide rescan button
        psDocumentCaptureOverlayViewController!.scanningMessageUpdateTimer?.invalidate()

        
    }
    
}
#endif
