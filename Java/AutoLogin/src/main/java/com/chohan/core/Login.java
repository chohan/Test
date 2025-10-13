package com.chohan.core;
//%JAVA17_HOME%\bin\java -Djasypt.encryptor.password="${ENV_PASSPHRASE}" -jar target\AutoLoginProject-1.0-SNAPSHOT.jar
//java -cp jasypt-1.9.3.jar org.jasypt.intf.cli.JasyptPBEStringEncryptionCLI input="YourPassword" password="SecretKey" algorithm=PBEWithMD5AndDES
///t/ThirdParty/Java/jasypt-1.9.3/bin/encrypt.sh password="${ENV_PASSPHRASE}" verbose=false input="This is my message to be encrypted"
///t/ThirdParty/Java/jasypt-1.9.3/bin/decrypt.sh password="${ENV_PASSPHRASE}" verbose=false input="k1AwOd5XuW4VfPQtEXEdVlMnaNn19hivMbn1G4JQgq/jArjtKqryXksYX4Hl6A0e"
// java17
import java.util.Properties;
import java.io.FileInputStream;
import java.io.BufferedReader;
import java.io.File;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.List;
import java.util.stream.Collectors;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
//import org.jasypt.spring.boot.annotation.EnableEncryptableProperties;
import com.chohan.portals.PortalService;
import com.chohan.portals.BurlingtonHydro;
import com.chohan.portals.EnbridgeGas;
import com.chohan.portals.Jenkins;
import org.springframework.boot.CommandLineRunner;
import org.springframework.stereotype.Component;
import org.springframework.stereotype.Service;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.beans.factory.annotation.Autowired;
import javax.annotation.PostConstruct;

@SpringBootApplication(scanBasePackages = {"com.chohan.portals", "com.chohan.core"})
public class Login implements CommandLineRunner {

//    @Autowired
//    private EnbridgeGas enbridgeGas;

    //    private final ConfigManager config;
    private String username;
    private String email;
    private String password;
    private final BrowserDriver driverManager;
    private final BrowserOperations operations;
    private final List<PortalService> portalServices;

    public static void main(String[] args) {
        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
        Util.trace();
        SpringApplication.run(Login.class, args);
    }

    // Both beans injected here by Spring
    public Login(BrowserDriver driverManager, BrowserOperations operations, List<PortalService> portalServices) {
        this.driverManager = driverManager;
        this.operations = operations;
        this.portalServices = portalServices;
//        // Exclude specific bean by class or name
//        this.portalServices = portalServices.stream()
//                .filter(bean -> !( (bean instanceof Jenkins)))
//                .collect(Collectors.toList());
    }

    @Override
    public void run(String... args) {
        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
        Util.trace();

        portalServices.forEach(ps -> {
            if (ps instanceof Jenkins)          {System.out.println("Skipping Jenkins"); return;}
//            if (ps instanceof BurlingtonHydro)  {System.out.println("Skipping BurlingtonHydro"); return;}
//            if (ps instanceof EnbridgeGas)      {System.out.println("Skipping EnbridgeGas"); return;}
            try {
                ps.login(operations);
            } catch (Exception ex) {
                System.err.println("Login failed for portal: " + ps.getClass().getSimpleName()
                        + " with error: " + ex.getMessage());
                ex.printStackTrace();
                // Continue to next portal
            }
        });
    }
//	public Login() {
//        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
//        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
//        // call getCredential() to read credentials from application.properties
//        try {
//            getCredential();
//        } catch (Exception ex) {
//            throw new RuntimeException("Failed to get credentials: " + ex.getMessage(), ex);
//        }
//        // Initialize the browser driver and operations
//        driverManager = new BrowserDriver();
//        driverManager.initializeDriver(ConfigManager.getProperty("browser", "firefox"));
//        operations = new BrowserOperations(driverManager);
//        // Perform login to Jenkins
////        Jenkins.login(operations, username, password);
////        BurlingtonHydro.login(operations, email, password);
//        EnbridgeGas.login(operations, email, password);
//        // Close the browser
//        driverManager.getDriver().quit();
//	}
//
//	public void getCredential() throws Exception {
//        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
//        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
//
//        // Get the username and encrypted password from the properties file
//        username = ConfigManager.getProperty("username", null);
//        email = ConfigManager.getProperty("email", null);
//        String decryptedPassword = ConfigManager.getProperty("decrypted_password", null);
//        String passwordFilePath = ConfigManager.getProperty("password_file", null);
//        String passphraseFilePath = ConfigManager.getProperty("passphrase_file", null);
//
//        // validate required properties
//        if (username == null || username.isEmpty()) {
//            throw new RuntimeException("Username not found in properties file. Exiting...");
//        }
//        if (email == null || email.isEmpty()) {
//            throw new RuntimeException("Email not found in properties file. Exiting...");
//        }
//
//        // use decrypted password directly if available
//        if (decryptedPassword != null && !decryptedPassword.isEmpty()) {
//            this.password = decryptedPassword;
//            System.out.println("Username: " + username + ", Email: " + email + ", Password: " + decryptedPassword);
//        } else {
//            // validate password and passphrase file paths
//            if (passwordFilePath == null || passwordFilePath.isEmpty() || passphraseFilePath == null || passphraseFilePath.isEmpty()) {
//                throw new RuntimeException("Either decrypted_password or password_file must be provided in properties file. Exiting...");
//            }
//
//            // validate files exist
//            if (!Files.exists(Paths.get(passwordFilePath)) || !Files.exists(Paths.get(passphraseFilePath))) {
//                    throw new RuntimeException("Password file not found: " + passwordFilePath + " or Passphrase file not found: " + passphraseFilePath + ". Exiting...");
//            }
//            // read passphrase from file
//            String passphrase = new String(Files.readAllBytes(Paths.get(passphraseFilePath))).trim();
//
//            // decrypt password from file
//            password = decryptPasswordFromFile(passwordFilePath, passphrase).trim();
//            if (password == null || password.isEmpty()) {
//                throw new RuntimeException("Decrypted password from file: " + passwordFilePath + " is empty. Exiting...");
//            }
//            System.out.println("Username: " + username + ", Email: " + email + ", Password: " + password);
//        }
//    }
//
//	private String decryptPassword(String encryptedPassword, String passphrase) throws Exception {
//        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
//        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
//
//        // Prepare the PGP command to decrypt the password
//        ProcessBuilder processBuilder = new ProcessBuilder(
//                ConfigManager.getProperty("gpg_path", null),
//                "--batch",
//                "--ignore-mdc-error",
//                "--passphrase", passphrase,
//                "-d", "-");
//        processBuilder.redirectErrorStream(true); // Merge error stream with output stream
//        Process process = processBuilder.start();
//        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
//        StringBuilder decryptedPassword = new StringBuilder();
//        String line;
//        while ((line = reader.readLine()) != null) {
//            decryptedPassword.append(line);
//        }
//        int exitCode = process.waitFor();
//        if (exitCode != 0) {
//            throw new RuntimeException("Failed to decrypt the password. Exit code: " + exitCode);
//        }
//        // Close the reader
//        reader.close();
//        // Return the decrypted password
//        if (decryptedPassword.length() == 0) {
//            throw new RuntimeException("Decrypted password is empty.");
//        }
//        // Remove any trailing newline characters
//        if (decryptedPassword.charAt(decryptedPassword.length() - 1) == '\n') {
//            decryptedPassword.deleteCharAt(decryptedPassword.length() - 1);
//        }
//        if (decryptedPassword.charAt(decryptedPassword.length() - 1) == '\r') {
//            decryptedPassword.deleteCharAt(decryptedPassword.length() - 1);
//        }
//		return decryptedPassword.toString();
//	}
//
//	private String decryptPasswordFromFile(String credentialFilePath, String passphrase) throws Exception {
//        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
//        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
//
//        //  Prepare the PGP command to decrypt the file
//        ProcessBuilder processBuilder = new ProcessBuilder(
//                ConfigManager.getProperty("gpg_path", null),
//                "--batch",
//                "--ignore-mdc-error",
//                "--passphrase", passphrase,
//                "-d",
//                credentialFilePath);
//        processBuilder.redirectErrorStream(true); // Merge error stream with output stream
//        Process process = processBuilder.start();
//        BufferedReader reader = new BufferedReader(new InputStreamReader(process.getInputStream()));
//        StringBuilder decryptedPassword = new StringBuilder();
//        String line;
//        while ((line = reader.readLine()) != null) {
//            decryptedPassword.append(line);
//        }
//        int exitCode = process.waitFor();
//        if (exitCode != 0) {
//            throw new RuntimeException("Failed to decrypt the file. Exit code: " + exitCode);
//        }
//
//		return decryptedPassword.toString();
//	}
}

