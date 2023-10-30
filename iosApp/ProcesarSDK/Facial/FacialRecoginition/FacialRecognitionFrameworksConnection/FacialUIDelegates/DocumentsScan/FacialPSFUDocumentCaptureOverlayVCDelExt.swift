#if RELEASE
import PS_FacialUI
import UIKit
import PS_Facial_Engine

extension FacialSDKManager: PSFUDocumentCaptureOverlayVCDelegate{
    func startWithScanningRegion(rect: CGRect) {
        PSDKCaptureManager.instance.manager?.setScanningRegion(rect)
    }
    func onReescanButtonPressed() {
        PSFacialEngine.getInstance().documentsFlow.handleReescann()
    }
    func onContinueButtonPressed() -> Bool{
        return PSFacialEngine.getInstance().documentsFlow.handleContinue()
    }
    
    func onScanButtonPressed() {
        PSDKCaptureManager.instance.manager?.startScanning()
    }
    
    func adjustOptionsForBackSideScanning(){
        PSDKCaptureManager.instance.adjustOptionsForBackSideScanning()
    }
    
    func onViewDidLoad(){
        if let document = PSFacialEngine.getInstance().getDocumentType(){
            if document == .BirthCertificate{
                PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .StartActaDoc, error: nil, cveDoc: nil)
            }else{
                PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .StartFrontDoc, error: nil, cveDoc: nil)
            }
            
        }
    }
    
    func scanningMode() -> PSFUDocumentCaptureOverlayViewController.ScanningMode {
        switch PSFacialEngine.getInstance().getDocumentSide() {
        case .Front:
            return .Front
        case .Back:
            return .Back
        default:
            return .Front
        }
        
    }

}
#endif
