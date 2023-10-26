import Foundation

open class PSDKError {
    
    public enum PSDKErrorType : Int{
        case SpoofLivenessProofDetected = 871010
        case Spoof3dDetected = 333
        case DocumentFaceNoMatch = 11009
        case LivenessProofFailed = 920917
        case LivenessServerProofFailed = 332
        case NetworkFailed = 871017
        case StartAuthFido = 871012
        case RequestError = 871013
        case RequestDecodeError = 871014
        case InvalidApplicationState = 871019
        case LivenessNoChallenges = 871015
        case LivenessCouldNotStartCamera = 50
        case FailedToCreateVideoDigest = 871016
        case LivenessVideoCaptureTimeout = 320
        case CurpEmpty = 871018
        case GenericTypeError = 377337
        case NoPasscodeEnabled = 9
    }
    
    public var message = ""
    public var nsError = NSError() //PSFacial_UI
    public var errorType: PSDKErrorType? = nil
    
    public init() {
        print("init")
    }
   
    
    public init (error: Error){
        errorType = .GenericTypeError
        initWith(error: error)
    }
    
    public init(errorType: PSDKErrorType) {
        self.errorType = errorType
        initWith(error: NSError(domain: "", code: errorType.rawValue, userInfo: [ NSLocalizedDescriptionKey: ""]))
    }
    
    private func initWith(error: Error){
        if let errorFromStringsFile = PSDaonSdk.instance.daonSdkDelegate?.getDasErrorsDict(errorCode: "\(error._code)"){
            self.message = errorFromStringsFile
            self.nsError = NSError(domain: "", code:error._code , userInfo: [ NSLocalizedDescriptionKey: errorFromStringsFile])
        }
        else{
            if (error as NSError).code == 0{
                self.nsError = NSError(domain: "", code: 0, userInfo: [ NSLocalizedDescriptionKey: error.localizedDescription])
                self.message = error.localizedDescription
            }else{
                let unkonwErrorMessage = PSDaonSdk.instance.daonSdkDelegate!.getDasErrorsDict(errorCode: "377337")!
                self.nsError = NSError(domain: "", code: (error as NSError).code , userInfo: [ NSLocalizedDescriptionKey: unkonwErrorMessage])
                self.message = unkonwErrorMessage
            }
        }
    }
    
    
   
}
