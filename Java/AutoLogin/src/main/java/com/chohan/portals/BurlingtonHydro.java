package com.chohan.portals;

import com.chohan.core.BrowserOperations;
import com.chohan.core.Util;
import org.openqa.selenium.By;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.JavascriptExecutor;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import java.time.Duration;

@Service
public class BurlingtonHydro implements PortalService {

    public static final String USERNAME_FIELD = "mat-input-0";
    public static final String PASSWORD_FIELD = "mat-input-1";
    public static final String LOGIN_BUTTON = "button[uxlib-btn-signin][type='submit']";
//    public static final String LOGIN_BUTTON = "button[type='submit']";
//    public static final String LOGIN_BUTTON = "button[type='submit'] span.mat-button-wrapper";
    public static final String LOGIN_SUCCESS_MESSAGE = "my-london-hydro";
    public static final String LOGIN_ERROR_MESSAGE = "error_message_element";
    private String loginUrl;
    private String username;
    private String password;
    private boolean shouldLogin;

    public BurlingtonHydro(@Value("${BurlingtonHydro.url}") String loginUrl,
                           @Value("${BurlingtonHydro.username}") String username,
                           @Value("${BurlingtonHydro.password}") String password,
                           @Value("${BurlingtonHydro.login:false}") boolean shouldLogin) {
        Util.trace();
        System.out.println("BurlingtonHydro portal initialized with URL: " + loginUrl + ", Username: " + username + ", Password: " + password);
        this.loginUrl = loginUrl;
        this.username = username;
        this.password = password;
        this.shouldLogin = shouldLogin;
    }

    @Override
    public void login(BrowserOperations operations) {
        Util.trace();
        System.out.println("URL: " + loginUrl + ", Username: " + username + ", Password: " + password + ", shouldLogin: " + shouldLogin);
        if (!shouldLogin) {
            System.out.println("Login skipped for " + Util.getClassname());
            return;
        }
        // Navigate to the Jenkins login page
        operations.getDriver().get(loginUrl);
        // Wait for the username field to be visible
        WebDriverWait wait = new WebDriverWait(operations.getDriver(), Duration.ofSeconds(10));
        wait.until(ExpectedConditions.visibilityOfElementLocated(By.id(USERNAME_FIELD)));
        // Enter the username
        operations.enterText(By.id(USERNAME_FIELD), username);
        // Enter the password
        operations.enterText(By.id(PASSWORD_FIELD), password);
        // Find the button
        WebElement button = operations.getDriver().findElement(By.cssSelector(LOGIN_BUTTON));
        // Scroll into view
        ((JavascriptExecutor) operations.getDriver()).executeScript("arguments[0].scrollIntoView(true);", button);
        wait.until(ExpectedConditions.elementToBeClickable(button));
        button.click();
        // Click the login button
//        wait.until(ExpectedConditions.elementToBeClickable(By.cssSelector(LOGIN_BUTTON)));
//        operations.clickElement(By.cssSelector(LOGIN_BUTTON));

        // Wait for either success or error message
        try {
            wait.until(ExpectedConditions.visibilityOfElementLocated(By.className(LOGIN_SUCCESS_MESSAGE)));
            System.out.println("Login successful.");
        } catch (Exception ex) {
            // Only check for error if success not found
            try {
                String errorMessage = operations.getElementText(By.id(LOGIN_ERROR_MESSAGE));
                System.out.println("Login failed: " + errorMessage);
                throw new RuntimeException("Login failed: " + errorMessage);
            } catch (Exception innerEx) {
                System.out.println("Login failed: Unknown error.");
                throw new RuntimeException("Login failed: Unknown error.");
            }
        }
    }
    // Add other constants and methods as needed
}
