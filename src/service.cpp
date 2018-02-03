#define _CRT_SECURE_NO_WARNINGS 1 
#include <windows.h>
#include "service.h"

/******************************************************************************************************************************/
// BOOL ServiceInstall(LPCTSTR ServiceName, LPCTSTR BinaryPathName, DWORD dwServiceType, DWORD dwStartType)
/******************************************************************************************************************************/
BOOL ServiceInstall(LPCTSTR ServiceName, LPCTSTR BinaryPathName, DWORD dwServiceType, DWORD dwStartType)
{
   SC_HANDLE	SchSCManager;
   SC_HANDLE    schService;
   DWORD	dwLastError;
   SchSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
   if (SchSCManager == NULL)
	   return FALSE;
   schService = CreateService (SchSCManager,          // SCManager database
			       ServiceName,           // name of service
			       ServiceName,           // name to display
                               SERVICE_ALL_ACCESS,    // desired access
			       dwServiceType,	       // service type
			       dwStartType,           // start type
                               SERVICE_ERROR_NORMAL,  // error control type
			       BinaryPathName,        // service's binary
                               NULL,                  // no load ordering group
                               NULL,                  // no tag identifier
                               NULL,                  // no dependencies
                               NULL,                  // LocalSystem account
                               NULL                   // no password
                               );

    if (schService == NULL)
    {
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
        return FALSE;
    }
	CloseServiceHandle(SchSCManager);
	CloseServiceHandle(schService);
	return TRUE;
}
/******************************************************************************************************************************/
// BOOL ServiceRemove(LPCTSTR ServiceName)
/******************************************************************************************************************************/
BOOL ServiceRemove(LPCTSTR ServiceName)
{
    SC_HANDLE	SchSCManager;
    SC_HANDLE	schService;
    DWORD	dwLastError;
    SchSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (SchSCManager == NULL)
	    return FALSE;
    schService = OpenService (SchSCManager,ServiceName,SERVICE_ALL_ACCESS);
    if (schService == NULL)
    {
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
    }
    if (!DeleteService(schService))
    {
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
	}
	CloseServiceHandle(SchSCManager);
	CloseServiceHandle(schService);
    return TRUE;
}
/******************************************************************************************************************************/
// BOOL ServiceStart(LPCTSTR ServiceName)
/******************************************************************************************************************************/
BOOL ServiceStart(LPCSTR ServiceName)
{
	SC_HANDLE		SchSCManager;
	SC_HANDLE		schService;
	DWORD			dwLastError;
	SERVICE_STATUS	status;
	SchSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (SchSCManager == NULL)
		return FALSE;
	schService = OpenService(SchSCManager, ServiceName, SERVICE_START);
	if (schService == NULL)
	{
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
	}
	if (!StartService(schService, 0, NULL))
	{
		dwLastError = GetLastError();
		if (dwLastError == ERROR_SERVICE_ALREADY_RUNNING)
		{
			if (QueryServiceStatus(schService, &status))
			{
				if (status.dwCurrentState == SERVICE_STOP_PENDING)
					dwLastError = ERROR_SERVICE_CANNOT_ACCEPT_CTRL;
			}
			else
				dwLastError = GetLastError();
		}
		CloseServiceHandle(schService);
		CloseServiceHandle(SchSCManager);
		SetLastError(dwLastError);
		if (dwLastError == ERROR_SERVICE_ALREADY_RUNNING)
			return TRUE;
		else
			return FALSE;
	}
	CloseServiceHandle(SchSCManager);
	CloseServiceHandle(schService);
	return TRUE;
}
/******************************************************************************************************************************/
// BOOL ServiceStop(LPCTSTR ServiceName)
/******************************************************************************************************************************/
BOOL ServiceStop(LPCTSTR ServiceName)
{
    SC_HANDLE		SchSCManager;
    SC_HANDLE		schService;
    DWORD		dwLastError;
    SERVICE_STATUS	serviceStatus;
    SchSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
    if (SchSCManager == NULL)
	    return FALSE;
    schService = OpenService (SchSCManager,ServiceName,SERVICE_ALL_ACCESS);
    if (schService == NULL)
    {
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
    }
    if (!ControlService(schService, SERVICE_CONTROL_STOP, &serviceStatus))
	{
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
    }
	CloseServiceHandle(SchSCManager);
	CloseServiceHandle(schService);
	return TRUE;
}
/******************************************************************************************************************************/
// BOOL ServiceExists(LPCTSTR ServiceName)
/******************************************************************************************************************************/
BOOL ServiceExists(LPCTSTR ServiceName)
{
	SC_HANDLE	SchSCManager;
	SC_HANDLE	schService;
	DWORD		dwLastError;
	SchSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (SchSCManager == NULL)
		return FALSE;
	schService = OpenService(SchSCManager, ServiceName, SERVICE_ALL_ACCESS);
	if (schService == NULL)
	{
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
	}
	CloseServiceHandle(SchSCManager);
	CloseServiceHandle(schService);
	return TRUE;
}
/******************************************************************************************************************************/
// BOOL ServiceRunning(LPCTSTR ServiceName)
/******************************************************************************************************************************/
BOOL ServiceRunning(LPCTSTR ServiceName)
{
	SC_HANDLE	   SchSCManager;
	SC_HANDLE	   schService;
	DWORD		   dwLastError;
	SERVICE_STATUS status;
	SchSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
	if (SchSCManager == NULL)
		return FALSE;
	schService = OpenService(SchSCManager, ServiceName, SERVICE_ALL_ACCESS);
	if (schService == NULL)
	{
		dwLastError = GetLastError();
		SetLastError(dwLastError);
		CloseServiceHandle(SchSCManager);
		CloseServiceHandle(schService);
		return FALSE;
	}
	if (QueryServiceStatus(schService, &status))
	{
		if (status.dwCurrentState == SERVICE_RUNNING)
		{
			CloseServiceHandle(SchSCManager);
			CloseServiceHandle(schService);
			return TRUE;
		}
	}
	CloseServiceHandle(SchSCManager);
	CloseServiceHandle(schService);
	return FALSE;
}
/******************************************************************************************************************************/
// BOOL OpenDevice(LPCTSTR ServiceName)
/******************************************************************************************************************************/
BOOL OpenDevice(LPCTSTR ServiceName)
{
    char		completeDeviceName[64] = "";
    LPCTSTR		dosDeviceName = ServiceName;
    HANDLE		hDevice;
    strcat (completeDeviceName,"\\\\.\\");
    strcat (completeDeviceName,dosDeviceName);
    hDevice = CreateFile (completeDeviceName,
                          GENERIC_READ | GENERIC_WRITE,
                          0,
                          NULL,
                          OPEN_EXISTING,
                          FILE_ATTRIBUTE_NORMAL,
                          NULL
                          );
	if (hDevice == ((HANDLE)-1))
	{
		CloseHandle(hDevice);
		return FALSE;
	}
	CloseHandle(hDevice);
    return TRUE;
}
/******************************************************************************************************************************/
