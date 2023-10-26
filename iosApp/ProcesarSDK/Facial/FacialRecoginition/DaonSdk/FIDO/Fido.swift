import UIKit
import DaonFIDOSDK
import PS_Facial_Engine

class Fido: DaonFIDO
{
    static let shared = Fido()
    
    // ADOS Root certificate validation.
    // NOTE. If validation is enabled, make sure this certificate is updated when the server configuration changes.
    let kAdosBASE64EncodedRootCertificate = "MIIFVjCCA0CgAwIBAgIQKuhll9ePQGSsywpelEVwazALBgkqhkiG9w0BAQswRzEVMBMGA1UEAwwMSWRlbnRpdHlYIENBMQ0wCwYDVQQKDAREYW9uMRIwEAYDVQQLDAlJZGVudGl0eVgxCzAJBgNVBAYTAklFMB4XDTE3MDUxODE1MDUyNFoXDTQ3MDUxODE1MDUyNFowRzEVMBMGA1UEAwwMSWRlbnRpdHlYIENBMQ0wCwYDVQQKDAREYW9uMRIwEAYDVQQLDAlJZGVudGl0eVgxCzAJBgNVBAYTAklFMIICIjANBgkqhkiG9w0BAQEFAAOCAg8AMIICCgKCAgEAm9YFCvgKLWtaf+RsNE1gtQgRLFAb7wHugKdn5turSw6Ub++GE/+DV0A9oenqxVt1ZwAvfhUFPm3En60q4eMED2JR+TQMFe5x9ai9GX3y9JM6Oi/ZdzZ0yIFAd0k3VDTGc2lrJhBtBnxslthine9uaLMgY8UB1HKk+4qrVu2VUnBcqCkMPPMvvi9SyxW/pNLOYP68jEPpFArUYgwTAKT6rN5vv/c/Mmw0Epdm6IXSxfdZ6Cr2hxzMKnQdqlJzRa5IH8UqcIbnpi4MHytS57aNsJVQMZbfouQH6poBrmwXbqccG374Hz2DfmGuRcpyA7ypVPnyjzAwivkZJa9sktYrX+faevA1hwRKBnX6tE1fQNinNKy0gkSJkbiN4lvgd1tLnJjCw24bO1zsNLVrLqQ8N7S2vKnqZQIZ7KDUrTX2sxE5HX6tIlJy93Hs6P0M8sLzHhsI3OzFyWzmrJkQHfy1DhCn/5u/KIYHy4jpDZzyQQPpeMvAaookEmAf0HWrFV/KE6xrG76DPRkue9Y1oxtaf7Xa6M4VbaEzvxRsva9QfkP59B2+9WGWb5tVRP+O8YEeJWmyLXXwEfn1XFgdIF3NeOWaCQx3DuSDUgkTbtDmbVf/45PoqPqA9b/Vjxne9PBdmuMHDVHJMJMAw8mWKsgrZipV63EuFlGma2P3NZKJqiMCAwEAAaNCMEAwHQYDVR0OBBYEFGaZUkpQ8Ou4u8BGvtcFc6s73S+WMA8GA1UdEwEB/wQFMAMBAf8wDgYDVR0PAQH/BAQDAgKEMAsGCSqGSIb3DQEBCwOCAgEAYRY8iFwuRiYW4zmuxX5R0PuRWloZ45lp6O3BfemI+8ukJSS6BCSKfd7jdyEgy/hv6J2s/Iriez/fI6NyM+NviZy1cFKjdAbV+Rlv9xR5pZ/JoGFYlZee6XlTtwfV7Sr8fidIJ2SNjkmqpMoEVre5ZL/cKaSmJEsz7ZZyMmniFEmz7QQ8ZWiBCkJ2qxzJbC3afUvk14X5ITDyPgRgs806FQw9V+eNlTsnde8zFP6DaDkeejT/mItSn+ucr+QQTBkJMjbHsDD64H3BcU0iWHKuqRpixxeACL1aXVJYt6t8fVLV8DlIv90ibb6I3kwJC3lJ/SBViST3WdOKHfsWyCEa/Hw06LUgRrujPxEO2ihpuph5C6RX9vkeXUPpeM9f2J7fs6D6ZyvnLYxrpg0u2IIB0LcjGLobMUK3Ev+QokQY6xGB2dWB8NxnjKOPekISfGBk36vQakA9LoK7L1phj4oq56aB50izIibKSBaLFsfYnsoXr5ZHB0R0i+Wmu+MEsr0hNZ3iSaZopCG+j4bjIWKTmqgAHaJYAHlvEfPXBml10941IEusYo9CoaMFxVBYVpqqNukjMoBMggG52AQ5FaRDfkVWljZrBL012hOT1rtAMROv/Bhn5qV4iEkS3H+YKTAYdbXNABbNFj213g0GdQpXvFCsphbusKWZCBLaIQhpVaQ="
    
    // The license can be provided as a file, license.txt included in the bundle, or as an extension.
    //let license = <DAON license. Javascript escaped JSON>
    
    func hasValidKeys() -> Bool
    {
        return DaonFIDO.hasValidKeys()
    }
    
    func initialize(psdkRegistrationMode: PSDKRegistrationMode,
        completion: @escaping (IXUAFErrorCode) -> ()){
       
        if let fidoStatus = DaonFIDO.status(), let fidoAppId = fidoStatus["appId"]{
            PSFacialEngine.getInstance().setAppId(fidoAppId)
        }

        if initialized{
            completion(.noError)
        }else{
            DispatchQueue.global(qos: .userInitiated).async{
                DaonFIDO.setLogging(enabled: true, level: .debug)
                var params : [String : String] = [String: String]()
//                see https://developer.identityx-cloud.com/client/fido/ios/release-notes/rn-history/ for more information
                //params["com.daon.face.liveness.active.type"] = "none"
                params["com.daon.sdk.ados.enabled"] = "true"
                //params["com.daon.face.liveness.passive.type"] = "none"
                params["com.daon.face.liveness.active.type"] = "none"
                //params["com.daon.face.liveness.enroll"] = "true"
                //params["com.daon.finger.sdk.locking"] = "true"
//                if (psdkRegistrationMode == PSDKRegistrationMode.ThreeDAndSelfie){
//                    params["com.daon.face.liveness.active.type"] = "3dface"
//                    params["com.daon.face.liveness.enroll"] = "true"
//                }
                let res = self.initialize(parameters: params)
                DispatchQueue.psfeMainAsync {
                    completion(res)
                }
            }
        }
    }
    
    internal func removeFidoAuthenticators(aaids:[String], completion: ((Error?) -> (Void))?){
        
        var vError:Error?
        var index = 0;
        
        func removeAuthenticator() {
            if let deregMessage = IXUAFMessageWriter.deregistrationRequest(withAaid: aaids[index], application: nil) {
                
                Fido.shared.deregister(message: deregMessage) { (error) in
                    
                    index += 1
                    if let err = error{
                        vError = err
                    }
                    if (index == aaids.count){
                        completion!(vError)
                        return
                    }
                    removeAuthenticator()
                }
            }
        }
        
        removeAuthenticator()
        
       
    }

    public func removeFidoAuthenticatorAndDeleteUserIfNeeded(userId: String,completion: @escaping (_ userFound:Bool, _ userDeleted:Bool, PSFEError?) -> (Void)){
        
        //primero borramos la autenticacion 3d de fido
        removeFidoAuthenticators(aaids: PSFEConstants.authenticators) { (error) in
            
            guard error == nil || (error as NSError?)?.localizedDescription == "uaf_error_user_not_enrolled" else {
                completion(false, false, PSFEError(error: error!))
                return
            }
            
            PSFacialEngine
                .getInstance()
                .psFacialEnginePSFacialServicesDelegate?
                .searchUserAndDelete(userId: userId){ (userFound,userDeleted, error) in
                    guard error == nil else {
                        completion(userFound, userDeleted, PSFEError(error: error!))
                        return
                    }
                    FacialSDKManager.instance.reset(resetFido: false)
                    completion(userFound, userDeleted,nil)
            }
        }
    }
    
    public func resetFido(){
        Fido.reset()
    }
    
    func existsDeviceAuthenticator(authenticatorAaid: String,
                                   completion: @escaping (NSError?, Bool) -> ()) {
        
        Fido.shared.discover { (discoveryData, error) in
            if let error = error {
                completion(NSError(domain: "", code: 1, userInfo: [NSLocalizedDescriptionKey: error.localizedDescription]) , false)
                return
            }
            
            if let availableAuthenticators = discoveryData?.availableAuthenticators
            {
                for authenticator in availableAuthenticators
                {
                    if (authenticator.aaid == authenticatorAaid){
                        completion(nil, true)
                        break
                    }
                }
            }
           
        }
        
    }
}
