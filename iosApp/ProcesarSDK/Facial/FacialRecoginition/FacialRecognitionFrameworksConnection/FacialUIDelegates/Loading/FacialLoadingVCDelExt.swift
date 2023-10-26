import Foundation
import UIKit
import PS_FacialUI
import PS_Facial_Engine

extension FacialSDKManager : PSLoadingVCDelegate{
    
    func willAppearLoading() {
        print("willAppearLoading")
    }
    
    func willDisappearLoading() {
        print("WillDisappearLoading")
    }
}
