import PS_Facial_Services
import PS_Facial_Engine
import PS_Core

extension FacialSDKManager: PSFSFacialServicesDelegate {
    
    func getEncyptedText(text: String) -> String {
        let encryptWithCore = PSEncryptDecript.encrypt(data: text, keyDataString: PSCore.shared.passwordComplete) ?? ""
        
        return encryptWithCore.base64EncodedString
    }
    
    func configureServices() {
        
        PSFSConfigManager
            .shared
            .setup()
            .withDaonServerUrl(daonServerUrl: PSFacialEngine.getInstance().getServerUrl())
            .withUser(daonUser: PSFacialEngine.getInstance().getSettingsString(.onboardingServerUsername)!)
            .withPassword(daonPassword: PSFacialEngine.getInstance().getSettingsString(.onboardingServerPassword)!)
            .build()
    }
    

    public func getServerUrl() -> String{
        return PSFacialEngine.getInstance().getServerUrl()
    }
 
    public func getUserIdx() -> String {
         return PSFacialEngine.getInstance().getIdxUserId()
    }
    
    public func getIdChekcs() -> String {
        return PSFacialEngine.getInstance().getIdCheckId()
    }
    

}
