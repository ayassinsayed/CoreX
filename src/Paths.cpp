#pragma once
#define _CRT_SECURE_NO_WARNINGS 1 

#include <Windows.h>
#include <Shlobj.h>
#include <Knownfolders.h>
#include <time.h>
#include "Paths.h"

//#if (_WIN32_WINNT >= _WIN32_WINNT_VISTA)
//if (!GetFileVersionInfoExW(FILE_VER_GET_NEUTRAL, path, 0, len, buff.get()))
//#else
//if (!GetFileVersionInfoW(path, 0, len, buff.get()))
//#endif
/******************************************************************************************************************************/
// LPSTR GetOSArch()
/******************************************************************************************************************************/
LPSTR GetOSArch()
{
	SYSTEM_INFO lpSystemInfo;
	GetNativeSystemInfo(&lpSystemInfo);
	switch(lpSystemInfo.wProcessorArchitecture)
	{
	case PROCESSOR_ARCHITECTURE_INTEL:
		return "PROCESSOR_ARCHITECTURE_INTEL";
		break;
	case PROCESSOR_ARCHITECTURE_MIPS:
		return "PROCESSOR_ARCHITECTURE_MIPS";
		break;
	case PROCESSOR_ARCHITECTURE_ALPHA:
		return "PROCESSOR_ARCHITECTURE_ALPHA";
		break;
	case PROCESSOR_ARCHITECTURE_PPC:
		return "PROCESSOR_ARCHITECTURE_PPC";
		break;
	case PROCESSOR_ARCHITECTURE_SHX:
		return "PROCESSOR_ARCHITECTURE_SHX";
		break;
	case PROCESSOR_ARCHITECTURE_ARM:
		return "PROCESSOR_ARCHITECTURE_ARM";
		break;
	case PROCESSOR_ARCHITECTURE_IA64:
		return "PROCESSOR_ARCHITECTURE_IA64";
		break;
	case PROCESSOR_ARCHITECTURE_ALPHA64:
		return "PROCESSOR_ARCHITECTURE_ALPHA64";
		break;
	case PROCESSOR_ARCHITECTURE_MSIL:
		return "PROCESSOR_ARCHITECTURE_MSIL";
		break;
	case PROCESSOR_ARCHITECTURE_AMD64:
		return "PROCESSOR_ARCHITECTURE_AMD64";
		break;
	case PROCESSOR_ARCHITECTURE_IA32_ON_WIN64:
		return "PROCESSOR_ARCHITECTURE_IA32_ON_WIN64";
		break;
	case PROCESSOR_ARCHITECTURE_NEUTRAL:
		return "PROCESSOR_ARCHITECTURE_NEUTRAL";
		break;
	case PROCESSOR_ARCHITECTURE_UNKNOWN:
		return "PROCESSOR_ARCHITECTURE_UNKNOWN";
		break;
	default:
		return "PROCESSOR_ARCHITECTURE_UNKNOWN";
		break;
	}
}
/******************************************************************************************************************************/
// LPSTR GetOsVersion()
/******************************************************************************************************************************/
LPSTR GetOsVersion()
{
	NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandle("ntdll"), "RtlGetVersion");
	if (RtlGetVersion)
		RtlGetVersion(&osvi);
	if (osvi.wProductType == VER_NT_WORKSTATION)
	{
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 0)
			return "_WIN32_WINNT_WIN2K";
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 1)
			return "_WIN32_WINNT_WINXP";
		else if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
			return "_WIN32_WINNT_WINXP64";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
			return "_WIN32_WINNT_VISTA";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
			return "_WIN32_WINNT_WIN7";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
			return "_WIN32_WINNT_WIN8";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3)
			return "_WIN32_WINNT_WINBLUE";
		else if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0)
			return "_WIN32_WINNT_WIN10";
	}
	else if (osvi.wProductType == VER_NT_DOMAIN_CONTROLLER || osvi.wProductType == VER_NT_SERVER)
	{
		if (osvi.dwMajorVersion == 5 && osvi.dwMinorVersion == 2)
			return "_WIN32_WINNT_WS03";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 0)
			return "_WIN32_WINNT_WS08";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 1)
			return "_WIN32_WINNT_WS08R2";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 2)
			return "_WIN32_WINNT_WS12";
		else if (osvi.dwMajorVersion == 6 && osvi.dwMinorVersion == 3)
			return "_WIN32_WINNT_WS12R2";
		else if (osvi.dwMajorVersion == 10 && osvi.dwMinorVersion == 0)
			return "_WIN32_WINNT_WS16";
	}
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetOSServicePack()
/******************************************************************************************************************************/
LPSTR GetOSServicePack()
{
	NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osvi;
	LPSTR            szCSDVersion = new char[128];
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandle("ntdll"), "RtlGetVersion");
	if (RtlGetVersion)
		RtlGetVersion(&osvi);
	wcstombs(szCSDVersion, osvi.szCSDVersion, 128);
	if (strlen(szCSDVersion) > 0)
		return szCSDVersion;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetOsProductInfo()
/******************************************************************************************************************************/
LPSTR GetOsProductInfo()
{
	NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osvi;
	DWORD			 dwType;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandle("ntdll"), "RtlGetVersion");
	if (RtlGetVersion)
		RtlGetVersion(&osvi);
	GetProductInfo( osvi.dwMajorVersion, osvi.dwMinorVersion, 0, 0, &dwType);;
	switch (dwType)
	{
	case PRODUCT_ULTIMATE:
		return "PRODUCT_ULTIMATE";
		break;
	case PRODUCT_PROFESSIONAL:
		return "PRODUCT_PROFESSIONAL";
		break;
	case PRODUCT_HOME_PREMIUM:
		return "Home Premium";
		break;
	case PRODUCT_HOME_BASIC:
		return "PRODUCT_HOME_PREMIUM";
		break;
	case PRODUCT_ENTERPRISE:
		return "PRODUCT_ENTERPRISE";
		break;
	case PRODUCT_BUSINESS:
		return "PRODUCT_BUSINESS";
		break;
	case PRODUCT_STARTER:
		return "PRODUCT_STARTER";
		break;
	case PRODUCT_CLUSTER_SERVER:
		return "PRODUCT_CLUSTER_SERVER";
		break;
	case PRODUCT_DATACENTER_SERVER:
		return "PRODUCT_DATACENTER_SERVER";
		break;
	case PRODUCT_DATACENTER_SERVER_CORE:
		return "PRODUCT_DATACENTER_SERVER_CORE";
		break;
	case PRODUCT_ENTERPRISE_SERVER:
		return "PRODUCT_ENTERPRISE_SERVER";
		break;
	case PRODUCT_ENTERPRISE_SERVER_CORE:
		return "PRODUCT_ENTERPRISE_SERVER_CORE";
		break;
	case PRODUCT_ENTERPRISE_SERVER_IA64:
		return "PRODUCT_ENTERPRISE_SERVER_IA64";
		break;
	case PRODUCT_SMALLBUSINESS_SERVER:
		return "PRODUCT_SMALLBUSINESS_SERVER";
		break;
	case PRODUCT_SMALLBUSINESS_SERVER_PREMIUM:
		return "PRODUCT_SMALLBUSINESS_SERVER_PREMIUM";
		break;
	case PRODUCT_STANDARD_SERVER:
		return "PRODUCT_STANDARD_SERVER";
		break;
	case PRODUCT_STANDARD_SERVER_CORE:
		return "PRODUCT_STANDARD_SERVER_CORE";
		break;
	case PRODUCT_WEB_SERVER:
		return "PRODUCT_WEB_SERVER";
		break;
	default:
		return NULL;
		break;
	}
}
/******************************************************************************************************************************/
// DWORD GetOSBuild()
/******************************************************************************************************************************/
DWORD GetOSBuild()
{
	NTSTATUS(WINAPI *RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osvi;
	osvi.dwOSVersionInfoSize = sizeof(osvi);
	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandle("ntdll"), "RtlGetVersion");
	if (RtlGetVersion)
		RtlGetVersion(&osvi);
	return osvi.dwBuildNumber;
}
/******************************************************************************************************************************/
// DWORD GetModuleSize(LPCSTR ModuleName)
/******************************************************************************************************************************/
DWORD GetModuleSize(LPCSTR ModuleName)
{
	HMODULE hModule = GetModuleHandle(ModuleName);
	PIMAGE_DOS_HEADER IMAGE_DOS_HEADER = (PIMAGE_DOS_HEADER)hModule;
	PIMAGE_NT_HEADERS IMAGE_NT_HEADERS = (PIMAGE_NT_HEADERS)((PBYTE)hModule + IMAGE_DOS_HEADER->e_lfanew);
	PIMAGE_SECTION_HEADER IMAGE_SECTION_HEADER = (PIMAGE_SECTION_HEADER)((PBYTE)IMAGE_NT_HEADERS + sizeof(IMAGE_NT_HEADERS32));
	DWORD maxpointer = 0, size = 0;
	for (int i = 0; i < IMAGE_NT_HEADERS->FileHeader.NumberOfSections; ++i)
	{
		if (IMAGE_SECTION_HEADER->PointerToRawData > maxpointer)
		{
			maxpointer = IMAGE_SECTION_HEADER->PointerToRawData;
			size = IMAGE_SECTION_HEADER->PointerToRawData + IMAGE_SECTION_HEADER->SizeOfRawData;
		}
		IMAGE_SECTION_HEADER++;
	}
	return size;
}
/******************************************************************************************************************************/
// LPSTR GetModuleFullPath()
/******************************************************************************************************************************/
LPSTR GetModuleFullPath()
{
	LPSTR szPath = new char[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetModuleName()
/******************************************************************************************************************************/
LPSTR GetModuleName()
{
	LPSTR szPath = new char[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	string stValue = szPath;
	stValue = stValue.substr(stValue.find_last_of('\\') + 1);
	return strcpy(szPath, stValue.c_str());
}
/******************************************************************************************************************************/
// LPSTR GetModuleDrive()
/******************************************************************************************************************************/
LPSTR GetModuleDrive()
{
	LPSTR szPath = new char[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	string stValue = szPath;
	stValue = stValue.substr(0, stValue.find_first_of('\\') + 1);
	return strcpy(szPath, stValue.c_str());
}
/******************************************************************************************************************************/
// LPSTR GetModuleDir()
/******************************************************************************************************************************/
LPSTR GetModuleDir()
{
	LPSTR szPath = new char[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	string stValue = szPath;
	stValue = stValue.substr(0, stValue.find_last_of('\\') + 1);
	return strcpy(szPath, stValue.c_str());
}
/******************************************************************************************************************************/
// LPSTR GetWorkingDir()
/******************************************************************************************************************************/
LPSTR GetWorkingDir()
{
	LPSTR szPath = new char[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, szPath);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetTempDir()
/******************************************************************************************************************************/
LPSTR GetTempDir()
{
	LPSTR szPath = new char[MAX_PATH];
	GetTempPath(MAX_PATH, szPath);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetHomeDrive()
/******************************************************************************************************************************/
LPSTR GetHomeDrive()
{
	LPSTR szPath = new char[MAX_PATH];
	GetEnvironmentVariable("HOMEDRIVE", szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetHomePath()
/******************************************************************************************************************************/
LPSTR GetHomePath()
{
	LPSTR szPath = new char[MAX_PATH];
	GetEnvironmentVariable("HOMEPATH", szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetHomeShare()
/******************************************************************************************************************************/
LPSTR GetHomeShare()
{
	LPSTR szPath = new char[MAX_PATH];
	GetEnvironmentVariable("HOMESHARE", szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR _GetUserName()
/******************************************************************************************************************************/
LPSTR _GetUserName()
{
	LPSTR szPath = new char[MAX_PATH];
	DWORD dwTemp = MAX_PATH;
	GetUserName(szPath, &dwTemp);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR _GetComputerName()
/******************************************************************************************************************************/
LPSTR _GetComputerName()
{
	LPSTR szPath = new char[MAX_PATH];
	DWORD dwTemp = MAX_PATH;
	GetComputerName(szPath, &dwTemp);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetLogonServer()
/******************************************************************************************************************************/
LPSTR GetLogonServer()
{
	LPSTR szPath = new char[MAX_PATH];
	GetEnvironmentVariable("LOGONSERVER", szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetLogonDNSDomain()
/******************************************************************************************************************************/
LPSTR GetLogonDNSDomain()
{
	LPSTR szPath = new char[MAX_PATH];
	GetEnvironmentVariable("USERDNSDOMAIN", szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetLogonDomain()
/******************************************************************************************************************************/
LPSTR GetLogonDomain()
{
	LPSTR szPath = new char[MAX_PATH];
	GetEnvironmentVariable("USERDOMAIN", szPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetComSpec()
/******************************************************************************************************************************/
LPSTR GetComSpec()
{
	LPSTR szValue = new char[MAX_PATH];
	GetEnvironmentVariable("COMSPEC", szValue, MAX_PATH);
	return szValue;
}
/******************************************************************************************************************************/
// LPSTR GetAccountPicturesDir()
/******************************************************************************************************************************/
LPSTR GetAccountPicturesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AccountPictures, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetAddNewProgramsDir()
/******************************************************************************************************************************/
LPSTR GetAddNewProgramsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AddNewPrograms, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}

/******************************************************************************************************************************/
// LPSTR GetAdminToolsDir()
/******************************************************************************************************************************/
LPSTR GetAdminToolsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_ADMINTOOLS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetAppDataDesktopDir()
/******************************************************************************************************************************/
LPSTR GetAppDataDesktopDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppDataDocuments, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetAppDataDocumentsDir()
/******************************************************************************************************************************/
LPSTR GetAppDataDocumentsDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppDataDocuments, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetAppDataFavoritesDir()
/******************************************************************************************************************************/
LPSTR GetAppDataFavoritesDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppDataFavorites, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetAppDataProgramDataDir()
/******************************************************************************************************************************/
LPSTR GetAppDataProgramDataDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppDataProgramData , 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetApplicationShortcutsDir()
/******************************************************************************************************************************/
LPSTR GetApplicationShortcutsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppsFolder, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetAppsFolderDir()
/******************************************************************************************************************************/
LPSTR GetAppsFolderDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppsFolder, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetAppUpdatesDir()
/******************************************************************************************************************************/
LPSTR GetAppUpdatesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_AppUpdates, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetCameraRollDir()
/******************************************************************************************************************************/
LPSTR GetCameraRollDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_CameraRoll, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetGetGetCDBurningDir()
/******************************************************************************************************************************/
LPSTR GetGetGetCDBurningDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_CDBURN_AREA, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetChangeRemoveProgramsDir()
/******************************************************************************************************************************/
LPSTR GetChangeRemoveProgramsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ChangeRemovePrograms, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetCommonAdminToolsDir()
/******************************************************************************************************************************/
LPSTR GetCommonAdminToolsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_ADMINTOOLS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetCommonOEMLinksDir()
/******************************************************************************************************************************/
LPSTR GetCommonOEMLinksDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_OEM_LINKS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetCommonProgramsDir()
/******************************************************************************************************************************/
LPSTR GetCommonProgramsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_PROGRAMS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetCommonStartMenuDir()
/******************************************************************************************************************************/
LPSTR GetCommonStartMenuDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_STARTMENU, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetCommonStartupDir()
/******************************************************************************************************************************/
LPSTR GetCommonStartupDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_STARTUP, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetCommonTemplatesDir()
/******************************************************************************************************************************/
LPSTR GetCommonTemplatesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_TEMPLATES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetComputerFolderDir()
/******************************************************************************************************************************/
LPSTR GetComputerFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DRIVES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetConflictFolderDir()
/******************************************************************************************************************************/
LPSTR GetConflictFolderDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ConflictFolder, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetConnectionsFolderDir()
/******************************************************************************************************************************/
LPSTR GetConnectionsFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_CONNECTIONS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetContactsDir()
/******************************************************************************************************************************/
LPSTR GetContactsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Contacts, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetControlPanelFolderDir()
/******************************************************************************************************************************/
LPSTR GetControlPanelFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_CONTROLS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetCookiesDir()
/******************************************************************************************************************************/
LPSTR GetCookiesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COOKIES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetDesktopDir()
/******************************************************************************************************************************/
LPSTR GetDesktopDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOP, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetDeviceMetadataStoreDir()
/******************************************************************************************************************************/
LPSTR GetDeviceMetadataStoreDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_DeviceMetadataStore, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetMyDocumentsDir()
/******************************************************************************************************************************/
LPSTR GetMyDocumentsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetDocumentsLibraryDir()
/******************************************************************************************************************************/
LPSTR GetDocumentsLibraryDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_DocumentsLibrary, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetDownloadsDir()
/******************************************************************************************************************************/
LPSTR GetDownloadsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Downloads, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetFavoritesDir()
/******************************************************************************************************************************/
LPSTR GetFavoritesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_FAVORITES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetFontsDir()
/******************************************************************************************************************************/
LPSTR GetFontsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_FONTS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetGamesDir()
/******************************************************************************************************************************/
LPSTR GetGamesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Games, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetGameTasksDir()
/******************************************************************************************************************************/
LPSTR GetGameTasksDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_GameTasks, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetHistoryDir()
/******************************************************************************************************************************/
LPSTR GetHistoryDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_HISTORY, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetHomeGroupDir()
/******************************************************************************************************************************/
LPSTR GetHomeGroupDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_HomeGroup, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetHomeGroupCurrentUserDir()
/******************************************************************************************************************************/
LPSTR GetHomeGroupCurrentUserDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_HomeGroupCurrentUser, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetImplicitAppShortcutsDir()
/******************************************************************************************************************************/
LPSTR GetImplicitAppShortcutsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ImplicitAppShortcuts, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetInternetCacheDir()
/******************************************************************************************************************************/
LPSTR GetInternetCacheDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_INTERNET_CACHE, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetInternetFolderDir()
/******************************************************************************************************************************/
LPSTR GetInternetFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_INTERNET, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetLibrariesDir()
/******************************************************************************************************************************/
LPSTR GetLibrariesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Libraries, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetLinksDir()
/******************************************************************************************************************************/
LPSTR GetLinksDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Links, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetLocalAppDataDir()
/******************************************************************************************************************************/
LPSTR GetLocalAppDataDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_LOCAL_APPDATA, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetLocalAppDataLowDir()
/******************************************************************************************************************************/
LPSTR GetLocalAppDataLowDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppDataLow, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetLocalizedResourcesDir()
/******************************************************************************************************************************/
LPSTR GetLocalizedResourcesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_RESOURCES_LOCALIZED, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetMyMusicDir()
/******************************************************************************************************************************/
LPSTR GetMyMusicDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYMUSIC, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetMusicLibraryDir()
/******************************************************************************************************************************/
LPSTR GetMusicLibraryDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_MusicLibrary, 0, NULL, &ppszPath)))
	wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetNetHoodDir()
/******************************************************************************************************************************/
LPSTR GetNetHoodDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_NETHOOD, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetNetworkFolderDir()
/******************************************************************************************************************************/
LPSTR GetNetworkFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_NETWORK, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetObjects3DDir()
/******************************************************************************************************************************/
LPSTR GetObjects3DDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Objects3D, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetOriginalImagesDir()
/******************************************************************************************************************************/
LPSTR GetOriginalImagesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_OriginalImages, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPhotoAlbumsDir()
/******************************************************************************************************************************/
LPSTR GetPhotoAlbumsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PhotoAlbums, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPicturesLibraryDir()
/******************************************************************************************************************************/
LPSTR GetPicturesLibraryDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PicturesLibrary, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetMyPicturesDir()
/******************************************************************************************************************************/
LPSTR GetMyPicturesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYPICTURES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPlaylistsDir()
/******************************************************************************************************************************/
LPSTR GetPlaylistsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Playlists, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPrintersFolderDir()
/******************************************************************************************************************************/
LPSTR GetPrintersFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PRINTERS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPrintersDir()
/******************************************************************************************************************************/
LPSTR GetPrintHoodDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PRINTHOOD, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetUserProfileDir()
/******************************************************************************************************************************/
LPSTR GetUserProfileDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetProgramDataDir()
/******************************************************************************************************************************/
LPSTR GetProgramDataDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_APPDATA, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetProgramFilesDir()
/******************************************************************************************************************************/
LPSTR GetProgramFilesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramFiles, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetProgramFilesX64Dir()
/******************************************************************************************************************************/
LPSTR GetProgramFilesX64Dir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramFilesX64, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetProgramFilesX86Dir()
/******************************************************************************************************************************/
LPSTR GetProgramFilesX86Dir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramFilesX86, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetProgramFilesCommonDir()
/******************************************************************************************************************************/
LPSTR GetProgramFilesCommonDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES_COMMON, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetProgramFilesCommonX64Dir()
/******************************************************************************************************************************/
LPSTR GetProgramFilesCommonX64Dir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_ProgramFilesCommonX64, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetProgramFilesCommonX86Dir()
/******************************************************************************************************************************/
LPSTR GetProgramFilesCommonX86Dir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAM_FILES_COMMONX86, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetProgramsDir()
/******************************************************************************************************************************/
LPSTR GetProgramsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_PROGRAMS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPublicDir()
/******************************************************************************************************************************/
LPSTR GetPublicDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Public, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPublicDesktopDir()
/******************************************************************************************************************************/
LPSTR GetPublicDesktopDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_DESKTOPDIRECTORY, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPublicDocumentsDir()
/******************************************************************************************************************************/
LPSTR GetPublicDocumentsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_DOCUMENTS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPublicDownloadsDir()
/******************************************************************************************************************************/
LPSTR GetPublicDownloadsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PublicDownloads, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPublicGameTasksDir()
/******************************************************************************************************************************/
LPSTR GetPublicGameTasksDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PublicGameTasks, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPublicLibrariesDir()
/******************************************************************************************************************************/
LPSTR GetPublicLibrariesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PublicLibraries, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPublicMusicDir()
/******************************************************************************************************************************/
LPSTR GetPublicMusicDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_MUSIC, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPublicPicturesDir()
/******************************************************************************************************************************/
LPSTR GetPublicPicturesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_PICTURES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetPublicRingtonesDir()
/******************************************************************************************************************************/
LPSTR GetPublicRingtonesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PublicRingtones, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPublicUserTilesDir()
/******************************************************************************************************************************/
LPSTR GetPublicUserTilesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_PublicUserTiles, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetPublicVideosDir()
/******************************************************************************************************************************/
LPSTR GetPublicVideosDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_COMMON_VIDEO, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetQuickLaunchDir()
/******************************************************************************************************************************/
LPSTR GetQuickLaunchDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_QuickLaunch, 0, NULL, &ppszPath)))
	wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetRecentDir()
/******************************************************************************************************************************/
LPSTR GetRecentDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_RECENT, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetRecordedTVDir()
/******************************************************************************************************************************/
LPSTR GetRecordedTVDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RecordedTV, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetRecordedTVLibraryDir()
/******************************************************************************************************************************/
LPSTR GetRecordedTVLibraryDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RecordedTVLibrary, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetRecycleBinFolderDir()
/******************************************************************************************************************************/
LPSTR GetRecycleBinFolderDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_BITBUCKET, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetResourceDir()
/******************************************************************************************************************************/
LPSTR GetResourceDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_RESOURCES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetRingtonesDir()
/******************************************************************************************************************************/
LPSTR GetRingtonesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Ringtones, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetRoamingAppDataDir()
/******************************************************************************************************************************/
LPSTR GetRoamingAppDataDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetRoamedTileImagesDir()
/******************************************************************************************************************************/
LPSTR GetRoamedTileImagesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamedTileImages, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetRoamingTilesDir()
/******************************************************************************************************************************/
LPSTR GetRoamingTilesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_RoamingTiles, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSampleMusicDir()
/******************************************************************************************************************************/
LPSTR GetSampleMusicDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SampleMusic, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSamplePicturesDir()
/******************************************************************************************************************************/
LPSTR GetSamplePicturesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SamplePictures, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSamplePlaylistsDir()
/******************************************************************************************************************************/
LPSTR GetSamplePlaylistsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SamplePlaylists, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSampleVideosDir()
/******************************************************************************************************************************/
LPSTR GetSampleVideosDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SampleVideos, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSavedGamesDir()
/******************************************************************************************************************************/
LPSTR GetSavedGamesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SavedGames, 0, NULL, &ppszPath)))
	wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSavedPicturesDir()
/******************************************************************************************************************************/
LPSTR GetSavedPicturesDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SavedPictures, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetSavedPicturesLibraryDir()
/******************************************************************************************************************************/
LPSTR GetSavedPicturesLibraryDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SavedPicturesLibrary, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetSavedSearchesDir()
/******************************************************************************************************************************/
LPSTR GetSavedSearchesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SavedSearches, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetScreenshotsDir()
/******************************************************************************************************************************/
LPSTR GetScreenshotsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_Screenshots, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSEARCH_CSCDir()
/******************************************************************************************************************************/
LPSTR GetSEARCH_CSCDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SEARCH_CSC, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSearchHistoryDir()
/******************************************************************************************************************************/
LPSTR GetSearchHistoryDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SearchHistory, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSearchHomeDir()
/******************************************************************************************************************************/
LPSTR GetSearchHomeDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SearchHome, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSEARCH_MAPIDir()
/******************************************************************************************************************************/
LPSTR GetSEARCH_MAPIDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SEARCH_MAPI, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSearchHomeDir()
/******************************************************************************************************************************/
LPSTR GetSearchTemplatesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SearchTemplates, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSendToDir()
/******************************************************************************************************************************/
LPSTR GetSendToDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_SENDTO, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetSidebarDefaultPartsDir()
/******************************************************************************************************************************/
LPSTR GetSidebarDefaultPartsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SidebarDefaultParts, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSidebarPartsDir()
/******************************************************************************************************************************/
LPSTR GetSidebarPartsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SidebarParts, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSkyDriveDir()
/******************************************************************************************************************************/
LPSTR GetSkyDriveDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SkyDrive, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSkyDriveCameraRollDir()
/******************************************************************************************************************************/
LPSTR GetSkyDriveCameraRollDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SkyDriveCameraRoll, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSkyDriveDocumentsDir()
/******************************************************************************************************************************/
LPSTR GetSkyDriveDocumentsDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SkyDriveDocuments, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSkyDrivePicturesDir()
/******************************************************************************************************************************/
LPSTR GetSkyDrivePicturesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SkyDrivePictures, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetStartMenuDir()
/******************************************************************************************************************************/
LPSTR GetStartMenuDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_STARTMENU, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetStartupDir()
/******************************************************************************************************************************/
LPSTR GetStartupDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_STARTUP, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetSyncManagerFolderDir()
/******************************************************************************************************************************/
LPSTR GetSyncManagerFolderDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SyncManagerFolder, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSyncResultsFolderDir()
/******************************************************************************************************************************/
LPSTR GetSyncResultsFolderDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SyncResultsFolder, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSyncSetupFolderDir()
/******************************************************************************************************************************/
LPSTR GetSyncSetupFolderDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_SyncSetupFolder, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetSystemDir()
/******************************************************************************************************************************/
LPSTR GetSystemDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_SYSTEM, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetSystemX86Dir()
/******************************************************************************************************************************/
LPSTR GetSystemX86Dir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_SYSTEMX86, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetTemplatesDir()
/******************************************************************************************************************************/
LPSTR GetTemplatesDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_TEMPLATES, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetTreePropertiesDir()
/******************************************************************************************************************************/
LPSTR GetTreePropertiesDir()
{
	/*LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_TreeProperties, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;*/
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetUserPinnedDir()
/******************************************************************************************************************************/
LPSTR GetUserPinnedDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_UserPinned, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetUserProfilesDir()
/******************************************************************************************************************************/
LPSTR GetUserProfilesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_UserProfiles, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetUserProgramFilesDir()
/******************************************************************************************************************************/
LPSTR GetUserProgramFilesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_UserProgramFiles, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetUserProgramFilesCommonDir()
/******************************************************************************************************************************/
LPSTR GetUserProgramFilesCommonDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_UserProgramFilesCommon, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetUsersFilesDir()
/******************************************************************************************************************************/
LPSTR GetUsersFilesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_UsersFiles, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetUsersLibrariesDir()
/******************************************************************************************************************************/
LPSTR GetUsersLibrariesDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_UsersLibraries, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetMyVideosDir()
/******************************************************************************************************************************/
LPSTR GetMyVideosDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYVIDEO, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// LPSTR GetVideosLibraryDir()
/******************************************************************************************************************************/
LPSTR GetVideosLibraryDir()
{
	LPWSTR ppszPath = NULL;
	LPSTR  szPath = new CHAR[MAX_PATH];
	*szPath = NULL;
	if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_VideosLibrary, 0, NULL, &ppszPath)))
		wcstombs(szPath, ppszPath, MAX_PATH);
	return szPath;
}
/******************************************************************************************************************************/
// LPSTR GetWindowsDir()
/******************************************************************************************************************************/
LPSTR GetWindowsDir()
{
	LPSTR szPath = new char[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_WINDOWS, NULL, NULL, szPath)))
		return szPath;
	return NULL;
}
/******************************************************************************************************************************/
// int GetDesktopWidth()
/******************************************************************************************************************************/
int GetDesktopWidth()
{
	RECT rTemp;
	GetWindowRect(GetDesktopWindow(), &rTemp);
	return (int)(rTemp.right);
}
/******************************************************************************************************************************/
// int GetDesktopHeight()
/******************************************************************************************************************************/
int GetDesktopHeight()
{
	RECT rTemp;
	GetWindowRect(GetDesktopWindow(), &rTemp);
	return (int)(rTemp.bottom);
}
/******************************************************************************************************************************/
// int GetDesktopDepth()
/******************************************************************************************************************************/
int GetDesktopDepth()
{
	return (int)GetDeviceCaps(GetDC(GetDesktopWindow()), BITSPIXEL);
}
/******************************************************************************************************************************/
// int GetDesktopRefresh()
/******************************************************************************************************************************/
int GetDesktopRefresh()
{
	return (int)GetDeviceCaps(GetDC(GetDesktopWindow()), VREFRESH);
}
/******************************************************************************************************************************/
// int GetSEC()
/******************************************************************************************************************************/
int GetSEC()
{
	time_t	long_time;
	tm	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_sec);
}
/******************************************************************************************************************************/
// int GetMIN()
/******************************************************************************************************************************/
int GetMIN()
{
	time_t	long_time;
	tm  	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_min);
}
/******************************************************************************************************************************/
// int GetHOUR()
/******************************************************************************************************************************/
int GetHOUR()
{
	time_t	long_time;
	tm	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_hour);
}
/******************************************************************************************************************************/
// int GetMDAY()
/******************************************************************************************************************************/
int GetMDAY()
{
	time_t 	long_time;
	tm	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_mday);
}
/******************************************************************************************************************************/
// int GetMON()
/******************************************************************************************************************************/
int GetMON()
{
	time_t 	long_time;
	tm	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_mon + 1);
}
/******************************************************************************************************************************/
// int GetYEAR()
/******************************************************************************************************************************/
int GetYEAR()
{
	time_t	long_time;
	tm	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_year + 1900);
}
/******************************************************************************************************************************/
// int GetWDAY()
/******************************************************************************************************************************/
int GetWDAY()
{
	time_t	long_time;
	tm	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return  int(newtime->tm_wday + 1);
}
/******************************************************************************************************************************/
// int GetYDAY()
/******************************************************************************************************************************/
int GetYDAY()
{
	time_t	long_time;
	tm  	*newtime;
	time(&long_time);
	newtime = localtime(&long_time);
	return int(newtime->tm_yday);
}

