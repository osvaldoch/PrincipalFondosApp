#if RELEASE
import UIKit
import DaonFIDOSDK
import PS_Facial_Engine
import PS_Facial_Services

public enum SdkStageReached : Int{
    case tutorial                       = 0
    case preRegistration                = 1
    case userIdEntered                  = 2
    case registrationChallengeCreated   = 3
    case fidoRegistrationComplete       = 4
    case documentRegistrationComplete   = 5
    case livenessCheckComplete          = 6
    case livenessCheckFailed            = 7
    case evaluationComplete             = 8
    case evaluationCheckFailed          = 9
}
public enum PSDKAnalitycsEvent: Int {
    case StartWelcome           = 1
    case ContinueWelcome        = 2
    case StartMainTutorial      = 3
    case ContinueMainTutorial   = 4
    case StartLiveness3D        = 5
    case ClickHelpLiveness3D    = 6
    case Liveness3DNearOk       = 7
    case SelfiePreview          = 8
    case ClickContinueSelfie    = 9
    case SelectDocument         = 10
    case ClickContinueFrontDoc  = 11
    case StartFrontDoc          = 12
    case ClickContinueBackDoc   = 13
    case StartActaDoc           = 14
    case ClickContinueActa      = 15
    case ClickHelpRandom        = 16
    case StartRandom            = 17
    case RandomOk               = 18
    case FacialSelfieValidation = 19
    case DocumentsRegister      = 20
    case FacialSelfieAttempt    = 22
    case DocumentAttempt        = 23
    case LifeTestAttempt        = 24
    case Default                = 0
}

public protocol FidoRegistrationTaskDelegate
{
    func onFidoStartRegistration()
    func onFidoRegistrationSuccess()
    func onFidoRegistrationFailed(_ error : Error)
    func get3DViewController() -> UIViewController
    func show3DViewController()
    func get3DViewController(_ isRegistrationContext:Bool) -> UIViewController
}

class FidoRegistrationTask: NSObject, IXUAFDelegate
{
    // MARK:- Properties
    private let serviceLibrary = PSFacialServiceViewModel()
    private let userId : String
    private let firstName : String
    private let lastName : String
    private let applicationId : String
    private let policyId : String
    private let delegate : FidoRegistrationTaskDelegate
    private var registrationChallenge : PSFSCreateRegistrationChallengeResponse?
    private var registrationOperation : IXUAFOperation?
    private var multiAuthenticatorCreator : (DASMultiAuthenticatorContext) -> (UIViewController)
    //private var viewController: UIViewController?
    private var customFaceAuthenticatorController:UIViewController?
    private let fidoSdk = Fido.shared
    private var countAttemptsFido = 0
    private let strCode = ", code: "
    
    // MARK:- Initializers
    
    init (userId : String, firstName : String, lastName : String, applicationId : String, policyId : String, delegate : FidoRegistrationTaskDelegate, multiAuthenticatorCreator : @escaping (DASMultiAuthenticatorContext) -> (UIViewController))
    {
        self.userId                    = userId
        self.firstName                 = firstName
        self.lastName                  = lastName
        self.applicationId             = applicationId
        self.policyId                  = policyId
        self.delegate                  = delegate
        self.multiAuthenticatorCreator = multiAuthenticatorCreator
    }
    
    // MARK:- Actions
    
    func start()
    {
        DobsLogUtils.logDebug("Attempt to create registration request on server.")
        
        //self.viewController = viewController
        self.startDaonRegistrationProcess()
        
    }
    
    
    
    private func startDaonRegistrationProcess(){
        
        self.serviceLibrary.onSuccessCreateRegistrationChallengeResponse = { (_ response:PSFSCreateRegistrationChallengeResponse) -> Void in
            DobsLogUtils.logDebug("Get registration challenge success. Registration ID: " +
                response.registrationId + ", user ID: " + response.userId + ". Perform FIDO SDK registration.")
            PSDaonSdk.instance.daonSdkDelegate?.setStageReached(.registrationChallengeCreated)
            PSDaonSdk.instance.daonSdkDelegate?.setIdxUserId(response.userId)
            self.registrationChallenge = response
            self.delegate.onFidoStartRegistration()
            self.fidoSdk.delegate = self
            
            func fidoRegister(){
                func removeAuth(){
                    self.fidoSdk.removeFidoAuthenticators(aaids: PSFEConstants.authenticators) {
                        (error) -> (Void) in
                        self.countAttemptsFido += 1
                        fidoRegister()
                    }
                }
                
                func serviceError(){
                    self.serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
                        //PSDaonSdk.instance.daonSdkDelegate?.eventAnalitycs(flow: PSDaonSdk.instance.daonSdkDelegate?.getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
                        DobsLogUtils.logError("Finalise registration on server error: \(err.localizedDescription)")
                        self.fidoSdk.notifyResult(message: self.registrationChallenge!.fidoRegistrationResponse, code: IUafServerResponseCodes.INTERNAL_SERVER_ERROR.rawValue)
                        self.customFaceAuthenticatorController?.view.removeFromSuperview()
                        self.customFaceAuthenticatorController?.removeFromParent()
                        PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext = nil
                        self.delegate.onFidoRegistrationFailed(PSDKError(error: err).nsError)
                    }
                }
                
                func successUploadBiometric(){
                    self.serviceLibrary.onSuccessUploadBiometricDataToRegistrationChallenge = { (_ response:PSFSUpdateRegistrationChallengeResponse) -> Void in
                        // "Success" means the server has responded, but it may have responded with an error cod
                        self.fidoSdk.delegate = nil
                        self.fidoSdk.notifyResult(message: response.fidoRegistrationResponse, code: response.fidoResponseCode)
                        
                        if (response.fidoResponseCode == IUafServerResponseCodes.OPERATION_COMPLETED.rawValue){
                            // Server responded with OK status code
                            DobsLogUtils.logDebug("FIDO registration succeeded")
                            self.customFaceAuthenticatorController?.view.removeFromSuperview()
                            self.customFaceAuthenticatorController?.removeFromParent()
                            PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext = nil
                            self.delegate.onFidoRegistrationSuccess()
                        }else{
                            // Server responded with error code
                            
                            DobsLogUtils.logError(PSFEAppErrorCodes.fidoRegistrationServerError.localizedDescription + ": " + "\(String(describing: response.fidoResponseMsg))" + self.strCode + String(response.fidoResponseCode))
                            
                            let fidoError = NSError(domain: "", code: PSFEAppErrorCodes.fidoRegistrationServerError._code, userInfo: [NSLocalizedDescriptionKey : response.fidoResponseMsg])
                            self.customFaceAuthenticatorController?.view.removeFromSuperview()
                            self.customFaceAuthenticatorController?.removeFromParent()
                            self.delegate.onFidoRegistrationFailed(PSDKError(error: fidoError).nsError)
                            PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext = nil
                        }
                    }
                }
                
                self.fidoSdk.register(message: self.registrationChallenge!.fidoRegistrationRequest, completion: { (registrationResponse, error) in
                    
                    if let error = error, (error.localizedDescription == "uaf_error_no_suitable_authenticator") &&
                        self.countAttemptsFido <= 1 {
                        removeAuth()
                        return
                    }
                    
                    self.registrationOperation = nil
                    
                    if let err = error{
                        
                        self.fidoSdk.delegate = nil
                        DobsLogUtils.logError("FIDO Registration Error: " + err.localizedDescription + self.strCode + String((err as NSError).code))
                        PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext = nil
                        self.delegate.onFidoRegistrationFailed(PSDKError(error: err).nsError)
                        
                    }else{
                        
                        successUploadBiometric()
                        
                        serviceError()
                        
                        // Notify SDK and calling object of success or failure
                        self.registrationChallenge!.fidoRegistrationResponse = registrationResponse!
                        self.serviceLibrary.performUploadBiometricDataToRegistrationChallenge(id: self.registrationChallenge!.id, status: "PENDING", fidoRegistrationResponse: self.registrationChallenge!.fidoRegistrationResponse)
                        
                    }
                })
            }
            
            fidoRegister()
        }
        
        self.serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            DobsLogUtils.logError("Create documents error: " + err.localizedDescription + self.strCode + String(err._code))
            //PSDaonSdk.instance.daonSdkDelegate?.eventAnalitycs(flow: PSDaonSdk.instance.daonSdkDelegate?.getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            self.delegate.onFidoRegistrationFailed(PSDKError(error: err).nsError)
        }
        
        self.serviceLibrary.performCreateRegistrationChallenge(applicationId: self.applicationId, policyId: self.policyId, userId: self.userId, firstName: self.firstName, lastName: self.lastName)
    }
    
    
    // MARK:- FIDO SDK delegate
    
    func operation(_ operation: IXUAFOperation, willAllowAuthenticators authenticators: [[IXUAFAuthenticator]]) -> [[IXUAFAuthenticator]]?
    {
        
        print("LLEGA AL FILTRO")
         self.registrationOperation = operation
         
         // Only return the group that has the registrationAaid
         for group in authenticators {
            if group[0].aaid == "D409#9201" {
                return [group]
            }
         }
         
         return nil
    }
    
    func operation(_ operation: IXUAFOperation, shouldVerifyMessage message: String)
    {
        self.registrationChallenge!.fidoRegistrationResponse  = message
        
        
        self.serviceLibrary.onSuccessUploadBiometricDataToRegistrationChallenge = { (_ response:PSFSUpdateRegistrationChallengeResponse) -> Void in
            // "Success" means the server has responded, but it may have responded with an error code
            operation.notify!(withResult: response.fidoRegistrationResponse, code: response.fidoResponseCode)
        }
        
        self.serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            //PSDaonSdk.instance.daonSdkDelegate?.eventAnalitycs(flow: PSDaonSdk.instance.daonSdkDelegate?.getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            self.delegate.onFidoRegistrationFailed(err)
        }
        self.serviceLibrary.performUploadBiometricDataToRegistrationChallenge(id: self.registrationChallenge!.id, status: "PENDING", fidoRegistrationResponse: self.registrationChallenge!.fidoRegistrationResponse)
        
    }
    
    func operation(_ operation: IXUAFOperation, shouldUseViewControllerForAuthenticatorType type: DASAuthenticatorPolicyType, context: DASMultiAuthenticatorContext) -> DASMultiAuthenticatorCollectorInfo?
    {
        let collectorInfo = DASMultiAuthenticatorCollectorInfo()
        collectorInfo.clientIsResponsibleForPresentation = true
        collectorInfo.collectionViewController = self.multiAuthenticatorCreator(context)
        
        return collectorInfo
    }

    
    func operation(_ operation: IXUAFOperation, shouldUseCollectionViewControllerForUserVerification method: Int, context: DASAuthenticatorContext) -> DASAuthenticatorCollectorInfo? {
        var collectorInfo : DASAuthenticatorCollectorInfo?
        if method == USER_VERIFY_FACEPRINT{
            PSDKSingleAuthenticatorContextManager.intance.singleAuthenticatorContext = context
            customFaceAuthenticatorController = self.delegate.get3DViewController(context.isRegistration)
        }else{
            return nil
        }
        if let viewController = customFaceAuthenticatorController{
            collectorInfo = DASAuthenticatorCollectorInfo(viewController: viewController, clientWillPresent: true)
            self.delegate.show3DViewController()
        }
        return collectorInfo
    }
}
#endif
