@echo off
REM Define the base path for the project
set basePath=C:\dev\Projects\AutoLogin
 
REM Set the date in YYYYMMDD format
for /f "tokens=2 delims==" %%I in ('wmic os get localdatetime /value ^| find "="') do set datetime=%%I
set logDate=%datetime:~0,8%
 
REM Define the log file path
set logFile=%basePath%\logs\autologin_%logDate%.log
 
REM Ensure the logs directory exists
if not exist %basePath%\logs (
    mkdir %basePath%\logs
)
 
REM Change the working directory to the base path
cd /d %basePath%
 
REM Add 3 blank lines and the current date and time to the log file
echo. >> %logFile%
echo. >> %logFile%
echo. >> %logFile%
echo ============= >> %logFile%
echo %date% %time% >> %logFile%
 
REM Run the Java application and redirect output and error to both console and log file in real-time
powershell -Command "& { %JAVA_HOME%\bin\java -jar 'target\AutoLoginProject-1.0-SNAPSHOT.jar' 2>&1 | ForEach-Object { $_; Add-Content -Path 'logs\autologin_%logDate%.log' -Value $_ } }"
 
REM Exit the script
exit /b
