#define _WIN32_WINNT 0x0400
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <winsvc.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <assert.h>
#include <time.h>

using namespace std;
ofstream fout;
std::streambuf* m_pOut_Buf_Save;
string m_sLogFilePath;
CRITICAL_SECTION g_crcLog;

void logInit()
{
	InitializeCriticalSection(&g_crcLog);
	//saving out buffer
	m_sLogFilePath = string("c:\\data\\logfiles\\flogger\\Test3");
	m_pOut_Buf_Save = cout.rdbuf();
	assert(m_pOut_Buf_Save);
}

void logFinish()
{
	//reloading saved buffer
	//cout.rdbuf(fout.rdbuf());
	DeleteCriticalSection(&g_crcLog);
}

void log(const char* method, const char* logEvent, const char* logMsg)
{
	time_t	tNow;
	tm		tmNow;
	char	szDate[80];
	char	szTime[80];
	char	szPathOut[255];
	::time(&tNow);
	localtime_s(&tmNow, &tNow);
	strftime(szDate, 80, "%Y%m%d", &tmNow);
	strftime(szTime, 80, "%H:%M:%S", &tmNow);
	sprintf_s(szPathOut, "%s_%s.log", m_sLogFilePath.c_str(), szDate);

	//opening out/err files
	EnterCriticalSection(&g_crcLog);
	fout.open(szPathOut, ios::app);
	//assert(fout);
	cout << szTime << " " << logEvent << " " << method << " " << logMsg << endl;
	fout << szTime << " " << logEvent << " " << method << " " << logMsg << endl;
	fout.close();
	LeaveCriticalSection(&g_crcLog);
}

void checkMemoryStatus()
{
	MEMORYSTATUS memory;
	GlobalMemoryStatus(&memory);
	ostringstream oss;
	oss << "Available P Memory=" << memory.dwAvailPhys << " Available V Memory=" << memory.dwAvailVirtual;
	log(__FUNCTION__, "INFO", oss.str().c_str());
}


// The name of the service
TCHAR *tsService_Name = _T("BeeperService");
TCHAR *tsService_Description = _T("My test beeper service");
SERVICE_STATUS_HANDLE serviceStatusHandle;
BOOL serviceRunning = FALSE;
BOOL servicePaused = FALSE;
int serviceCurrentStatus;
int beepDelay = 3000;
HANDLE threadHandle;
const int JW_SERVICE_CONTROL_BEEP_NOW = 128;
HANDLE  killServiceEvent;

// ServiceExecutionThread -
//   This is the main thread of execution for the
// service while it is running.
DWORD ServiceExecutionThread(LPDWORD param)
{
	log(__FUNCTION__, "INFO", "IN");
	ostringstream oss;
	oss << "serviceRunning=" << serviceRunning;
	log(__FUNCTION__, "INFO", oss.str().c_str());
	while (serviceRunning)
	{
		//log(__FUNCTION__, "INFO", "beeping");
		checkMemoryStatus();
		Beep(100,100);
		Sleep(beepDelay);
	}
	log(__FUNCTION__, "INFO", "OUT");
	return 0;
}

//to install this as service
void installService(TCHAR *tszServiceName, TCHAR* tszDescription)
{
	SC_HANDLE myService, scm;
	TCHAR szPath[MAX_PATH];

	ostringstream oss;
	oss << "Installing service ...";
	log(__FUNCTION__, "INFO", oss.str().c_str());

    if( !GetModuleFileName( NULL, szPath, MAX_PATH ) )
    {
		ostringstream oss;
		oss << "Cannot install service " << GetLastError();
		log(__FUNCTION__, "INFO", oss.str().c_str());
        return;
    }

	// open a connection to the SCM
	scm = OpenSCManager(0, 0, SC_MANAGER_ALL_ACCESS);//SC_MANAGER_CREATE_SERVICE);
	if (!scm)
	{
	   log(__FUNCTION__, "ERRR", "OpenSCManager fails! " + GetLastError());
	   return;
	}
	log(__FUNCTION__, "INFO", "Opened Service Control Manager...");


	// Install the new service
	myService = CreateService(
	  scm,
	  tszServiceName,	// the internal service name used by the SCM
	  tszServiceName,		// the external label seen in the Service Control applet
	  SERVICE_ALL_ACCESS,	// We want full access to control the service
	  SERVICE_WIN32_OWN_PROCESS,  // The service is a single app and not a driver
	  SERVICE_DEMAND_START,	// The service will be started by us manually
	  SERVICE_ERROR_NORMAL,	// If error during service start, don't misbehave.
	  szPath,
	  0, 0, 0, 0, 0);
	if (!myService)
	{
		ostringstream oss;
		oss << "CreateService fails! " + GetLastError();
		log(__FUNCTION__, "ERRR", oss.str().c_str());
	}
	else
	{
		log(__FUNCTION__, "INFO", "Service successfully installed");
	}
	// clean up
	CloseServiceHandle(myService);
	CloseServiceHandle(scm);
}

//removes service
void removeService()
{
	SC_HANDLE myService, scm;
	BOOL success;
	SERVICE_STATUS status;
	log(__FUNCTION__, "INFO", "Removing Service...");

	// Open a Service Control Manager connection
	scm = OpenSCManager(0, 0, SC_MANAGER_CREATE_SERVICE);
	if (!scm)
	{
		ostringstream oss;
		oss << "OpenSCManager fails! " + GetLastError();
		log(__FUNCTION__, "ERRR", oss.str().c_str());
		return;
	}
	log(__FUNCTION__, "INFO", "Opened Service Control Manager...f");

	// Get the service's handle
	myService = OpenService(scm, tsService_Name, SERVICE_ALL_ACCESS | DELETE);
	if (!myService)
	{
		ostringstream oss;
		oss << "OpenSCManager fails! " + GetLastError();
		log(__FUNCTION__, "ERRR", oss.str().c_str());
		return;
	}

	// Stop the service if necessary
	success = QueryServiceStatus(myService, &status);
	if (!success)
	{
		ostringstream oss;
		oss << "QueryServiceStatus fails! " + GetLastError();
		log(__FUNCTION__, "ERRR", oss.str().c_str());
	}
	if (status.dwCurrentState != SERVICE_STOPPED)
	{
		log(__FUNCTION__, "ERRR", "Service currently active.  Stopping service...");
		success = ControlService(myService, SERVICE_CONTROL_STOP, &status);
		if (!success)
		{
			ostringstream oss;
			oss << "ControlService fails to stop service! " + GetLastError();
			log(__FUNCTION__, "ERRR", oss.str().c_str());
		}
		Sleep(500);
	}

	// Remove the service
	success = DeleteService(myService);
	if (success)
	{
		log(__FUNCTION__, "INFO", "Service successfully removed.");
	}
	else
	{
		ostringstream oss;
		oss << "DeleteService Fails! " + GetLastError();
		log(__FUNCTION__, "ERRR", oss.str().c_str());
	}
	CloseServiceHandle(myService);
	CloseServiceHandle(scm);
}

// StartService -
//   This starts the service by creating its execution thread.
BOOL StartServiceThread()
{
	log(__FUNCTION__, "INFO", "IN");
   DWORD id;
   // Start the service's thread
   threadHandle = CreateThread(0, 0, (LPTHREAD_START_ROUTINE) ServiceExecutionThread, 0, 0, &id);
   if (threadHandle == 0)
   {
      return FALSE;
   }
   else
   {
      serviceRunning = TRUE;
      return TRUE;
   }
	log(__FUNCTION__, "INFO", "OUT");
}

// the killServiceEvent to allow ServiceMain to exit.
void KillService()
{
	log(__FUNCTION__, "INFO", "IN");
	serviceRunning=FALSE;
  // Set the event that is blocking ServiceMain
  // so that ServiceMain can return
	SetEvent(killServiceEvent);
}

void terminateService(DWORD dwCode)
{
	ostringstream oss;
	oss << "GetLastError=" << dwCode;
	log(__FUNCTION__, "INFO", oss.str().c_str());

	//any clean up routines be called here
}

// This function updates the service status for the SCM
BOOL UpdateSCMStatus (DWORD dwCurrentState,
                      DWORD dwWin32ExitCode,
                      DWORD dwServiceSpecificExitCode,
                      DWORD dwCheckPoint,
                      DWORD dwWaitHint)
{
	log(__FUNCTION__, "INFO", "IN");

	BOOL success;
	SERVICE_STATUS serviceStatus;

	// Fill in all of the SERVICE_STATUS fields
	serviceStatus.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	serviceStatus.dwCurrentState = dwCurrentState;
   // If in the process of something, then accept
   // no control events, else accept anything
   if (dwCurrentState == SERVICE_START_PENDING)
   {
      serviceStatus.dwControlsAccepted = 0;
   }
   else
   {
      serviceStatus.dwControlsAccepted =
         SERVICE_ACCEPT_STOP |
         SERVICE_ACCEPT_PAUSE_CONTINUE |
         SERVICE_ACCEPT_SHUTDOWN;
   }
   // if a specific exit code is defines, set up
   // the Win32 exit code properly
   if (dwServiceSpecificExitCode == 0)
   {
      serviceStatus.dwWin32ExitCode = dwWin32ExitCode;
   }
   else
   {
      serviceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
   }
   serviceStatus.dwServiceSpecificExitCode =   dwServiceSpecificExitCode;
   serviceStatus.dwCheckPoint = dwCheckPoint;
   serviceStatus.dwWaitHint = dwWaitHint;
   // Pass the status record to the SCM
   success = SetServiceStatus (serviceStatusHandle, &serviceStatus);
   if (!success)
   {
      KillService();
   }
	log(__FUNCTION__, "INFO", "OUT");
   return success;
}

//   Handles the events dispatched by the Service Control Manager.
VOID ServiceCtrlHandler (DWORD controlCode)
{
	log(__FUNCTION__, "INFO", "IN");
	
	BOOL success;
   switch(controlCode)
   {
      // There is no START option because
      // ServiceMain gets called on a start
      // Pause the service
      case SERVICE_CONTROL_PAUSE:
		log(__FUNCTION__, "INFO", "SERVICE_CONTROL_PAUSE");
         if (serviceRunning && !servicePaused)
         {
            // Tell the SCM we're about to Pause.
            success = UpdateSCMStatus(SERVICE_PAUSE_PENDING, NO_ERROR,
                                      0, 1, 1000);
            servicePaused = TRUE;
            SuspendThread(threadHandle);
            serviceCurrentStatus = SERVICE_PAUSED;
         }
         break;
      // Resume from a pause
      case SERVICE_CONTROL_CONTINUE:
 		log(__FUNCTION__, "INFO", "SERVICE_CONTROL_CONTINUE");
        if (serviceRunning && servicePaused)
         {
            // Tell the SCM we're about to Resume.
            success = UpdateSCMStatus(SERVICE_CONTINUE_PENDING, NO_ERROR, 0,
                                      1, 1000);
            servicePaused=FALSE;
            ResumeThread(threadHandle);
            serviceCurrentStatus = SERVICE_RUNNING;
         }
         break;
      // Beep now in response to our special control message.
      case JW_SERVICE_CONTROL_BEEP_NOW:
 		log(__FUNCTION__, "INFO", "JW_SERVICE_CONTROL_BEEP_NOW");
         Beep(500, 500);
         break;
      // Update the current status for the SCM.
      case SERVICE_CONTROL_INTERROGATE:
  		log(__FUNCTION__, "INFO", "SERVICE_CONTROL_INTERROGATE");
        // This does nothing, here we will just fall through to the end
         // and send our current status.
         break;
      // For a shutdown, we can do cleanup but it must take place quickly
      // because the system will go down out from under us.
      // For this app we have time to stop here, which I do by just falling
      // through to the stop message.
      case SERVICE_CONTROL_SHUTDOWN:
  		log(__FUNCTION__, "INFO", "SERVICE_CONTROL_SHUTDOWN");
      // Stop the service
      case SERVICE_CONTROL_STOP:
  		log(__FUNCTION__, "INFO", "SERVICE_CONTROL_STOP");
         // Tell the SCM we're about to Stop.
         serviceCurrentStatus = SERVICE_STOPPED; //SERVICE_STOP_PENDING;
         success = UpdateSCMStatus(serviceCurrentStatus, NO_ERROR, 0, 1, 5000);
         KillService();
         return;

      default:
  		log(__FUNCTION__, "INFO", "default");
          break;
   }
   UpdateSCMStatus(serviceCurrentStatus, NO_ERROR, 0, 0, 0);
	log(__FUNCTION__, "INFO", "OUT");
}


VOID ServiceMain(DWORD argc, LPTSTR *argv)
{
	log(__FUNCTION__, "INFO", "IN");

	BOOL success;
   // First we must call the Registration function
   serviceStatusHandle = RegisterServiceCtrlHandler(tsService_Name, (LPHANDLER_FUNCTION) ServiceCtrlHandler);
   if (!serviceStatusHandle)
   {
      terminateService(GetLastError());
      return;
   }
   // Next Notify the Service Control Manager of progress
   success = UpdateSCMStatus(SERVICE_START_PENDING, NO_ERROR, 0, 1, 5000);
   if (!success)
   {
      terminateService(GetLastError());
      return;
   }
   // Now create the our service termination event to block on
   killServiceEvent = CreateEvent (0, TRUE, FALSE, 0);
   if (!killServiceEvent)
   {
      terminateService(GetLastError());
      return;
   }
   // Notify the SCM of progress again
   success = UpdateSCMStatus(SERVICE_START_PENDING, NO_ERROR, 0, 2, 1000);
   if (!success)
   {
      terminateService(GetLastError());
      return;
   }
   // Check for a beep delay parameter passed in...
   if (argc == 2)
   {
      int temp = _ttoi(argv[1]);
	  beepDelay = (temp < 1000)? 2000 : temp;
   }
   // Notify the SCM of progress again...
   success = UpdateSCMStatus(SERVICE_START_PENDING, NO_ERROR, 0, 3, 5000);
   if (!success)
   {
      terminateService(GetLastError());
      return;
   }
   // Start the service execution thread by calling our StartServiceThread function...
   success = StartServiceThread();
   if (!success)
   {
      terminateService(GetLastError());
      return;
   }
   // The service is now running.  Notify the SCM of this fact.
   serviceCurrentStatus = SERVICE_RUNNING;
   success = UpdateSCMStatus(SERVICE_RUNNING, NO_ERROR, 0, 0, 0);
   if (!success)
   {
      terminateService(GetLastError());
      return;
   }
   // Now just wait for our killed service signal, and then exit, which
   // terminates the service!
   WaitForSingleObject (killServiceEvent, INFINITE);
   terminateService(0);
	log(__FUNCTION__, "INFO", "OUT");
}







//int main(int argc, char *argv[])
int _tmain(int argc, TCHAR *argv[])
{
	logInit();
	log(__FUNCTION__, "INFO", "***** Service started *****");

	if( argc>1 && (argv[1][0]=='-' || argv[1][0]=='/') )
	{
		if(argv[1][1]=='i')
			installService(tsService_Name, tsService_Description);
		else if(argv[1][1]=='r')
			removeService();
		else
			log(__FUNCTION__, "INFO", "My Servic");

		return 0;
	}

	SERVICE_TABLE_ENTRY serviceTable[2];
	serviceTable[0].lpServiceName = tsService_Name;
	serviceTable[0].lpServiceProc = (LPSERVICE_MAIN_FUNCTION)ServiceMain;
	serviceTable[1].lpServiceName = NULL;
	serviceTable[1].lpServiceProc = NULL;

	BOOL success;
	// Register the service with the Service Control Manager
	success = StartServiceCtrlDispatcher(serviceTable);
	if (!success)
	{
		// This error message would not show up unless we had the "allow service to
		// interact with desktop" option checked, which is unlikely for a console mode
		// app, but we'll print an error message anyway just in case there's someone
		// around to see it.
		ostringstream oss;
		oss << "StartServiceCtrlDispatcher fails! " << GetLastError();
		log(__FUNCTION__, "ERRR", oss.str().c_str());
	}
	log(__FUNCTION__, "INFO", "return code");
	log(__FUNCTION__, "INFO", "***** Service finished *****");
	logFinish();
	return 0;
}


