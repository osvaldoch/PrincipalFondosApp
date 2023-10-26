import UIKit
import DaonFIDOSDK
import PS_Facial_Services
import PS_Facial_Engine


public protocol FidoAuthenticationTaskDelegate {
    func onFidoAuthenticationSuccess()
    func onFidoAuthenticationCancelled()
    func onFidoAuthenticationFailed(_ error : Error)
    func get3DViewControllerForAuth(_ isRegistrationContext:Bool) -> UIViewController
    func show3DViewControllerForAuth()
}

class FidoAuthenticationTask: NSObject, IXUAFDelegate
{
    // MARK:- Properties
    
    private let userId : String
    private let applicationId : String
    private let policyId : String
    private let desc : String
    private let delegate : FidoAuthenticationTaskDelegate
    private var authenticationRequest : PSFSCreateAuthenticationResponse?
    private var authenticationOperation : IXUAFOperation?
    let fidoSdk = Fido.shared
    // MARK:- Initializers
    
    init (userId : String, applicationId : String, policyId : String, description : String, delegate : FidoAuthenticationTaskDelegate)
    {
        self.userId        = userId
        self.applicationId = applicationId
        self.policyId      = policyId
        self.desc          = description
        self.delegate      = delegate
    }
    
    // MARK:- Actions
    
    private func updateAuthRegister(serviceLibrary:PSFacialServiceViewModel,authenticationResponse:String?){
        // Notify SDK and calling activity of success or failure
        self.authenticationRequest!.fidoAuthenticationResponse = authenticationResponse
        serviceLibrary.onSuccessUpdateAuthenticationRegister = { (_ response:PSFSUpdateAuthenticationResponse) -> Void in
            self.fidoSdk.delegate = nil
            // "Success" means the server has responded, but it may have responded with an error code
            self.fidoSdk.notifyResult(message: response.fidoAuthenticationResponse, code: response.fidoResponseCode)
            if (response.fidoResponseCode == IUafServerResponseCodes.OPERATION_COMPLETED.rawValue){
                DobsLogUtils.logDebug("FIDO authentication succeeded")
                self.delegate.onFidoAuthenticationSuccess()
            }else{
                // Server responded with error code
                DobsLogUtils.logError(AppErrorCodes.fidoAuthenticationServerError.localizedDescription + ": " + response.fidoResponseMsg + ", code: " + String(response.fidoResponseCode))
                self.delegate.onFidoAuthenticationFailed(PSDKError(errorType: .NetworkFailed).nsError)
            }
        }
        
        serviceLibrary.onServiceError = { (error) -> Void in
            self.fidoSdk.delegate = nil
            //PSDaonSdk.instance.daonSdkDelegate?.eventAnalitycs(flow: PSDaonSdk.instance.daonSdkDelegate?.getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
            DobsLogUtils.logError("Finalise authentication on server error: \(error.localizedDescription)")
            self.fidoSdk.notifyResult(message: self.authenticationRequest!.fidoAuthenticationResponse!, code: IUafServerResponseCodes.INTERNAL_SERVER_ERROR.rawValue)
            self.delegate.onFidoAuthenticationFailed(error)
        }

        serviceLibrary.performUpdateAuthenticationRegister(fidoAuthenticationResponse: self.authenticationRequest!.fidoAuthenticationResponse!, authenticationRequestId: self.authenticationRequest!.id)
    }
    
    func start(){

        //let core = PSFacialEngine.getInstance()
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessAuthenticationRegister = { (_ response:PSFSCreateAuthenticationResponse) -> Void in
            DobsLogUtils.logDebug("Create authentication request success. ID: " + response.id + ". Perform FIDO SDK authentication.")
            self.authenticationRequest = response
            self.fidoSdk.delegate = self
            self.fidoSdk.authenticate(message: response.fidoAuthenticationRequest, completion: { (authenticationResponse, error) in
                if let err = error{
                    self.fidoSdk.delegate = nil
                    if (err._code == IXUAFErrorCode.userCancelled.rawValue){
                        self.delegate.onFidoAuthenticationCancelled()
                    }else{
                        DobsLogUtils.logError("FIDO Authentication Error: " + err.localizedDescription + ", code: " + String((err as NSError).code))
                        self.delegate.onFidoAuthenticationFailed(err)
                    }
                }else{
                    self.updateAuthRegister(serviceLibrary: serviceLibrary,authenticationResponse:authenticationResponse)
                }
            })



        }

        serviceLibrary.onServiceError = { (error) -> Void in
            DobsLogUtils.logError("Create authentication reques error: \(error.localizedDescription)")
            //PSDaonSdk.instance.daonSdkDelegate?.eventAnalitycs(flow: PSDaonSdk.instance.daonSdkDelegate?.getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
            self.delegate.onFidoAuthenticationFailed(error)
        }

        serviceLibrary.performAuthenticationRegister(userId: self.userId, applicationId: self.applicationId, policyId: self.policyId, description: self.desc, type: "FI")
    }
    
    // MARK:- FIDO SDK delegate
    
    func operation(_ operation: IXUAFOperation, willAllowAuthenticators authenticators: [[IXUAFAuthenticator]]) -> [[IXUAFAuthenticator]]?
    {
        self.authenticationOperation = operation
        return authenticators
    }
    
    func operation(_ operation: IXUAFOperation, shouldVerifyMessage message: String)
    {
        let authRequest                           = PSFSCreateAuthenticationResponse()
        authRequest.id                            = self.authenticationRequest!.id
        authRequest.fidoAuthenticationResponse    = message
        
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessUpdateAuthenticationRegister = { (_ response:PSFSUpdateAuthenticationResponse) -> Void in
            operation.notify!(withResult: response.fidoAuthenticationResponse, code: response.fidoResponseCode)
        }
        
        serviceLibrary.onServiceError = { (error) -> Void in
            //PSDaonSdk.instance.daonSdkDelegate?.eventAnalitycs(flow: PSDaonSdk.instance.daonSdkDelegate?.getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
            DobsLogUtils.logError("Validate capture data error: \(error.localizedDescription)")
            self.delegate.onFidoAuthenticationFailed(error)
        }

        serviceLibrary.performUpdateAuthenticationRegister(fidoAuthenticationResponse: authRequest.fidoAuthenticationResponse!, authenticationRequestId: authRequest.id)
        
    }
    
    
    func operation(_ operation: IXUAFOperation, shouldUseCollectionViewControllerForUserVerification method: Int, context: DASAuthenticatorContext) -> DASAuthenticatorCollectorInfo? {
        
        
        var collectorInfo : DASAuthenticatorCollectorInfo?
        var vc : UIViewController?
        
        if method == USER_VERIFY_FACEPRINT{
            PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext = context
            vc = self.delegate.get3DViewControllerForAuth(context.isRegistration)
        }else{
            return nil
        }
        
        if vc != nil
        {
            collectorInfo = DASAuthenticatorCollectorInfo(viewController: vc, clientWillPresent: true)
            
            delegate.show3DViewControllerForAuth()
        }
        return collectorInfo
    }
}
