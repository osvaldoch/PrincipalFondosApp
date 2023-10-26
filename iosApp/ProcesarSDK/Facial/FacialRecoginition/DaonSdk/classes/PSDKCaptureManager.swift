
import Foundation
import DaonDocument
import PS_Facial_Engine

class PSDKCaptureManager:NSObject {
    
    public var backDocumentType : String?
    public static var instance: PSDKCaptureManager = PSDKCaptureManager()
    
    internal var manager: DMDSCaptureManager?
    
    private override init(){
        manager = DMDSCaptureManager()
    }
    
    public func setCustomCapture(withOverlay: UIViewController & DMDSCustomScanDelegate,
                                 idDocument: PSFEIdDocument,
                                 completionHandler: (Error?) -> Void){
        
        if let managerCapture = manager {
            managerCapture.customCapture(withOverlay: withOverlay,
                                   cameraOptions: captureOptions(for: idDocument)) { (error) in
                
                
                completionHandler(error)
            }
        }
        
    }
    
    private func captureOptions(for document: PSFEIdDocument) -> DMDSOptions
    {
        
        if (PSFacialEngine.getInstance().psfeFacialInfo?.scanDocumentScreenSize == .Large &&
            (PSFacialEngine.getInstance().psfeFacialInfo?.documentType == .AnyDoc || PSFacialEngine.getInstance().getFacialMode() == .Minor)){
            
            return optionForPortrait()
        }
        
        let documentTypes = NSMutableSet()
        documentTypes.add(document.front.docType)
        
        let options             = DMDSOptions()
        options.licenseKey      = PSDaonSdk.instance.getDocumentsLicence()
        options.documentTypes   = documentTypes
        options.defaultProcessedImageDPI = 400
        options.faceDetection   = false
        options.autoStartScanning = true
        options.scanningDuration = 10
        options.fallbackToEdgeDetectionDuration = 10
        options.fallbackToEdgeDetectionDocumentType = kEdgeDetection_ID1
        options.edgeDetectionVerticalCardScan = false
        
        // Habilitar deteccion de bordes "fallbackToEdgeDetection" en caso de no reconocer documento(Credencial de votar)
        // Si se habilita al momento de escanear documentos, se intentara escanear el documento con deteccion de bordes.
        options.fallbackToEdgeDetection = true
        options.edgeDetectionPortraitScaleTolerance = 0.12
        
        return options
    }
    
    private func optionForPortrait() -> DMDSOptions {
        let documentTypes = NSMutableSet()
        //documentTypes.add(document.front.docType)
        documentTypes.add(kEdgeDetection_A4_Portrait)
        
        let options             = DMDSOptions()
        options.licenseKey      = PSDaonSdk.instance.getDocumentsLicence()
        options.documentTypes   = documentTypes
        options.faceDetection   = false
        options.fallbackToEdgeDetection = false
        options.fallbackToEdgeDetectionDuration = 60;
        options.defaultProcessedImageDPI = 400
        options.scanningDuration = 10
        options.stableEdgeDetectionsNumber = 6
        options.customEdgeDetectionAspectRatio = 1.41999996
        options.customEdgeDetectionPhysicalSizeInInches = 3.46000004
        options.edgeDetectionPortraitScaleTolerance = 0.119999997
        options.edgeDetectionLandscapeScaleTolerance = 0.0799999982
        options.edgeDetectionVerticalCardScan = false
        options.autoStartScanning = true

    
        return options
    }
    
    func adjustOptionsForBackSideScanning(){
        if let backDocumentType = backDocumentType{
            
            manager!.options?.documentTypes.removeAllObjects()
            manager!.options?.documentTypes.add(backDocumentType)
            manager!.options?.faceDetection = false
            manager!.options?.scanningDuration = 10
            manager!.options?.autoStartScanning = true
            manager!.options?.fallbackToEdgeDetectionDuration = 10
            manager!.options?.fallbackToEdgeDetectionDocumentType = kEdgeDetection_ID1
            manager!.options?.edgeDetectionVerticalCardScan = false
            // Habilitar deteccion de bordes "fallbackToEdgeDetection" en caso de no reconocer documento(Credencial de votar)
            // Si se habilita al momento de escanear documentos, se intentara escanear el documento con deteccion de bordes.
            manager!.options?.fallbackToEdgeDetection = true
            manager!.options?.edgeDetectionPortraitScaleTolerance = 0.12
        }
    }

 
}

