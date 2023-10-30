#if RELEASE
import PS_Facial_Engine

extension FacialSDKManager: PSFacialEngineMainAppDelegate {
    
    func on3DRegistrationSuccess() {
       PSFacialEngine.getInstance().psfeProcesarFlow.handleOn3DSuccess()
    }
    
    func on3DRegistrationFailed(_ error: PSFEError) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOn3DError(error: error.nsError)
    }
    
    func onDocumentsCapturedSuccess(){
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnDocumentsCapturedSuccess()
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .DocumentsRegister, error: nil, cveDoc: nil)
    }
    func onDocumentsError(_ error: PSFEError){
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnDocumentsError(error.nsError)
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .DocumentAttempt, error: nil, cveDoc: nil)
    }
    
    func onRandomLivenessFailed(error:PSFEError) {
         PSFacialEngine.getInstance().psfeProcesarFlow.handleOnRandomLivenessError(error: error)
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .LifeTestAttempt, error: nil, cveDoc: nil)
    }

    func onRandomLivenessSuccess() {
    
        PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .RandomOk, error: nil,cveDoc: nil)
        
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnRandomLivenessSucces()
    }
    
    func on3DAuthFailed(_ error: PSFEError){
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOn3DError(error: error.nsError)
    }
    func on3DAuthCancelled(){
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOn3DAuthCancelled()
    }
    func on3DAuthSuccess() {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOn3DSuccess()
    }
    
    func onReviewSuccess() {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnReviewSuccess()
    }
    
    func onReviewFailed(_ error: Error) {
        PSFacialEngine.getInstance().psfeProcesarFlow.handleOnReviewError(error)
    }
}
#endif
