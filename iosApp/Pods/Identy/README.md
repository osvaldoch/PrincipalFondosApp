IDENTY  SDK

#Installation

   The IDENTY SDK  is compatible with Apple iOS version 10.0 and above.
        IDENTY SDK is available through CocoaPods.
⁃    Install cocoapods  

        $ sudo gem install cocoapods   
⁃    Create Pod file inside project workspace
   
        $ pod init
⁃    To install sdk, simply add the following to your Podfile:
    
        # Uncomment the next line to define a global platform for your project
        # platform :ios, '11.0'
        plugin 'cocoapods-art', :sources => [
         'cocoapods-identy-finger'
        ]
        target 'IdentyProject' do
        #use_frameworks!
        pod 'Identy','3.0.2.0'
        end

⁃    You will need to access cocoa pods private repo to get started.

#Cocoapods

1.    Set your repository credentials. The first step is to add the credentials received from Identy into  your .netrc file. Navigate to your home folder and create a file called .netrc

          cd ~/
          vi .netrc

       Add the credentials in the following format:

          machine identy.jfrog.io
          login ${provided_username}
          password ${provided_encrypted_password}

2. Install cocoapods-art

        $ sudo gem install cocoapods-art 

3. Add repository to the local

        $ pod repo-art add cocoapods-identy-finger "https://identy.jfrog.io/identy/api/pods/cocoapods-identy-finger"

4. Update the pod repo in need  to use the updated SDK version.

         $ pod repo-art update cocoapods-identy-finger 
         $ pod install
  
#Set Enable Bitcode to NO in Build settings.

#Features
        Initialize SDK with params mentioned in document and perform -
        Enroll, Enroll with Identy User
        Verify, Verify with Identy User
        Capture
        Enroll With Templates
        Verify With Templates

#Usage

    let bundlePath = Bundle.main.path(forResource: "${license_file_name}", ofType: "lic")!
    let instance = IdentyFramework.init(with: bundlePath , localizablePath: Bundle.main.path(forResource: "en", ofType: "lproj"), table: "Main")
    
    // Enroll
    instance.enroll(viewcontrol: self){ (success, responseModel, errorMessage) in if success {  print(success)  }else{  print("errorMessage\(errorMessage)")   }
    }
     // Verify
    instance.verify(viewcontrol: self){ (success, responseModel, errorMessage) in if success {    print(success)  }else{  print("errorMessage\(errorMessage)")  }

    


