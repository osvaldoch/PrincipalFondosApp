import UIKit
import DaonDocument

 class PSDKCapturedDocument: NSObject
{
    // MARK:- Properties
    
    var frontCapturedTime : Date?
    var front : DMDSDocument?
    var backCapturedTime : Date?
    var back : DMDSDocument?
    
    // MARK:- Utils
    
    public func reset()
    {
        self.frontCapturedTime  = nil
        self.front              = nil
        self.backCapturedTime   = nil
        self.back               = nil
    }
    
    public func copy() -> PSDKCapturedDocument {
        let copy = PSDKCapturedDocument()
        if let front = self.front{
            copy.front = copyDocument(document: front)
        }
        if let back = self.back{
            copy.back = copyDocument(document: back)
        }
        copy.frontCapturedTime = self.frontCapturedTime
        copy.backCapturedTime = self.backCapturedTime
        return copy
    }
    
    fileprivate func copyQuadrangle(quadCoordinates: DMDSQuadrangle) -> DMDSQuadrangle {
        let copy = DMDSQuadrangle()
        copy.lowerLeft = quadCoordinates.lowerLeft
        copy.lowerRight = quadCoordinates.lowerRight
        copy.upperLeft = quadCoordinates.upperLeft
        copy.upperRight = quadCoordinates.upperRight
        return copy
    }
    
    private func copyDocument(document: DMDSDocument) -> DMDSDocument?{
        let copy = DMDSDocument()
        if let textExtracted = document.textExtracted{
            copy.textExtracted = NSDictionary(dictionary: textExtracted, copyItems: true) as? [AnyHashable : Any]
        }
        copy.qualityScore = document.qualityScore
        if let cgImage = document.processedImage.cgImage{
            copy.processedImage = UIImage(cgImage: cgImage)
        }
        if let cgImage = document.unprocessedImage.cgImage{
            copy.unprocessedImage =  UIImage(cgImage: cgImage)
        }
        copy.processedDocumentCoordinates = copyQuadrangle(quadCoordinates: document.processedDocumentCoordinates)
        copy.documentType = document.documentType
        copy.captureType = document.captureType

        return copy
    }
}
