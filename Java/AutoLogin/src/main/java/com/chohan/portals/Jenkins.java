package com.chohan.portals;

import com.chohan.core.BrowserOperations;
import org.openqa.selenium.By;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.springframework.beans.factory.annotation.Value;
import java.time.Duration;

public class Jenkins implements PortalService {

    private String url;
    private String username;
    private String password;

	public static final String loginUrl = "http://.....";
	public static final String USERNAME_FIELD = "j_username";
	public static final String PASSWORD_FIELD = "j_password";
	public static final String LOGIN_BUTTON = "Submit";
	public static final String LOGIN_SUCCESS_MESSAGE = "success_message_element";
	public static final String LOGIN_ERROR_MESSAGE = "error_message_element";

    public Jenkins(@Value("${Jenkins.url}") String url,
                   @Value("${Jenkins.username}") String username,
                   @Value("${Jenkins.password}") String password) {
        super();
        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
        System.out.println("EnbridgeGas portal initialized with URL: " + url + ", Username: " + username + ", Password: " + password);
        this.url = url;
        this.username = username;
        this.password = password;
    }

    @Override
    public void login(BrowserOperations operations) {

        // Navigate to the Jenkins login page
        operations.getDriver().get(loginUrl);
        // Wait for the username field to be visible
        WebDriverWait wait = new WebDriverWait(operations.getDriver(), Duration.ofSeconds(10));
        wait.until(ExpectedConditions.visibilityOfElementLocated(By.name(USERNAME_FIELD)));
        // Enter the username
        operations.enterText(By.name(USERNAME_FIELD), username);
        // Enter the password
        operations.enterText(By.name(PASSWORD_FIELD), password);
        // Click the login button
        operations.clickElement(By.name(LOGIN_BUTTON));
        // Wait for the login to complete and check for success or error messages
        try {
            wait.until(ExpectedConditions.visibilityOfElementLocated(By.id(LOGIN_SUCCESS_MESSAGE)));
            System.out.println("Login successful.");
        } catch (Exception e) {
            String errorMessage = operations.getElementText(By.id(LOGIN_ERROR_MESSAGE));
            System.out.println("Login failed: " + errorMessage);
            throw new RuntimeException("Login failed: " + errorMessage);
        }

	}

}

