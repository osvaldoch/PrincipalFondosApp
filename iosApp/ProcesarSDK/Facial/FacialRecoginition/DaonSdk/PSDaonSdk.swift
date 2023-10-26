import Foundation
import PS_Facial_Engine

class PSDaonSdk: NSObject {
    
    public static var instance = PSDaonSdk()
    public var daonSdkDelegate:PSDaonSdkDelegate?
    public var fidoSkd = Fido.shared
    private var documentsLicense:String?
    
    public func initialize(psdkRegistrationMode: PSDKRegistrationMode,
                           completion: @escaping (NSError?, Bool) -> ()){
        initDocumentsLicense()
        self.fidoSkd.initialize (psdkRegistrationMode: psdkRegistrationMode) {
            (errorCode) in
            if (errorCode == .noError || errorCode == .deviceDebug)
            {
                completion(nil, self.fidoSkd.hasValidKeys())
            }
            else
            {
                var message = "Unknown error"
                
                switch errorCode
                {
                case .licenseExpired:           message = "License expired"
                case .licenseNotVerified:       message = "License not verified"
                case .licenseNoAuthenticators:  message = "No licensed authenticators"
                case .deviceSecurityDisabled:   message = "Device passcode/Touch ID/Face ID is not enabled"
                case .deviceCompromised:        message = "Device is jailbroken"
                default:                        message = "Unknown error"
                }
                let error:NSError = NSError(domain: "", code: errorCode.rawValue, userInfo: [ NSLocalizedDescriptionKey: message])
                completion(error, self.fidoSkd.hasValidKeys())
            }
        }
    }
    
    public func removeFidoAuthenticatorAndDeleteUserIfNeeded(userId: String,completion: @escaping (_ userFound:Bool, _ userDeleted:Bool, PSFEError?) -> (Void)){
        self.fidoSkd.removeFidoAuthenticatorAndDeleteUserIfNeeded(userId: userId, completion: completion)
    }
    
    private func initDocumentsLicense(){
        let licenseDevPath = Bundle.main.path(forResource: "daon_doc_license_dev", ofType: "txt")
        
        if let path = Bundle.main.path(forResource: "daon_doc_license", ofType: "txt") {
            do {
                    documentsLicense = try String(contentsOfFile:path, encoding: String.Encoding.utf8)
                    documentsLicense = documentsLicense?.replacingOccurrences(of: "\n", with: "")
                    print(documentsLicense ?? "")
                } catch {
                    print("No se encontro licencia de documentos")
                }
        } else if FileManager.default.fileExists(atPath: licenseDevPath!) {
            do {
                documentsLicense = try String(contentsOfFile:licenseDevPath!, encoding: String.Encoding.utf8)
                documentsLicense = documentsLicense?.replacingOccurrences(of: "\n", with: "")
                print(documentsLicense ?? "")
            } catch {
                print("No se encontro licencia DEV de documentos")
            }
        }
    }
    
    public func getDocumentsLicence()->String{
        return documentsLicense ?? ""
    }
}
