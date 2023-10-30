//
//  PSInitialize.swift
//  iosApp
//
//  Created by OSVALDO CESPEDES on 22/10/23.
//  Copyright © 2023 orgName. All rights reserved.
//

import Foundation
import shared

#if RELEASE
import PS_Core
import PS_Auto_Transfer
import PS_Core
import PS_BaseExternal
import PS_Facial_Services

public class PSSdkInitialize: PSCoreDelegate {
    
    
    let modelTraspasos = PSAutoTransferViewModel()
    let baseManager = PSBaseService()
    let catalog = PSCatalogViewModel()
    public var curp = "CEHO950625HHGSRS02"
    
    func setupCore() {
#if DEBUG
        let json: [String: Any] = ["url": Constans.sdkProcesar.url,
                                   "key": Constans.sdkProcesar.apiKey,
                                   "versionApp": Constans.Core.version,
                                   "partKey": Constans.Core.secretKey,
                                   "clientID": Constans.Core.coreCurp,
                                   "clientKey": Constans.Core.coreAforeKey]
        print("---- SECRET KEY ----")
        print(json)
#endif
        PSCore.shared.initialize(url: Constans.sdkProcesar.url,
                                 urlWeb: Constans.sdkProcesarUrlWeb,
                                 key: Constans.sdkProcesar.apiKey,
                                 versionApp: Constans.Core.version,
                                 partKey: Constans.Core.secretKey,
                                 clientID: Constans.Core.coreCurp,
                                 clientKey: Constans.Core.coreAforeKey,
                                 keyEncript: Constans.Core.keyEncrypt,
                                 psCoreDelegate: self)
        DispatchQueue.main.async {
            self.load()
        }
        
    }
    
    func load() {
        self.catalog.getInitialization(showContent: true, context: .Transverse)
        self.catalog.onServiceError = {(_ error:PSError)  -> Void in
            let json:[String:String] = ["cveDiagnostic":error.cveDiagnostic,
                                        "exception":error.exception,
                                        "message":error.message]
            print(json)
        }
        self.catalog.onSuccessGetInitialization = { (_ response: PSCheckInitializationResponseModel) -> Void in
            self.loadBaseManager()
            self.loadModelTraspasos()
            self.consultarFolioTraspaso()
            self.successCheckContactDetails()
            var documentos: [PSFSDocumentCatalog.Document] = []
            for catalog in response.identificacionDaon {
                if let type = PSFSDocumentCatalog.Document.DocuementType(rawValue: catalog.nombre) {
                    let doc = PSFSDocumentCatalog.Document(type: type,
                                                           documentos: catalog.documentos)
                    documentos.append(doc)
                }
            }
            PSFSConfigManager.shared.setup().documentCatalogConfig?.withDocumentCatalog(documentCatalog: PSFSDocumentCatalog(documentos: documentos)).build()
            
            DispatchQueue.main.async {
                self.consultarFolio()
            }
        }
    }
    
    private func loadBaseManager(){
        self.baseManager.onServiceError = { [self] (_ error: PSError) -> Void in
            let json:[String:String] = ["cveDiagnostic":error.cveDiagnostic,"exception":error.exception,"message":error.message]
            print(json)
        }
    }
    
    private func loadModelTraspasos(){
        self.modelTraspasos.onServiceError = { (_ error: PSError) -> Void in
            let body:[String:String] = ["exception": error.exception,
                                        "message": error.message]
            print(body)
        }
    }
    
    private func consultarFolioTraspaso() {
        self.modelTraspasos.getConsultarFolioTraspasoApp = {(_ response: PSConsultTransferAppFolioResponse) -> Void in
            print("******************")
            print("******* getConsultarFolioTraspasoApp ***********")
            print("******************")
            print("******************")
            print(response.folio)
            print(response.message)
            self.checkContactDetails()
        }
    }
    
    func consultarFolio() {
        self.modelTraspasos.managerConsultarFolioTraspasoApp(curp: curp)
    }
    
    func checkContactDetails() {
        self.modelTraspasos.checkContactDetails(curp: curp, claveAfore: "538")
    }
    
    private func successCheckContactDetails() {
        self.modelTraspasos.onSuccessCheckContactDetails = { [self] (response:PSContactDetailsResponse) -> Void in
            print("******************")
            print("******* onSuccessCheckContactDetails ***********")
            print("******************")
            print("******************")
            print(response.message)
            print(response.curp)
        }
    }
    
}

extension PSSdkInitialize {
    public func onTokenExpired(error: Error) {
        /*if let topController = UIApplication.topViewController() {
         topController.dismissLoadingView()
         handleLoginError(vc: topController, error: error) {
         tag, result in
         topController.closeSession()
         }
         }*/
    }
}

internal struct Constans {
    
    internal enum PREnvironment: String {
        case Production
        case QA
        case QA2
        case QA3
    }
    
    internal static var environment: PREnvironment = .Production
    
    internal static var sdkProcesar: (url: String, apiKey: String) {
        switch Constans.environment {
            case .Production:
                return (url: "https://api.esar.io/aweb/sartoken/", apiKey: "ef53343d4444cd03ac6b2e97")
            case .QA, .QA2, .QA3:
                return (url: "https://development.esar.io/uat/sartoken/", apiKey: "aghjma23deyfk3xh5zut5ert")
        }
    }
    
    internal static var sdkProcesarUrlWeb: String {
        switch Constans.environment {
        case .Production:
            return "https://api.esar.io/sartoken"
        case .QA, .QA2, .QA3:
            return "https://development.esar.io/sartoken"
        }
    }
    
    internal class Core {
        
        internal static let customProjectId = ""

        internal static let url = "https://api.esar.io/aweb/sartoken/"
        internal static let urlWeb = "https://api.esar.io/sartoken"

        internal static let apiKey = "ef53343d4444cd03ac6b2e97"

        internal static let version = "1.0.0"

        internal static let secretKey = "foWRHpr4ThlcfgKL"
        internal static let keyEncrypt = "Procesar1*"

        internal static let coreCurp = "PECG860227HYNCHB07"

        internal static let coreAforeKey = "538"

    }
    
}
#endif
