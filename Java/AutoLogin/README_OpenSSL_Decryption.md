# OpenSSL Password Decryption Implementation

This document explains how to use the OpenSSL password decryption functionality that has been added to your AutoLogin project.

## Overview

The `OpenSSLDecryptor` class provides OpenSSL-compatible AES-256-CBC decryption functionality that can decrypt passwords encrypted with OpenSSL using a pass key stored in an environment variable.

## Features

- **AES-256-CBC Decryption**: Compatible with OpenSSL's default encryption
- **Environment Variable Support**: Pass key retrieved from environment variables
- **OpenSSL Format Detection**: Automatically detects OpenSSL encrypted data format
- **Error Handling**: Comprehensive error handling and validation
- **Integration Ready**: Easy to integrate with existing configuration management

## Files Added

1. `src/main/java/com/chohan/core/OpenSSLDecryptor.java` - Main decryption utility
2. `src/main/java/com/chohan/core/OpenSSLDecryptorTest.java` - Test and demonstration class
3. `README_OpenSSL_Decryption.md` - This documentation file

## Usage Examples

### 1. Basic Usage with Environment Variable

```java
// Set environment variable first
// Windows: set OPENSSL_PASS_KEY=your_secret_key
// Linux/Mac: export OPENSSL_PASS_KEY=your_secret_key

String encryptedPassword = "U2FsdGVkX1+..."; // Your OpenSSL encrypted data
String decrypted = OpenSSLDecryptor.decryptPasswordFromEnv(encryptedPassword);
```

### 2. Usage with Custom Environment Variable

```java
String encryptedPassword = "U2FsdGVkX1+...";
String decrypted = OpenSSLDecryptor.decryptPassword(encryptedPassword, "MY_CUSTOM_PASS_KEY");
```

### 3. Usage with Direct Pass Key

```java
String encryptedPassword = "U2FsdGVkX1+...";
String passKey = "your_secret_key";
String decrypted = OpenSSLDecryptor.decryptPassword(encryptedPassword, passKey);
```

### 4. Check if Data is OpenSSL Encrypted

```java
String data = "U2FsdGVkX1+...";
if (OpenSSLDecryptor.isOpenSSLEncrypted(data)) {
    String decrypted = OpenSSLDecryptor.decryptPasswordFromEnv(data);
}
```

## Creating OpenSSL Encrypted Passwords

To create passwords that can be decrypted by this utility, use OpenSSL command line:

### Encrypt a password:
```bash
echo "your_password" | openssl enc -aes-256-cbc -a -salt -k "your_secret_key"
```

### Encrypt from file:
```bash
openssl enc -aes-256-cbc -a -salt -in password.txt -out encrypted.txt -k "your_secret_key"
```

## Environment Variable Setup

### Windows:
```cmd
set OPENSSL_PASS_KEY=your_secret_key
```

### Linux/Mac:
```bash
export OPENSSL_PASS_KEY=your_secret_key
```

### Permanent Setup (Windows):
```cmd
setx OPENSSL_PASS_KEY "your_secret_key"
```

## Integration with Existing Configuration

You can integrate this with your existing configuration management by modifying your property loading logic:

```java
public String getDecryptedPassword(String configValue) {
    try {
        if (OpenSSLDecryptor.isOpenSSLEncrypted(configValue)) {
            return OpenSSLDecryptor.decryptPasswordFromEnv(configValue);
        } else if (configValue.startsWith("ENC(") && configValue.endsWith(")")) {
            // Use existing Jasypt decryption
            return jasyptDecrypt(configValue);
        } else {
            return configValue; // Plain text
        }
    } catch (Exception e) {
        System.err.println("Error decrypting password: " + e.getMessage());
        return configValue;
    }
}
```

## Testing

Run the test class to verify the implementation:

```java
java -cp "target/classes:target/lib/*" com.chohan.core.OpenSSLDecryptorTest
```

## Security Considerations

1. **Environment Variables**: Store pass keys in environment variables, not in code
2. **Key Management**: Use strong, unique pass keys for each environment
3. **Access Control**: Limit access to environment variables containing pass keys
4. **Logging**: Avoid logging decrypted passwords or pass keys

## Error Handling

The implementation includes comprehensive error handling for:
- Missing or empty environment variables
- Invalid encrypted data format
- Decryption failures
- Null or empty input validation

## Compatibility

- **Java Version**: Compatible with Java 8+
- **OpenSSL**: Compatible with OpenSSL AES-256-CBC encryption
- **Format**: Supports standard OpenSSL base64 encoded format with "Salted__" header

## Example Configuration Update

You can update your `application.properties` to use OpenSSL encrypted passwords:

```properties
# Original Jasypt encrypted passwords
EnbridgeGas.password=ENC(Ype4nebmcU6K91SrFY8nM7GsK6NEHESz)

# New OpenSSL encrypted passwords (example format)
# EnbridgeGas.password=U2FsdGVkX1+your_openssl_encrypted_password_here
```

## Troubleshooting

1. **Environment Variable Not Found**: Ensure the environment variable is set and accessible
2. **Invalid Format**: Verify the encrypted data is in proper OpenSSL base64 format
3. **Decryption Fails**: Check that the pass key matches the one used for encryption
4. **Compilation Issues**: Ensure all required Java crypto libraries are available

## Support

For issues or questions about this implementation, refer to the test class `OpenSSLDecryptorTest.java` for usage examples and troubleshooting guidance.
