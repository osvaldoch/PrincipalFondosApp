import SwiftUI
import shared

struct ContentView: View {
    let greet = Greeting().greet()
#if RELEASE
    let sdk = PSSdkInitialize()
#endif

    init() {
       // sdk.setupCore()
    }

	var body: some View {
		Text(greet)
	}
}

struct ContentView_Previews: PreviewProvider {
	static var previews: some View {
		ContentView()
	}
}
