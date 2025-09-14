package com.chohan.core;

import org.openqa.selenium.WebDriver;
import org.openqa.selenium.Dimension;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.firefox.FirefoxDriver;
import org.openqa.selenium.edge.EdgeDriver;
//import org.openqa.selenium.edge.EdgeOptions;
import io.github.bonigarcia.wdm.WebDriverManager;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import javax.annotation.PostConstruct;
import java.nio.file.Files;
import java.nio.file.Paths;

@Component
public class BrowserDriver {

    @Value("${chrome.driver.path}")
    private String chromeDriverPath;
    @Value("${firefox.driver.path}")
    private String firefoxDriverPath;
    @Value("${edge.driver.path}")
    private String edgeDriverPath;
    @Value("${browser}")
    private String browser;

    private WebDriver driver;

    // Method to initialize the WebDriver based on the browser type
    @PostConstruct
    public void initializeDriver() {
        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
        System.out.println("Chrome Driver Path: " + chromeDriverPath);
        System.out.println("Firefox Driver Path: " + firefoxDriverPath);
        System.out.println("Edge Driver Path: " + edgeDriverPath);
        System.out.println("Initializing browser driver for: " + browser);
        String driverPath = null;
        switch (browser.toLowerCase()) {
            case "chrome":
//                driverPath = ConfigManager.getProperty("chrome.driver.path");
                driverPath = chromeDriverPath;
                if (driverPath == null || driverPath.isEmpty() || !Files.exists(Paths.get(driverPath))) {
                    throw new RuntimeException("Firefox driver path is not set correctly in properties file or file does not exist. Exiting...");
                }
                System.setProperty("webdriver.chrome.driver", driverPath);
                WebDriverManager.chromedriver().setup();
                driver = new ChromeDriver();
                break;
            case "firefox":
//                driverPath = ConfigManager.getProperty("firefox.driver.path");
                driverPath = firefoxDriverPath;
                if (driverPath == null || driverPath.isEmpty() || !Files.exists(Paths.get(driverPath))) {
                    throw new RuntimeException("Firefox driver path is not set correctly in properties file or file does not exist. Exiting...");
                }
                System.setProperty("webdriver.gecko.driver", driverPath);
//                WebDriverManager.firefoxdriver().setup();
                driver = new FirefoxDriver();
                break;
            case "edge":
//                driverPath = ConfigManager.getProperty("chrome.driver.path");
                driverPath = edgeDriverPath;
                if (driverPath == null || driverPath.isEmpty() || !Files.exists(Paths.get(driverPath))) {
                    throw new RuntimeException("Firefox driver path is not set correctly in properties file or file does not exist. Exiting...");
                }
                System.setProperty("webdriver.edge.driver", driverPath);
                WebDriverManager.edgedriver().setup();
//                EdgeOptions options = new EdgeOptions();
//                options.addArguments("--headless"); // Run in headless mode
//                options.addArguments("--disable-gpu"); // Disable GPU for compatibility
//                options.addArguments("--window-size=1920,1080"); // Set a default window size
//                options.addArguments("--window-size=800,500"); // Set a default window size
                driver = new EdgeDriver();
                break;
            default:
                throw new IllegalArgumentException("Unsupported browser: " + browser);
        }

        // Set the browser window size to half the screen
        driver.manage().window().maximize();
//        int screenWidth = java.awt.Toolkit.getDefaultToolkit().getScreenSize().width;
//        int screenHeight = java.awt.Toolkit.getDefaultToolkit().getScreenSize().height;
//        driver.manage().window().setSize(new Dimension(screenWidth / 2, screenHeight));
    }

    // Method to navigate to a specific URL
    public void navigateTo(String url) {
        if (driver != null) {
            driver.get(url);
        } else {
            throw new IllegalStateException("Driver is not initialized. Call initializeDriver() first.");
        }
    }

    public void maximizeWindow() {
        if (driver != null) {
            driver.manage().window().maximize();
        } else {
            throw new IllegalStateException("Driver is not initialized. Call initializeDriver() first.");
        }
    }

    // Method to quit the WebDriver
    public void quitDriver() {
        if (driver != null) {
            driver.quit();
            driver = null;
        }
    }

    // Method to get the current WebDriver instance
    public WebDriver getDriver() {
        if (driver == null) {
            throw new IllegalStateException("Driver is not initialized. Call initializeDriver() first.");
        }
        return driver;
    }

    // create a method to get current URL
    public String getCurrentUrl() {
        if (driver != null) {
            return driver.getCurrentUrl();
        } else {
            throw new IllegalStateException("Driver is not initialized. Call initializeDriver() first.");
        }
    }
}
