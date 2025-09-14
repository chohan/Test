package com.chohan.core;

import org.openqa.selenium.By;
import org.openqa.selenium.JavascriptExecutor;
import org.openqa.selenium.NoSuchElementException;
import org.openqa.selenium.TimeoutException;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.support.ui.ExpectedConditions;
import org.openqa.selenium.support.ui.WebDriverWait;
import org.springframework.stereotype.Component;
import java.time.Duration;
import java.util.concurrent.TimeUnit;

@Component
public class BrowserOperations {

    private WebDriver driver;
    private BrowserDriver driverManager;

    public BrowserOperations(BrowserDriver driverManager) {
        StackTraceElement e = Thread.currentThread().getStackTrace()[1];
        System.out.println("\n\n\n################## Salah: " + e.getClassName() + ":" + e.getLineNumber() + " " + e.getMethodName() + "(..) ");
        this.driverManager = driverManager;
        this.driver = driverManager.getDriver();
    }

    public WebDriver getDriver() {
        return this.driver;
    }

    // Method to click on a web element
    public void clickElement(By locator) {
        WebElement element = driver.findElement(locator);
        element.click();
    }

    // Method to enter text into a web element
    public void enterText(By locator, String text) {
        WebElement element = driver.findElement(locator);
        element.clear();
        element.sendKeys(text);
    }

    // Method to get text from a web element
    public String getElementText(By locator) {
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10)); // Wait for up to 10 seconds
        WebElement element = wait.until(ExpectedConditions.presenceOfElementLocated(locator));
        return element.getText();
    }

    public boolean isElementVisible(By locator) {
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(10)); // Wait for up to 10 seconds
        try {
            return wait.until(ExpectedConditions.visibilityOfElementLocated(locator)) != null;
        } catch (TimeoutException e) {
            return false;
        }
    }

    // Method to wait for an element to be visible
    public void waitForElementVisible(By locator, int timeoutInSeconds) {
        WebDriverWait wait = new WebDriverWait(driver, Duration.ofSeconds(timeoutInSeconds));
        wait.until(ExpectedConditions.visibilityOfElementLocated(locator));
    }

    // Method to handle alerts
    public void acceptAlert() {
        driver.switchTo().alert().accept();
    }

    public void dismissAlert() {
        driver.switchTo().alert().dismiss();
    }

    public String getAlertText() {
        return driver.switchTo().alert().getText();
    }

    // Method to switch to a window by title
    public void switchToWindowByTitle(String title) {
        for (String windowHandle : driver.getWindowHandles()) {
            driver.switchTo().window(windowHandle);
            if (driver.getTitle().equals(title)) {
                break;
            }
        }
    }

    // Method to check if an element is present
    public boolean isElementPresent(By locator) {
        try {
            driver.findElement(locator);
            return true;
        } catch (NoSuchElementException e) {
            return false;
        }
    }

    // Method to check if an element is displayed
    public boolean isElementDisplayed(By locator) {
        return driver.findElement(locator).isDisplayed();
    }

    // Method to get the attribute value of an element
    public String getElementAttribute(By locator, String attribute) {
        WebElement element = driver.findElement(locator);
        return element.getAttribute(attribute);
    }

    // Method to scroll to an element
    public void scrollToElement(By locator) {
        WebElement element = driver.findElement(locator);
        ((JavascriptExecutor) driver).executeScript("arguments[0].scrollIntoView(true);", element);
    }

    // Method to navigate to a URL using Driver_Selenium
    public void navigateToUrl(String url) {
        driverManager.navigateTo(url);
    }

    // Method to maximize the browser window using Driver_Selenium
    public void maximizeWindow() {
        driverManager.maximizeWindow();
    }

    // Method to get the current URL using Driver_Selenium
    public String getCurrentUrl() {
        return driverManager.getCurrentUrl();
    }

    // Method to quit the driver using Driver_Selenium
    public void quitDriver() {
        driverManager.quitDriver();
    }

    // Method to get current page title
    public String getPageTitle() {
        return driver.getTitle();
    }
}
