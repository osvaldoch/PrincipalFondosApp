//
//  DASStorageProvider.h
//  DaonAuthenticatorSDK
//
//  Created by Neil Johnston on 4/3/19.
//  Copyright © 2019 Daon. All rights reserved.
//

#import <DaonAuthenticatorSDK/DASAuthenticator.h>

// Forward Declarations
@class DASLockInfo;

// Blocks

/*!
 @typedef DASStorageCompletionBlock
 @brief Block that is used to notify a calling object that a data item has been stored.
 @param error An error if the storage failed, otherwise nil.
 */
typedef void (^DASStorageCompletionBlock) (NSError* error);

/*!
 @typedef DASRetrievalCompletionBlock
 @brief Block that is used to notify a calling object that a data item has been retrieved.
 @param error An error if the retrieval failed, otherwise nil.
 @param data The retrieved data.
 */
typedef void (^DASRetrievalCompletionBlock) (NSError* error, NSData* data);

// Constants
extern NSString * const KDASStorageKeyDaonExtensions;

// Enums
/*!
 @typedef DASStoredDataType
 @brief Categorizes the different registration data that can be encrypted and stored.
 @constant DASStoredDataTypeRegistrationData    The registration data in it's final form, e.g a face or voice template.
 @constant DASStoredDataTypeRawRegistrationData The raw (original) data before template generation. This is not stored by default, it must be enabled via an extension.
 */
typedef NS_ENUM(NSInteger, DASStoredDataType)
{
    DASStoredDataTypeRegistrationData       = 0,
    DASStoredDataTypeRawRegistrationData    = 1,
};

/*!
 @brief Protocol for classes that which to provide key management and storage capabilities.
 */
@protocol DASStorageProvider <NSObject>

/*!
 @functiongroup Keys
 */

/*!
 @brief Determine if keys exist for a particular key name.
 @param keyName The name of the keys to create.
 @return YES if the keys exist
 */
- (BOOL) hasKey:(NSString*)keyName;

/*!
 @brief Create keys for a particular key name.
 @param keyName The name of the keys to create.
 @param authenticator The @link DASAuthenticator @/link type used when accessing the key.
 @return YES if the keys were created.
 */
- (BOOL) createKeys:(NSString*)keyName authenticator:(id<DASAuthenticator>)authenticator;

/*!
 @brief Create keys for a particular key name.
 @param keyName The name of the keys to create.
 @param authenticator The @link DASAuthenticator @/link type used when accessing the key.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used when accessing the key.
 @return YES if the keys were created.
 */
- (BOOL) createKeys:(NSString*)keyName authenticator:(id<DASAuthenticator>)authenticator algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/*!
 @brief Remove the keys created for a particular key name.
 @param keyName The name of the keys to delete.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used when accessing the key.
 @return YES if the keys were deleted.
 */
- (BOOL) removeKeys:(NSString*)keyName algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/*!
 @brief Retrieve the public key that is being stored for a particular key name.
 @param keyName The key to retrieve the public key for.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used when accessing the key.
 @return An NSData object containing the public key.
 */
- (NSData*) getPublicKey:(NSString*)keyName algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;

/*!
 @brief Determines if a Local Authentication device enrollment (Touch ID / Face ID) has changed.
 @param keyName The name of the signing key that was previously registered and will be checked.
 @param algorithm The @link DASAuthenticatorSigningAlgorithm @/link type used when accessing the key.
 @return YES if the device enrollment has changed (finger/face have been added or removed).
 */
- (BOOL) hasEnrollmentChangedForKey:(NSString*)keyName algorithm:(DASAuthenticatorSigningAlgorithm)algorithm;



/*!
 @functiongroup Signing
 */

/*!
 @functiongroup NSString storage and retrieval
 */

/*!
 @brief Stores an NSString in the keychain or user defaults.
 @param storageKeyString The key under which to store the NSString.
 @param value The NSString to store.
 @param inKeychain If YES the NSString will be stored in the keychain otherwise it will be stored in user defaults.
 */
- (void) setString:(NSString*)storageKeyString value:(NSString*)value inKeychain:(BOOL)inKeychain;

/*!
 @brief Retrieve an NSString that is stored in the keychain or user defaults.
 @param storageKeyString The key under which the NSString is stored.
 @param inKeychain If YES the NSString will be retrieved from the keychain otherwise it will be retrieved from user defaults.
 @return The retrieved NSString
 */
- (NSString*) getString:(NSString*)storageKeyString inKeychain:(BOOL)inKeychain;

/*!
 @brief Check if an NSString that is stored in the keychain or user defaults.
 @param storageKeyString The key under which the NSString is stored.
 @param inKeychain If YES the NSString will checked for in the keychain otherwise it will be checked in user defaults.
 @return YES if the NSString is stored.
 */
- (BOOL) hasString:(NSString*)storageKeyString inKeychain:(BOOL)inKeychain;

/*!
 @brief Remove an NSString from the keychain or user defaults.
 @param storageKeyString The key under which the NSString is stored.
 @param inKeychain If YES the NSString will be removed from the keychain otherwise it will be removed from user defaults.
 */
- (void) removeString:(NSString*)storageKeyString inKeychain:(BOOL)inKeychain;



/*!
 @functiongroup NSDictionary storage and retrieval
 */

/*!
 @brief Stores an NSDictionary in the keychain
 @param storageKeyString The key under which to store the NSDictionary.
 @param value The NSDictionary to store.
 */
- (void) setDictionary:(NSString*)storageKeyString value:(NSDictionary*)value;

/*!
 @brief Retrieve an NSDictionary that is stored in the keychain.
 @param storageKeyString The key under which the NSDictionary is stored.
 @return The retrieved NSDictionary
 */
- (NSDictionary*) getDictionary:(NSString*)storageKeyString;

/*!
 @brief Remove an NSDictionary from the keychain.
 @param storageKeyString The key under which the NSDictionary is stored.
 */
- (void) removeDictionary:(NSString*)storageKeyString;



/*!
 @functiongroup NSData storage and retrieval
 */

/*!
 @brief Stores an NSData in the keychain
 @param storageKeyString The key under which to store the NSData.
 @param value The NSData to store.
 */
- (void) setData:(NSString*)storageKeyString value:(NSData*)value;

/*!
 @brief Retrieve an NSData that is stored in the keychain.
 @param storageKeyString The key under which the NSData is stored.
 @return The retrieved NSData
 */
- (NSData*) getData:(NSString*)storageKeyString;

/*!
 @brief Remove an NSDictionary from the keychain.
 @param storageKeyString The key under which the NSDictionary is stored.
 */
- (void) removeData:(NSString*)storageKeyString;



/*!
 @functiongroup Locking
 */

/*!
 @brief Retrieves the @link LockInfo @/link for a specific authenticator.
 @param authenticatorId The ID of the authenticator whose @link LockInfo @/link will be retrieved.
 @return The @link LockInfo @/link for the specified authenticator
 */
- (DASLockInfo*) lockInfoForAuthenticator:(NSString*)authenticatorId;

/*!
 @brief Updates the @link LockInfo @/link for a specific authenticator.
 @param lockInfo The updated @link LockInfo @/link object
 @param authenticatorId The ID of the authenticator whose @link LockInfo @/link will be updated.
 */
- (void) updateLockInfo:(DASLockInfo*)lockInfo forAuthenticator:(NSString*)authenticatorId;

/*!
 @brief Unlocks a specific authenticator.
 @param authenticatorId The ID of the authenticator which will be unlocked.
 @param randomId A random string that will be stored with the unlock request. The random string is stored with the authenticators state. When a subsequent unlock request is made, the new string will be compared against the previous string. If they do not match, then the unlock will proceed.
 @return YES if the authenticator was unlocked.
 */
- (BOOL) unlock:(NSString*)authenticatorId randomId:(NSString*)randomId;

/*!
 @brief Retrieves the @link DASAuthenticatorLockState @/link for a specific authenticator.
 @param authenticatorId The ID of the authenticator whose lock information will be retrieved.
 @return The @link DASAuthenticatorLockState @/link.
 */
- (DASAuthenticatorLockState) lockStateForAuthenticator:(NSString*)authenticatorId;

/*!
 @brief Delete the stored lock information (@link LockInfo @/link) for a specific authenticator.
 @param authenticatorId The ID of the authenticator whose lock information will be deleted.
 */
- (void) deleteLockInfoForAuthenticator:(NSString*)authenticatorId;



/*!
 @functiongroup Reenroll
 */

/*!
 @brief Prepares the authenticator for re-enrollment.
 @discussion The random string is stored with the authenticators state. When a subsequent re-enroll request is made, the new string will be compared against the previous string. If they do not match, then the re-enroll can proceed.
 @param authenticatorId The ID of the authenticator which will be prepared for re=enrollment.
 @param randomId A random string that will be stored with the reenroll request.
 @return YES if the authenticator can re-enroll
 */
- (BOOL) reenroll:(NSString*)authenticatorId randomId:(NSString*)randomId;



/*!
 @functiongroup File System Encryption
 */

/*!
 @brief Generates a random data id for use in naming an encrypted data file.
 @param authenticatorId The ID of the authenticator whose data will potentially be stored in the encrypted data file.
 @param dataType The @link DASStoredDataType @/link type of the data that will potentially be stored in the encrypted data file.
 @return The random data id for use in naming an encrypted data file.
 */
- (NSString*) getDataIdForAuthenticator:(NSString*)authenticatorId forDataType:(DASStoredDataType)dataType;

/*!
 @brief Determines if an encrypted data file with a specified ID exists.
 @param dataId A unique ID which identifies the encrypted data file.
 @return YES if the encrypted data file exists.
 */
- (BOOL) isDataAvailable:(NSString*)dataId;

/*!
 @brief Stores a NSData object in an encrypted data file with a specified ID.
 @param data The data to store.
 @param dataId A unique ID which identifies the encrypted data file.
 @param backgroundOption If YES, the kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly attribute will be used when creating the encryption keys.
 @param completionBlock A @link DASStorageCompletionBlock @/link block that will be used to notify the caller that the data was stored, or failed during the attempt.
 */
- (void) storeData:(NSData*)data withId:(NSString*)dataId withBackgroundOption:(BOOL)backgroundOption completionBlock:(DASStorageCompletionBlock)completionBlock;

/*!
 @brief Asynchronously Retrieves the contents of encrypted data file with a specified ID.
 @param dataId A unique ID which identifies the encrypted data file.
 @param backgroundOption If YES, the kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly attribute will be used when accessing the encryption keys.
 @param completionBlock A @link DASRetrievalCompletionBlock @/link block that will be used to notify the caller that the data was retrieved, or failed during the attempt.
 */
- (void) retrieveDataWithId:(NSString*)dataId withBackgroundOption:(BOOL)backgroundOption completionBlock:(DASRetrievalCompletionBlock)completionBlock;

/*!
 @brief Synchronously Retrieves the contents of encrypted data file with a specified ID.
 @param dataId A unique ID which identifies the encrypted data file.
 @param backgroundOption If YES, the kSecAttrAccessibleAfterFirstUnlockThisDeviceOnly attribute will be used when accessing the encryption keys.
 @param error The pointer to an NSError object that will be set if an error occurred.
 @return The retrieved data or nil if an error occurred.
 */
- (NSData*) retrieveDataWithId:(NSString*)dataId withBackgroundOption:(BOOL)backgroundOption error:(NSError**)error;

/*!
 @brief Deletes the encrypted data file with a specified ID.
 @param dataId A unique ID which identifies the encrypted data file.
 */
- (void) deleteDataWithId:(NSString*)dataId;

/*!
 @brief Removes all stored settings (From NSUserDefaults) and deletes all encrypted data files from the file system.
 */
- (void) reset;

@end
