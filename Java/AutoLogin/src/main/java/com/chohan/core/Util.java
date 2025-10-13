package com.chohan.core;

import org.bouncycastle.crypto.BlockCipher;
import org.bouncycastle.crypto.engines.TwofishEngine;
import org.bouncycastle.crypto.modes.CBCBlockCipher;
import org.bouncycastle.crypto.paddings.PaddedBufferedBlockCipher;
import org.bouncycastle.crypto.params.KeyParameter;
import org.bouncycastle.crypto.params.ParametersWithIV;
import org.bouncycastle.openpgp.operator.jcajce.JcaKeyFingerprintCalculator;
import org.bouncycastle.openpgp.PGPPublicKeyRing;
import org.bouncycastle.openpgp.operator.PublicKeyDataDecryptorFactory;
import org.bouncycastle.openpgp.operator.jcajce.JcePublicKeyDataDecryptorFactoryBuilder;
import org.bouncycastle.openpgp.operator.jcajce.JcePBESecretKeyDecryptorBuilder;
import org.bouncycastle.openpgp.PGPPrivateKey;
import org.bouncycastle.openpgp.PGPSecretKey;
import org.bouncycastle.openpgp.PGPSecretKeyRingCollection;
import org.bouncycastle.openpgp.PGPCompressedData;
import org.bouncycastle.openpgp.PGPEncryptedData;
import org.bouncycastle.openpgp.PGPEncryptedDataGenerator;
import org.bouncycastle.openpgp.PGPEncryptedDataList;
import org.bouncycastle.openpgp.PGPLiteralData;
import org.bouncycastle.openpgp.PGPLiteralDataGenerator;
import org.bouncycastle.openpgp.PGPOnePassSignatureList;
import org.bouncycastle.openpgp.PGPPublicKey;
import org.bouncycastle.openpgp.PGPPublicKeyEncryptedData;
import org.bouncycastle.openpgp.PGPUtil;
import org.bouncycastle.openpgp.jcajce.JcaPGPObjectFactory;
import org.bouncycastle.openpgp.operator.jcajce.JcePGPDataEncryptorBuilder;
import org.bouncycastle.openpgp.operator.jcajce.JcePBEKeyEncryptionMethodGenerator;
import org.bouncycastle.openpgp.operator.jcajce.JcePublicKeyKeyEncryptionMethodGenerator;
import org.bouncycastle.util.io.Streams;
import org.bouncycastle.bcpg.SymmetricKeyAlgorithmTags;
import org.bouncycastle.jce.provider.BouncyCastleProvider;

import org.jasypt.util.text.BasicTextEncryptor;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.InputStream;
import java.io.OutputStream;
import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.Security;
import java.util.Arrays;
import java.util.Base64;

public class Util {

    static {
        // Add Bouncy Castle provider
        if (Security.getProvider(BouncyCastleProvider.PROVIDER_NAME) == null) {
            Security.addProvider(new BouncyCastleProvider());
        }
    }

    public static String getClassname() {
        String fullClassName = Thread.currentThread().getStackTrace()[2].getClassName();
        return fullClassName.substring(fullClassName.lastIndexOf('.') + 1);
    }

    public static void trace() {
        StackTraceElement e = Thread.currentThread().getStackTrace()[2];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
    }

    /**
     * Universal password decryption method that supports both OpenSSL and Jasypt encrypted passwords
     *
     * @param configValue The password value from configuration (can be plain text, OpenSSL encrypted, or Jasypt encrypted)
     * @param envVarName  Environment variable name containing the OpenSSL pass key (optional, defaults to "OPENSSL_PASS_KEY")
     * @return Decrypted password or original value if not encrypted
     */
    public static String getDecryptedPassword(String configValue, String envVarName) {
        if (configValue == null || configValue.trim().isEmpty()) {
            return configValue;
        }

        try {
            // Check if it's OpenSSL encrypted
            if (isOpenSSLEncrypted(configValue)) {
                System.out.println("Detected OpenSSL encrypted password, decrypting...");
                String passKey = System.getenv(envVarName);
                if (passKey == null || passKey.trim().isEmpty()) {
                    throw new IllegalArgumentException("Environment variable '" + envVarName + "' not found or empty");
                }
                return decryptOpenSSL(configValue, passKey);
            }
            // Check if it's Jasypt encrypted
            else if (configValue.startsWith("ENC(") && configValue.endsWith(")")) {
                System.out.println("Detected Jasypt encrypted password - using existing Jasypt decryption");
                // Note: This would need to be integrated with your existing Jasypt configuration
                // For now, return as-is since Jasypt is already configured in your Spring Boot app
                return configValue;
            }
            // Plain text password
            else {
                return configValue;
            }
        } catch (Exception e) {
            System.err.println("Error decrypting password: " + e.getMessage());
            e.printStackTrace();
            return configValue; // Return original value on error
        }
    }

    /**
     * Convenience method using default environment variable name
     */
    public static String getDecryptedPassword(String configValue) {
        return getDecryptedPassword(configValue, "OPENSSL_PASS_KEY");
    }

    /**
     * Check if a configuration value appears to be encrypted (either OpenSSL or Jasypt)
     */
    public static boolean isEncryptedPassword(String configValue) {
        if (configValue == null || configValue.trim().isEmpty()) {
            return false;
        }

        return isOpenSSLEncrypted(configValue) ||
                (configValue.startsWith("ENC(") && configValue.endsWith(")"));
    }

    /**
     * Encrypts a plaintext string using TwoFish encryption algorithm
     *
     * @param plaintext The text to encrypt
     * @param key       The encryption key (must be 16, 24, or 32 bytes)
     * @return Base64 encoded encrypted string with IV prepended
     * @throws Exception if encryption fails
     */
    public static String encryptTwoFish(String plaintext, byte[] key) throws Exception {
        if (plaintext == null || plaintext.isEmpty()) {
            throw new IllegalArgumentException("Plaintext cannot be null or empty");
        }

        if (key == null || (key.length != 16 && key.length != 24 && key.length != 32)) {
            throw new IllegalArgumentException("Key must be 16, 24, or 32 bytes long");
        }

        // Generate random IV
        byte[] iv = new byte[16]; // TwoFish block size is 16 bytes
        new SecureRandom().nextBytes(iv);

        // Create TwoFish cipher in CBC mode with PKCS7 padding
        BlockCipher engine = new TwofishEngine();
        BlockCipher cipher = new CBCBlockCipher(engine);
        PaddedBufferedBlockCipher paddedCipher = new PaddedBufferedBlockCipher(cipher);

        // Initialize cipher for encryption
        KeyParameter keyParam = new KeyParameter(key);
        ParametersWithIV keyWithIV = new ParametersWithIV(keyParam, iv);
        paddedCipher.init(true, keyWithIV);

        // Encrypt the plaintext
        byte[] input = plaintext.getBytes(StandardCharsets.UTF_8);
        byte[] output = new byte[paddedCipher.getOutputSize(input.length)];

        int len = paddedCipher.processBytes(input, 0, input.length, output, 0);
        len += paddedCipher.doFinal(output, len);

        // Trim output to actual length
        byte[] encrypted = new byte[len];
        System.arraycopy(output, 0, encrypted, 0, len);

        // Prepend IV to encrypted data
        byte[] result = new byte[iv.length + encrypted.length];
        System.arraycopy(iv, 0, result, 0, iv.length);
        System.arraycopy(encrypted, 0, result, iv.length, encrypted.length);

        // Return Base64 encoded result
        return Base64.getEncoder().encodeToString(result);
    }

    /**
     * Encrypts a plaintext string using TwoFish with a string key
     *
     * @param plaintext The text to encrypt
     * @param keyString The encryption key as string (will be hashed to appropriate length)
     * @return Base64 encoded encrypted string with IV prepended
     * @throws Exception if encryption fails
     */
    public static String encryptTwoFish(String plaintext, String keyString) throws Exception {
        if (keyString == null || keyString.isEmpty()) {
            throw new IllegalArgumentException("Key string cannot be null or empty");
        }

        // Hash the key string to get a 32-byte key
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] key = digest.digest(keyString.getBytes(StandardCharsets.UTF_8));

        return encryptTwoFish(plaintext, key);
    }

    /**
     * Decrypts a TwoFish encrypted string
     *
     * @param encryptedData Base64 encoded encrypted data with IV prepended
     * @param key           The decryption key (must be 16, 24, or 32 bytes)
     * @return Decrypted plaintext string
     * @throws Exception if decryption fails
     */
    public static String decryptTwoFish(String encryptedData, byte[] key) throws Exception {
        if (encryptedData == null || encryptedData.isEmpty()) {
            throw new IllegalArgumentException("Encrypted data cannot be null or empty");
        }

        if (key == null || (key.length != 16 && key.length != 24 && key.length != 32)) {
            throw new IllegalArgumentException("Key must be 16, 24, or 32 bytes long");
        }

        // Decode Base64 data
        byte[] data = Base64.getDecoder().decode(encryptedData);

        if (data.length < 16) {
            throw new IllegalArgumentException("Invalid encrypted data: too short");
        }

        // Extract IV and encrypted data
        byte[] iv = new byte[16];
        byte[] encrypted = new byte[data.length - 16];
        System.arraycopy(data, 0, iv, 0, 16);
        System.arraycopy(data, 16, encrypted, 0, encrypted.length);

        // Create TwoFish cipher in CBC mode with PKCS7 padding
        BlockCipher engine = new TwofishEngine();
        BlockCipher cipher = new CBCBlockCipher(engine);
        PaddedBufferedBlockCipher paddedCipher = new PaddedBufferedBlockCipher(cipher);

        // Initialize cipher for decryption
        KeyParameter keyParam = new KeyParameter(key);
        ParametersWithIV keyWithIV = new ParametersWithIV(keyParam, iv);
        paddedCipher.init(false, keyWithIV);

        // Decrypt the data
        byte[] output = new byte[paddedCipher.getOutputSize(encrypted.length)];
        int len = paddedCipher.processBytes(encrypted, 0, encrypted.length, output, 0);
        len += paddedCipher.doFinal(output, len);

        // Trim output to actual length and convert to string
        byte[] decrypted = new byte[len];
        System.arraycopy(output, 0, decrypted, 0, len);

        return new String(decrypted, StandardCharsets.UTF_8);
    }

    /**
     * Decrypts a TwoFish encrypted string using a string key
     *
     * @param encryptedData Base64 encoded encrypted data with IV prepended
     * @param keyString     The decryption key as string (will be hashed to appropriate length)
     * @return Decrypted plaintext string
     * @throws Exception if decryption fails
     */
    public static String decryptTwoFish(String encryptedData, String keyString) throws Exception {
        if (keyString == null || keyString.isEmpty()) {
            throw new IllegalArgumentException("Key string cannot be null or empty");
        }

        // Hash the key string to get a 32-byte key
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] key = digest.digest(keyString.getBytes(StandardCharsets.UTF_8));

        return decryptTwoFish(encryptedData, key);
    }

    /**
     * Generates a random TwoFish key
     *
     * @param keySize Key size in bytes (16, 24, or 32)
     * @return Random key bytes
     * @throws IllegalArgumentException if key size is invalid
     */
    public static byte[] generateTwoFishKey(int keySize) {
        if (keySize != 16 && keySize != 24 && keySize != 32) {
            throw new IllegalArgumentException("Key size must be 16, 24, or 32 bytes");
        }

        byte[] key = new byte[keySize];
        new SecureRandom().nextBytes(key);
        return key;
    }

    /**
     * Encrypts a plaintext string using Jasypt
     *
     * @param plaintext The text to encrypt
     * @param password  The password to use for encryption
     * @return Encrypted string in Jasypt's format
     */
    public static String encryptJasypt(String plaintext, String password) {
        BasicTextEncryptor textEncryptor = new BasicTextEncryptor();
        textEncryptor.setPassword(password);
        return textEncryptor.encrypt(plaintext);
    }

    /**
     * Decrypts a Jasypt encrypted string
     *
     * @param encryptedText The encrypted text
     * @param password      The password to use for decryption
     * @return Decrypted plaintext string
     */
    public static String decryptJasypt(String encryptedText, String password) {
        BasicTextEncryptor textEncryptor = new BasicTextEncryptor();
        textEncryptor.setPassword(password);
        return textEncryptor.decrypt(encryptedText);
    }

    /**
     * Encrypts a plaintext string using GPG with a public key
     *
     * @param plaintext        The text to encrypt
     * @param publicKeyArmored The armored GPG public key
     * @return Base64 encoded encrypted string
     * @throws Exception if encryption fails
     */
    public static String encryptGPG(String plaintext, String publicKeyArmored) throws Exception {
//        PGPPublicKey publicKey = PGPUtil.getPublicKey(new ByteArrayInputStream(publicKeyArmored.getBytes(StandardCharsets.UTF_8)));
        InputStream inputStream = new ByteArrayInputStream(publicKeyArmored.getBytes(StandardCharsets.UTF_8));
        PGPPublicKeyRing pubKeyRing = new PGPPublicKeyRing(inputStream, new JcaKeyFingerprintCalculator());
        PGPPublicKey publicKey = pubKeyRing.getPublicKey();

        ByteArrayOutputStream out = new ByteArrayOutputStream();
        PGPEncryptedDataGenerator encryptedDataGenerator = new PGPEncryptedDataGenerator(
                new JcePGPDataEncryptorBuilder(SymmetricKeyAlgorithmTags.AES_256)
                        .setWithIntegrityPacket(true)
                        .setSecureRandom(new SecureRandom())
                        .setProvider("BC"));
        encryptedDataGenerator.addMethod(new JcePublicKeyKeyEncryptionMethodGenerator(publicKey).setProvider("BC"));

        OutputStream encryptedOut = encryptedDataGenerator.open(out, new byte[4096]);

        PGPLiteralDataGenerator literalDataGenerator = new PGPLiteralDataGenerator();
        OutputStream literalOut = literalDataGenerator.open(
                encryptedOut,
                PGPLiteralData.BINARY,
                PGPLiteralData.CONSOLE,
                plaintext.length(),
                new java.util.Date()
        );

        literalOut.write(plaintext.getBytes(StandardCharsets.UTF_8));
        literalOut.close();
        encryptedOut.close();

        return Base64.getEncoder().encodeToString(out.toByteArray());
    }

    /**
     * Decrypts a GPG encrypted string using a private key
     *
     * @param encryptedDataB64  Base64 encoded encrypted data
     * @param privateKeyArmored The armored GPG private key
     * @param passphrase        The passphrase for the private key
     * @return Decrypted plaintext string
     * @throws Exception if decryption fails
     */
    public static String decryptGPG(String encryptedDataB64, String privateKeyArmored, String passphrase) throws Exception {
        byte[] encryptedData = Base64.getDecoder().decode(encryptedDataB64);
        InputStream in = new ByteArrayInputStream(encryptedData);

        in = PGPUtil.getDecoderStream(in);
        JcaPGPObjectFactory pgpFact = new JcaPGPObjectFactory(in);

        PGPEncryptedDataList enc;
        Object o = pgpFact.nextObject();
        if (o instanceof PGPEncryptedDataList) {
            enc = (PGPEncryptedDataList) o;
        } else {
            enc = (PGPEncryptedDataList) pgpFact.nextObject();
        }

        PGPPublicKeyEncryptedData pbe = (PGPPublicKeyEncryptedData) enc.get(0);

//        PGPSecretKeyRingCollection pgpSec = new PGPSecretKeyRingCollection(
//                PGPUtil.getDecoderStream(new ByteArrayInputStream(privateKeyArmored.getBytes(StandardCharsets.UTF_8)))
//        );
        InputStream keyIn = new ByteArrayInputStream(privateKeyArmored.getBytes(StandardCharsets.UTF_8));
        PGPSecretKeyRingCollection secretKeyRingCollection =
                new PGPSecretKeyRingCollection(PGPUtil.getDecoderStream(keyIn), new JcaKeyFingerprintCalculator());

//        PGPSecretKey secretKey = pgpSec.getSecretKey(pbe.getKeyID());
//        PGPPrivateKey privateKey = secretKey.extractPrivateKey(
//                new JcePBESecretKeyDecryptorBuilder().setProvider("BC").build(passphrase.toCharArray())
//        );
        PGPSecretKey secretKey = secretKeyRingCollection.getSecretKey(pbe.getKeyID());
        PGPPrivateKey privateKey = secretKey.extractPrivateKey(
                new JcePBESecretKeyDecryptorBuilder().setProvider("BC").build(passphrase.toCharArray())
        );
        PublicKeyDataDecryptorFactory decryptorFactory =
                new JcePublicKeyDataDecryptorFactoryBuilder().setProvider("BC").build(privateKey);

        InputStream clear = pbe.getDataStream(decryptorFactory);
        JcaPGPObjectFactory plainFact = new JcaPGPObjectFactory(clear);

        Object message = plainFact.nextObject();
        if (message instanceof PGPCompressedData) {
            PGPCompressedData cData = (PGPCompressedData) message;
            JcaPGPObjectFactory pgpFacto = new JcaPGPObjectFactory(cData.getDataStream());
            message = pgpFacto.nextObject();
        }

        if (message instanceof PGPLiteralData) {
            PGPLiteralData ld = (PGPLiteralData) message;
            InputStream unc = ld.getInputStream();
            ByteArrayOutputStream out = new ByteArrayOutputStream();
            Streams.pipeAll(unc, out);
            return out.toString(StandardCharsets.UTF_8.name());
        } else if (message instanceof PGPOnePassSignatureList) {
            throw new Exception("Encrypted message contains a signed message - not literal data.");
        } else {
            throw new Exception("Message is not a simple encrypted file - type unknown.");
        }
    }

    private static final String ALGORITHM = "AES";
    private static final String TRANSFORMATION = "AES/CBC/PKCS5Padding";
    private static final String OPENSSL_MAGIC = "Salted__";
    private static final int KEY_LENGTH = 32; // 256 bits
    private static final int IV_LENGTH = 16;  // 128 bits

    /**
     * Encrypts a plaintext string using OpenSSL's AES-256-CBC algorithm
     *
     * @param plaintext The text to encrypt
     * @param passKey   The password to use for encryption
     * @return Base64 encoded encrypted string in OpenSSL's format
     * @throws Exception if encryption fails
     */
    public static String encryptOpenSSL(String plaintext, String passKey) throws Exception {
        // Generate a random 8-byte salt
        byte[] salt = new byte[8];
        new SecureRandom().nextBytes(salt);

        // Derive key and IV from password and salt
        byte[][] keyAndIV = deriveKeyAndIV(passKey.getBytes(StandardCharsets.UTF_8), salt);
        byte[] key = keyAndIV[0];
        byte[] iv = keyAndIV[1];

        // Encrypt using AES-256-CBC
        SecretKeySpec secretKey = new SecretKeySpec(key, "AES");
        IvParameterSpec ivSpec = new IvParameterSpec(iv);
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey, ivSpec);
        byte[] encrypted = cipher.doFinal(plaintext.getBytes(StandardCharsets.UTF_8));

        // Prepend "Salted__" and the salt
        ByteArrayOutputStream out = new ByteArrayOutputStream();
        out.write("Salted__".getBytes(StandardCharsets.UTF_8));
        out.write(salt);
        out.write(encrypted);

        return Base64.getEncoder().encodeToString(out.toByteArray());
    }

    /**
     * Decrypts an OpenSSL encrypted password using the provided pass key
     *
     * @param encryptedData Base64 encoded encrypted data (OpenSSL format)
     * @param passKey       Pass key for decryption
     * @return Decrypted password as string
     * @throws Exception if decryption fails
     */
    public static String decryptOpenSSL(String encryptedData, String passKey) throws Exception {
        if (encryptedData == null || encryptedData.trim().isEmpty()) {
            throw new IllegalArgumentException("Encrypted data cannot be null or empty");
        }

        if (passKey == null || passKey.trim().isEmpty()) {
            throw new IllegalArgumentException("Pass key cannot be null or empty");
        }

        // Decode base64 encrypted data
        byte[] encrypted = Base64.getDecoder().decode(encryptedData.trim());

        // Check for OpenSSL magic header
        if (encrypted.length < 16 || !Arrays.equals(Arrays.copyOfRange(encrypted, 0, 8),
                OPENSSL_MAGIC.getBytes(StandardCharsets.UTF_8))) {
            throw new IllegalArgumentException("Invalid OpenSSL encrypted data format");
        }

        // Extract salt (8 bytes after magic header)
        byte[] salt = Arrays.copyOfRange(encrypted, 8, 16);

        // Extract actual encrypted data
        byte[] cipherText = Arrays.copyOfRange(encrypted, 16, encrypted.length);

        // Derive key and IV using OpenSSL's EVP_BytesToKey equivalent
        byte[][] keyAndIV = deriveKeyAndIV(passKey.getBytes(StandardCharsets.UTF_8), salt);
        byte[] key = keyAndIV[0];
        byte[] iv = keyAndIV[1];

        // Decrypt using AES-256-CBC
        SecretKeySpec secretKey = new SecretKeySpec(key, ALGORITHM);
        IvParameterSpec ivSpec = new IvParameterSpec(iv);

        Cipher cipher = Cipher.getInstance(TRANSFORMATION);
        cipher.init(Cipher.DECRYPT_MODE, secretKey, ivSpec);

        byte[] decrypted = cipher.doFinal(cipherText);
        return new String(decrypted, StandardCharsets.UTF_8);
    }

    /**
     * Derives key and IV using OpenSSL's EVP_BytesToKey equivalent algorithm
     * This mimics the key derivation used by OpenSSL's "openssl enc" command
     */
    public static byte[][] deriveKeyAndIV(byte[] password, byte[] salt) throws Exception {
        MessageDigest md = MessageDigest.getInstance("MD5");
        byte[] key = new byte[KEY_LENGTH];
        byte[] iv = new byte[IV_LENGTH];
        byte[] concat = new byte[password.length + salt.length];

        System.arraycopy(password, 0, concat, 0, password.length);
        System.arraycopy(salt, 0, concat, password.length, salt.length);

        byte[] hash = md.digest(concat);
        int keyIvLen = KEY_LENGTH + IV_LENGTH;
        byte[] keyIv = new byte[keyIvLen];
        int hashLen = hash.length;

        System.arraycopy(hash, 0, keyIv, 0, Math.min(hashLen, keyIvLen));

        // If we need more bytes, keep hashing
        int offset = hashLen;
        while (offset < keyIvLen) {
            md.reset();
            md.update(hash);
            md.update(concat);
            hash = md.digest();

            int remaining = keyIvLen - offset;
            int copyLen = Math.min(hashLen, remaining);
            System.arraycopy(hash, 0, keyIv, offset, copyLen);
            offset += copyLen;
        }

        System.arraycopy(keyIv, 0, key, 0, KEY_LENGTH);
        System.arraycopy(keyIv, KEY_LENGTH, iv, 0, IV_LENGTH);

        return new byte[][]{key, iv};
    }

    /**
     * Utility method to check if a string appears to be OpenSSL encrypted
     * (Base64 encoded and starts with "Salted__" when decoded)
     */
    public static boolean isOpenSSLEncrypted(String data) {
        if (data == null || data.trim().isEmpty()) {
            return false;
        }

        try {
            byte[] decoded = Base64.getDecoder().decode(data.trim());
            return decoded.length >= 16 &&
                    Arrays.equals(Arrays.copyOfRange(decoded, 0, 8),
                            OPENSSL_MAGIC.getBytes(StandardCharsets.UTF_8));
        } catch (Exception e) {
            return false;
        }
    }

    /**
     * Convenience method to decrypt password with default environment variable name
     */
    public static String decryptPasswordFromEnv(String encryptedData, String envVarName) throws Exception {
        String passKey = System.getenv(envVarName);
        if (passKey == null || passKey.trim().isEmpty()) {
            throw new IllegalArgumentException("Environment variable '" + envVarName + "' not found or empty");
        }

        return decryptOpenSSL(encryptedData, passKey);
    }

    public static String decryptPasswordFromEnv(String encryptedData) throws Exception {
        return decryptPasswordFromEnv(encryptedData, "OPENSSL_PASS_KEY");
    }
}
