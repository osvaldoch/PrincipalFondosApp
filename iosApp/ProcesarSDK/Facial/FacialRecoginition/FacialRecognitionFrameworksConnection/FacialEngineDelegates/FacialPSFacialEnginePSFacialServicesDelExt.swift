import PS_Facial_Services
import PS_Facial_Engine
extension FacialSDKManager: PSFacialEnginePSFacialServicesDelegate {
    
    
    func searchUserAndDelete(userId: String, completion: @escaping (Bool, Bool, Error?) -> (Void)) {
        
        PSFSUserUtil.searchUserAndDelete(userId: userId){ (userFound,userDeleted, error) in
            if (error != nil) {
                completion(userFound,userDeleted, error)
                return
            }
            completion(userFound,userDeleted, nil)
        }
    }
    
    func uploadDocuments(userId: String,
                         idCheck: String,
                         psfeImageDocuments: [PSFEImageDocument],
                         capturedTime: Date,
                         completion: @escaping (_ error: Error?)->()) {
        
        
        var documentImages: [PSFSSDocumentImage] = []
        for psfeImageDocument in psfeImageDocuments {
            documentImages.append(PSFSSDocumentImage(imageFormat: "JPG",
                                                    value: psfeImageDocument.base64,
                                                    type: psfeImageDocument.type.rawValue))
        }
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        
        serviceLibrary.onSuccessAddDocumentToTheIdCheck = { (_ frontDocument:PSFSCreateDocumentResponse) -> Void in
            
            completion(nil)
        }
        
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            DobsLogUtils.logError("Create documents error: " + err.localizedDescription + ", code: " + String(err._code))
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            completion(err)
        }
        
        serviceLibrary.perfomAddDocumentToTheIdCheck(
            userId: userId,
            idcheckid: idCheck,
            capture: capturedTime,
            processedImageBase64: nil,
            images: documentImages)
        
    }
    
    func uploadTwoSidedDocuments(userId: String,
                                 idCheck: String,
                                 captureType: String,
                                 capturedTime: Date,
                                 imagesBase64: [String],
                                 sides: Int,
                                 completion: @escaping (_ error: Error?)->()){
        
        guard let imagesArray = createImageObjectsForTwoSidedDocuments(captured: capturedTime,
                                                                       imagesBase64: imagesBase64,
                                                                       sides: sides) else { return }
        guard let request = createDocumentRequest(captureType: captureType, captured: capturedTime, images: imagesArray) else { return }
        uploadTwoSidedDocuments(userId: userId,
                                idCheck: idCheck,
                                request: request,
                                capturedTime: capturedTime,
                                completion: completion)
        
    }
    
    private func createImageObjectsForTwoSidedDocuments(captured: Date,
                                                        imagesBase64: [String],
                                                        sides: Int) ->  [Image]? {
        
        guard (sides == 1 || sides == 2) && // los documentos solo pueden tener 1 o dos lados
                imagesBase64.count == sides * 2 else { // por cada lado de los coumentos se envian 2 imagenes
            #if DEBUG
            fatalError("Incorrect number of images")
            #else
            return nil
            #endif
        }
        
        var subtypes: [String] = []
        var types: [String] = []
        for _ in 1...sides {
            let processedUnprocessed = ["PROCESSED", "UNPROCESSED"]
            let fronts = ["FRONT", "FRONT"]
            subtypes.append(contentsOf: processedUnprocessed)
            types.append(contentsOf: fronts)
            if sides == 2 {
                let backs = ["BACK","BACK"]
                types.append(contentsOf: backs)
            }
        }
        var imagesArray: [Image] = []
        for (index, imageBase64) in imagesBase64.enumerated() {
            let imageObject = Image(
                captured: captured.toString(format: PSServerConstants.serverDateFormat),
                sensitiveData: SensitiveData(
                    imageFormat: "JPG",
                    value: imageBase64
                ),
                subtype: subtypes[index],
                type: types[index]
            )
            imagesArray.append(imageObject)
        }
    
        
        return imagesArray
    }
    
    private func createDocumentRequest(captureType: String, captured: Date, images: [Image]) -> PSFSDocumentRequest? {
        
        let clientCaptureObject = ClientCapture(
            images: images
        )

        let captureRequestObject = PSFSDocumentRequest(
            captureType: captureType,
            captured: captured.toString(format: PSServerConstants.serverDateFormat),
            clientCapture: clientCaptureObject
        )

        return captureRequestObject
    }

    
    private func uploadTwoSidedDocuments(userId: String,
                                 idCheck: String,
                                 request: PSFSDocumentRequest,
                                 capturedTime: Date,
                                 completion: @escaping (_ error: Error?)->()) {
        
        
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        
        serviceLibrary.onSuccessAddDocumentToTheIdCheck = { (_ frontDocument:PSFSCreateDocumentResponse) -> Void in
            
            completion(nil)
        }
        
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            DobsLogUtils.logError("Create documents error: " + err.localizedDescription + ", code: " + String(err._code))
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            completion(err)
        }

        
        
        serviceLibrary.perfomrAddTwoSidedDocumentToIdCheck(userId: userId,
                                                           idCheckId: idCheck,
                                                           psfsDocumentRequest: request)
        
    }
    
    func uploadDocument(userId: String,
                        idCheck: String,
                        docBase64: String,
                        capturedTime: Date,
                        completion: @escaping (_ error: Error?)->()) {
        
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        
        serviceLibrary.onSuccessAddDocumentToTheIdCheck = { (_ frontDocument:PSFSCreateDocumentResponse) -> Void in
            
            completion(nil)
        }
        
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            DobsLogUtils.logError("Create documents error: " + err.localizedDescription + ", code: " + String(err._code))
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc:nil)
            completion(err)
        }
        
        serviceLibrary.perfomAddDocumentToTheIdCheck(
            userId: userId,
            idcheckid: idCheck,
            capture: capturedTime,
            processedImageBase64: docBase64,
            images: nil)
        
    }
    
    func getUserIdxId(userId: String, completion: @escaping (_ userIdxId: String?,_ error: Error? ) -> (Void)){
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        serviceLibrary.onSuccessSearchUser = { (_ response:PSFSGetUserResponse) -> Void in
            if let userIdxId = response.items?[0].id{
                completion(userIdxId, nil)
            }
            else
            {
                completion(nil, NSError(domain: "", code: 101089, userInfo: [ NSLocalizedDescriptionKey: "No se encontro usuario en daon al intentar obtener el idx"]))
            }
        }
        
        serviceLibrary.onServiceError = { (error) -> Void in
           //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
            completion(nil, error)
        }
        
        serviceLibrary.perfomSearchUser(userId: userId)
    }
    
    func createIdCheck(userIdxId: String,
                       livenessPolicyName: String,
                       idCheckReferenceId: String,
                       completion: @escaping (_ idCheckId: String?, _ error: Error?) -> (Void)){
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        
        serviceLibrary.onSuccessCreateIDCheckWithLivenessPolicy = { (_ idCheck:PSFSCreateIdCheckResponse) -> Void in
            
            completion(idCheck.id, nil)
            
        }
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc:nil)
            completion(nil, err)
        }
        serviceLibrary
            .performCreateIDCheckWithLivenessPolicy(userID: userIdxId,
                                                    livenessPolicyName: livenessPolicyName,
                                                    guid: idCheckReferenceId)
        
    }
    
    func checkIfBestFrameExists(completion: @escaping (Bool, Error?) -> ()) {
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessGetFaceLivenessResponse = {(_ response:PSFSGetFaceLivenessResponse) -> Void in
            if (response.items == nil || response.items!.count == 0){
                completion(false, nil)
            }
            else{
                completion(true, nil)
            }
        }
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            completion(false, err)
        }
        serviceLibrary.performGetFaceLiveness(userId: PSFacialEngine.getInstance().getIdxUserId(), idCheck: PSFacialEngine.getInstance().getIdCheckId())
    }
    
    func getLivenessChallenges(userId: String, idCheckId: String, responseHandler: @escaping (PSFEError?, String?) -> (Void)) {
        
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessGetLivenessChallengesResponse = { (_ response:PSFSGetLivenessChallengesResponse, _ jsonString: String?) -> Void in
            if let jsonString = jsonString {
                responseHandler(nil, jsonString)
            }
            else{
                responseHandler(nil, nil)
            }
           
        }
        serviceLibrary.onServiceError = {(_ err:Error)  -> Void in
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: err, cveDoc: nil)
            responseHandler(PSFEError(error: err), nil)
        }
        serviceLibrary.performGetVideoChallenger(userId: userId, idcheckid: idCheckId)
    }
    
    func checkDocumentsStatus(userId: String, idCheckId: String, responseHandler: @escaping (Bool?, Error?) -> (Void)) {
        
        let serviceLibrary = PSFacialServiceViewModel()
        
        serviceLibrary.onSuccessGetCheckAllDocuments = { [weak self] (_ response: PSFSGetAllDocumentsResponse) -> Void in
            
            guard self != nil else { return }
            
            PSFSDocumentsUtil.evaluateDocumentStatus(documentResponse: response,
                                                     completion: responseHandler)
        }
        
        serviceLibrary.onServiceError = { [weak self] (_ err: Error)  -> Void in
            
            guard self != nil else { return }
            
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "",event: .Default, error: err, cveDoc: nil)
            responseHandler(false, err)
        }
        serviceLibrary.perfomCheckAllProcessedDocs(userId: userId, idcheckid: idCheckId)
    }
    
    func createEvaluation(userId : String, idCheckId : String, evaluationPolicyName : String, responseHandler: @escaping (Error?) -> (Void)){
        
        var evaluationStr = ""

        
        let serviceLibrary = PSFacialServiceViewModel()
        serviceLibrary.onSuccessCreateEvaluation = { (_ response:PSFSCreateEvaluationResponse, _ jsonStr: String?) -> Void in

            if let jsonStr = jsonStr {
                evaluationStr = jsonStr
            }
            
            let error = PSFSEvaluationUtil.validateEvaluationResponse(response: response,
                                                                      selectedDocumentType: PSFacialEngine.getInstance().getDocumentType()?.rawValue ?? "" )
            
            if (error != nil){
                 PSFacialEngine.getInstance().setStageReached(.evaluationCheckFailed)
            }
            
            //obtiene el resultado de la cara y la credencial
            let psfsImageResult = PSFSEvaluationUtil.getImageResultFromEvaluationResponse(response: response)
            //convierte el resultado de la cara y la credencial de un objeto de el framewok de los servivcio
            //a un objeto de el motor
            if let psfsImageResult = psfsImageResult{
                let psfeImageResult = PSFEImageResult(fmr: psfsImageResult.fmr,
                                                      result: psfsImageResult.result,
                                                      score: psfsImageResult.score,
                                                      threshold: psfsImageResult.threshold)
                //guarda en el motor el resultado de la cara y de la credencial
                PSFacialEngine.getInstance().setImageResult(psfeImageResult: psfeImageResult)
            }
            
            let statusLog = error != nil ? "NO_MATCH" : psfsImageResult?.result ?? ""
            PSFacialEngine.getInstance().psFacialEngineLogsDelegate?.performSendLogsFacial(curp: PSFacialEngine.getInstance().getUserId(), idLog: PSFacialEngine.getInstance().getIdxUserId(), statusLog: statusLog, responseLog: jsonStr, operatingSystem: "iOS", typeProcess: Int(PSFacialEngine.getInstance().getExpedientType()!) ?? 0)
            
            
            responseHandler(error)
            
        }
        
        serviceLibrary.onServiceError = {(_ error:Error)  -> Void in
            //PSFacialEngine.getInstance().psFacialEnginePSFacialAnalitycsDelegate?.eventAnalitycs(flow: PSFacialEngine.getInstance().getFlowId() ?? "", event: .Default, error: error, cveDoc: nil)
            PSFacialEngine.getInstance().psFacialEngineLogsDelegate?.performSendLogsFacial(curp: PSFacialEngine.getInstance().getUserId(), idLog: PSFacialEngine.getInstance().getIdxUserId(), statusLog: "NO_MATCH", responseLog: evaluationStr, operatingSystem: "iOS", typeProcess: Int(PSFacialEngine.getInstance().getExpedientType()!) ?? 0)
            responseHandler(error)
        }
        serviceLibrary.perfomCreateEvaluation(userId: userId, idcheckid: idCheckId, evaluationPolicyName: evaluationPolicyName)
        
        
    }
    
}
