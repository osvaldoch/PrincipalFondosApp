#if RELEASE
import PS_FacialUI
import PS_Facial_Engine

extension FacialSDKManager: PSFUChooseDocsInstructionsVCDelegate {
   
    func backStartDocumentsFlowBtnClicked(){
        PSFacialEngine.getInstance().documentsFlow.startDocumentsFlow(transitionDirection: .toLeft)
    }
    
    func getAvaliableCustomDocs() -> [PSFUDocumentType]? {
        guard let docType = PSFacialEngine.getInstance().psfeFacialInfo?.documentType else {
            return nil
        }
        guard let psfuDocumentType = psfeDocumentTypeToPSFUDocumentType(psfeDocType: docType) else {
            return nil
        }
        
        return [psfuDocumentType]
    }
    
    func psfeDocumentTypeToPSFUDocumentType(psfeDocType: PSFEDocumentType) -> PSFUDocumentType? {
        
        switch psfeDocType {
        case .IFE:
            return PSFUDocumentType.ine_ife
        case .BirthCertificate:
            return .acta
        case .FM2:
            return .immigration
        case .MatriculaConsular:
            return .consular
        case .Pasaporte:
            return .passport
        case .AnyDoc:
            return .anyDoc
        @unknown default:
            #if DEBUG
            fatalError("@unknown default")
            #else
            return nil
            #endif
        }
    }
    
    func onIneSelected() {
        PSFacialEngine.getInstance().documentsFlow.handleIneSelected()
    }
    func onConsularSelected() {
        PSFacialEngine.getInstance().documentsFlow.handleConsularSelected()
    }
    func onImmigrationSelected() {
        PSFacialEngine.getInstance().documentsFlow.handleImmigrationSelected()
    }
    func onPassportSelected() {
        PSFacialEngine.getInstance().documentsFlow.handlePassportSelected()
    }
    func onActaSelected() {
        PSFacialEngine.getInstance().documentsFlow.handleActaSelected()
    }
    
}
#endif
