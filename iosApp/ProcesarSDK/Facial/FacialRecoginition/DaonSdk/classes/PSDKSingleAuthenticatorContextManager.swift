import Foundation
import DaonAuthenticatorSDK


public class PSDKSingleAuthenticatorContextManager: NSObject{
    
    public static var intance: PSDKSingleAuthenticatorContextManager = PSDKSingleAuthenticatorContextManager()
    
    weak var singleAuthenticatorContext : DASAuthenticatorContext?
    
    public func completeCaptureWithErrorCode(errorCode: Int){
        if let authError = DASAuthenticatorError(rawValue: errorCode)
        {
            singleAuthenticatorContext?.completeCapture(error: authError)
        }
    }
}
