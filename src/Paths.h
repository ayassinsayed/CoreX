#pragma once
#include <Windows.h>
#include <string>
using namespace std;
/******************************************************************************************************************************/
#define _WIN32_WINNT_NT4            0x0400
#define _WIN32_WINNT_WIN2K          0x0500
#define _WIN32_WINNT_WINXP          0x0501
#define _WIN32_WINNT_WS03           0x0502
#define _WIN32_WINNT_WIN6           0x0600
#define _WIN32_WINNT_VISTA          0x0600
#define _WIN32_WINNT_WS08           0x0600
#define _WIN32_WINNT_LONGHORN       0x0600
#define _WIN32_WINNT_WIN7           0x0601
#define _WIN32_WINNT_WIN8           0x0602
#define _WIN32_WINNT_WINBLUE        0x0603
#define _WIN32_WINNT_WIN10			0x0A00 
/******************************************************************************************************************************/
LPSTR GetOSArch();
/******************************************************************************************************************************/
LPSTR GetOsVersion();
LPSTR GetOSServicePack();
LPSTR GetOsProductInfo();
DWORD GetOSBuild();
/******************************************************************************************************************************/
DWORD GetModuleSize(LPCSTR ModuleName = NULL);
LPSTR GetModuleFullPath();
LPSTR GetModuleName();
LPSTR GetModuleDrive();
LPSTR GetModuleDir();
/******************************************************************************************************************************/
LPSTR GetWorkingDir();
LPSTR GetTempDir();
LPSTR GetHomeDrive();
LPSTR GetHomePath();
LPSTR GetHomeShare();
LPSTR _GetUserName();
LPSTR _GetComputerName();
LPSTR GetLogonServer();
LPSTR GetLogonDNSDomain();
LPSTR GetLogonDomain();
LPSTR GetComSpec();
/******************************************************************************************************************************/
LPSTR GetAccountPicturesDir();
LPSTR GetAddNewProgramsDir();
LPSTR GetAdminToolsDir();
LPSTR GetAppDataDesktopDir();
LPSTR GetAppDataDocumentsDir();
LPSTR GetAppDataFavoritesDir();
LPSTR GetAppDataProgramDataDir();
LPSTR GetApplicationShortcutsDir();
LPSTR GetAppsFolderDir();
LPSTR GetAppUpdatesDir();
LPSTR GetCameraRollDir();
LPSTR GetGetGetCDBurningDir();
LPSTR GetChangeRemoveProgramsDir();
LPSTR GetCommonAdminToolsDir();
LPSTR GetCommonOEMLinksDir();
LPSTR GetCommonProgramsDir();
LPSTR GetCommonStartMenuDir();
LPSTR GetCommonStartupDir();
LPSTR GetCommonTemplatesDir();
LPSTR GetComputerFolderDir();
LPSTR GetConflictFolderDir();
LPSTR GetConnectionsFolderDir();
LPSTR GetContactsDir();
LPSTR GetControlPanelFolderDir();
LPSTR GetCookiesDir();
LPSTR GetDesktopDir();
LPSTR GetDeviceMetadataStoreDir();
LPSTR GetMyDocumentsDir();
LPSTR GetDocumentsLibraryDir();
LPSTR GetDownloadsDir();
LPSTR GetFavoritesDir();
LPSTR GetFontsDir();
LPSTR GetGamesDir();
LPSTR GetGameTasksDir();
LPSTR GetHistoryDir();
LPSTR GetHomeGroupDir();
LPSTR GetHomeGroupCurrentUserDir();
LPSTR GetImplicitAppShortcutsDir();
LPSTR GetInternetCacheDir();
LPSTR GetInternetFolderDir();
LPSTR GetLibrariesDir();
LPSTR GetLinksDir();
LPSTR GetLocalAppDataDir();
LPSTR GetLocalAppDataLowDir();
LPSTR GetLocalizedResourcesDir();
LPSTR GetMyMusicDir();
LPSTR GetMusicLibraryDir();
LPSTR GetNetHoodDir();
LPSTR GetNetworkFolderDir();
LPSTR GetObjects3DDir();
LPSTR GetOriginalImagesDir();
LPSTR GetPhotoAlbumsDir();
LPSTR GetPicturesLibraryDir();
LPSTR GetMyPicturesDir();
LPSTR GetPlaylistsDir();
LPSTR GetPrintersFolderDir();
LPSTR GetPrintHoodDir();
LPSTR GetUserProfileDir();
LPSTR GetProgramDataDir();
LPSTR GetProgramFilesDir();
LPSTR GetProgramFilesX64Dir();
LPSTR GetProgramFilesX86Dir();
LPSTR GetProgramFilesCommonDir();
LPSTR GetProgramFilesCommonX64Dir();
LPSTR GetProgramFilesCommonX86Dir();
LPSTR GetProgramsDir();
LPSTR GetPublicDir();
LPSTR GetPublicDesktopDir();
LPSTR GetPublicDocumentsDir();
LPSTR GetPublicDownloadsDir();
LPSTR GetPublicGameTasksDir();
LPSTR GetPublicLibrariesDir();
LPSTR GetPublicMusicDir();
LPSTR GetPublicPicturesDir();
LPSTR GetPublicRingtonesDir();
LPSTR GetPublicUserTilesDir();
LPSTR GetPublicVideosDir();
LPSTR GetQuickLaunchDir();
LPSTR GetRecentDir();
LPSTR GetRecordedTVDir();
LPSTR GetRecordedTVLibraryDir();
LPSTR GetRecycleBinFolderDir();
LPSTR GetResourceDir();
LPSTR GetRingtonesDir();
LPSTR GetRoamingAppDataDir();
LPSTR GetRoamedTileImagesDir();
LPSTR GetRoamingTilesDir();
LPSTR GetSampleMusicDir();
LPSTR GetSamplePicturesDir();
LPSTR GetSamplePlaylistsDir();
LPSTR GetSampleVideosDir();
LPSTR GetSavedGamesDir();
LPSTR GetSavedPicturesDir();
LPSTR GetSavedPicturesLibraryDir();
LPSTR GetSavedSearchesDir();
LPSTR GetScreenshotsDir();
LPSTR GetSEARCH_CSCDir();
LPSTR GetSearchHistoryDir();
LPSTR GetSearchHomeDir();
LPSTR GetSEARCH_MAPIDir();
LPSTR GetSearchTemplatesDir();
LPSTR GetSendToDir();
LPSTR GetSidebarDefaultPartsDir();
LPSTR GetSidebarPartsDir();
LPSTR GetSkyDriveDir();
LPSTR GetSkyDriveCameraRollDir();
LPSTR GetSkyDriveDocumentsDir();
LPSTR GetSkyDrivePicturesDir();
LPSTR GetStartMenuDir();
LPSTR GetStartupDir();
LPSTR GetSyncManagerFolderDir();
LPSTR GetSyncResultsFolderDir();
LPSTR GetSyncSetupFolderDir();
LPSTR GetSystemDir();
LPSTR GetSystemX86Dir();
LPSTR GetTemplatesDir();
LPSTR GetTreePropertiesDir();
LPSTR GetUserPinnedDir();
LPSTR GetUserProfilesDir();
LPSTR GetUserProgramFilesDir();
LPSTR GetUserProgramFilesCommonDir();
LPSTR GetUsersFilesDir();
LPSTR GetUsersLibrariesDir();
LPSTR GetMyVideosDir();
LPSTR GetVideosLibraryDir();
LPSTR GetWindowsDir();
/******************************************************************************************************************************/
int GetDesktopWidth();
int GetDesktopHeight();
int GetDesktopDepth();
int GetDesktopRefresh();
int GetSEC();
int GetMIN();
int GetHOUR();
int GetMDAY();
int GetMON();
int GetYEAR();
int GetWDAY();
int GetYDAY();
/******************************************************************************************************************************/