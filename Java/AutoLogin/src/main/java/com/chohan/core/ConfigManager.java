package com.chohan.core;

import java.io.FileInputStream;
import java.io.IOException;
import java.util.Properties;
//import com.ulisesbocchio.jasyptspringboot.annotation.EnableEncryptableProperties;
import org.springframework.context.annotation.Configuration;
import org.springframework.beans.factory.annotation.Value;
//import org.springframework.beans.factory.annotation.Getter;
import lombok.Data;

//@EnableEncryptableProperties    // required for springboot 2.4.0 or lower
//@Configuration
//@Data
public class ConfigManager {

    // Browser and driver configurations
    @Value("${chrome.driver.path}")
    private String chromeDriverPath;
    @Value("${firefox.driver.path}")
    private String firefoxDriverPath;
    @Value("${edge.driver.path}")
    private String edgeDriverPath;
    @Value("${browser}")
    private String browser;

    // EnbridgeGas portal configurations
    @Value("${EnbridgeGas.url}")
    private String enbridgeGasUrl;
    @Value("${EnbridgeGas.username}")
    private String enbridgeGasUsername;
    @Value("${EnbridgeGas.password}")
    private String enbridgeGasPassword;

    // BurlingtonHydro portal configurations
    @Value("${BurlingtonHydro.url}")
    private String burlingtonHydroUrl;
    @Value("${BurlingtonHydro.username}")
    private String burlingtonHydroUsername;
    @Value("${BurlingtonHydro.password}")
    private String burlingtonHydroPassword;


//  private static Properties properties = new Properties();
//
//  static {
//    try (FileInputStream fis = new FileInputStream("application.properties")) {
//      properties.load(fis);
//    } catch (IOException e) {
//      throw new RuntimeException("Failed to load application.properties.", e);
//    }
//  }
//
//  public static String getProperty(String key) { return properties.getProperty(key); }
//
//  public static String getProperty(String key, String defaultValue) {
//    return properties.getProperty(key, defaultValue);
//  }
}

