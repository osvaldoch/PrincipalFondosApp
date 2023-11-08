
import SwiftUI
import shared
import PS_FacialUI
import PS_Facial_Engine
import PS_Facial_Services
import PS_Core
import PS_Auto_Transfer

struct ComposeView: UIViewControllerRepresentable,
                    PSFacialEngineRegistrationFlowDelegate,
                    PSFacialEngineAuthFlowDelegate,
                    PSFacialEngineLogsDelegate,
                    PSFacialEngineAnalitycsDelegate {
    
    func onDocumentCaptured(capturedImagesBase64: [String?], documentType: PS_Facial_Engine.PSFEDocumentType?) {
                
    }
    
    func onRegistrarionFlowFinished(capturedImagesBase64: [String?], documentType: PS_Facial_Engine.PSFEDocumentType?, psfeImageResult: PS_Facial_Engine.PSFEImageResult?, error: PS_Facial_Engine.PSFEError?) {
            
    }
    
    func onAuthenticationFlowFinished(_ selfie: UIImage?, error: PS_Facial_Engine.PSFEError?) {
        
    }
    
    func performSendLogsFacial(curp: String, idLog: String?, statusLog: String?, responseLog: String?, operatingSystem: String, typeProcess: Int) {
        
    }
    
    func eventAnalitycs(flow: String, event: PS_Facial_Engine.PSFEAnalitycsEvent, error: Error?, cveDoc: String?) {
        
    }
    
    func makeUIViewController(context: Context) -> UIViewController {
        Main_iosKt.MainViewController()
    }

    func facial(view: UIViewController) {

    }
    
    func updateUIViewController(_ uiViewController: UIViewController, context: Context) {
        PSFacialEngine.getInstance().psfeProcesarFlow = MyCustomFlowManager()
        FacialSDKManager.instance.initialize(appName: "PricipalAforeApp",
                                             psfeRegistrationMode: PSFERegistrationMode.OnlySelfie) { (error, hasValidKeys) -> (Void) in
            /*if let error = error {
             return
             }
             if (!hasValidKeys){
             }*/
            FacialSDKManager.instance.initWithViewController(viewController: uiViewController,
                                                                     info: PSFEFacialInfo(userId: "CEHO950625HHGSRS02",
                                                                                          firstName: "CESPEDES",
                                                                                          lastName: "HERNADEZ",
                                                                                          expedientType: "",
                                                                                          minorId: ""),
                                                                     facialMode: .Validation,
                                                                     psFacialEngineAuthFlowDelegate: self,
                                                                     psFacialEngineRegistrationFlowDelegate: self)
        }
    }

}

struct ContentView: View {
    var body: some View {
        ComposeView()
                .ignoresSafeArea(.keyboard) // Compose has own keyboard handler
    }
}

