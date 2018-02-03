#include "file.h"

/******************************************************************************************************************************/
// bool FileCopy(LPCSTR source, LPCSTR dest, DWORD flag)
/******************************************************************************************************************************/
bool FileCopy(LPCSTR source, LPCSTR dest, DWORD flag)
{
	HANDLE hFile;
	HANDLE hAppend;
	DWORD  dwBytesRead, dwBytesWritten, dwPos;
	BYTE   buff[4096];
	hFile = CreateFile(source,        // open One.txt
		GENERIC_READ,             // open for reading
		0,                        // do not share
		NULL,                     // no security
		OPEN_EXISTING,            // existing file only
		FILE_ATTRIBUTE_NORMAL,    // normal file
		NULL);                    // no attr. template
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;
	hAppend = CreateFile(dest,        // open Two.txt
		GENERIC_WRITE,            // open for writing
		FILE_SHARE_READ,          // allow multiple readers
		NULL,                     // no security
		(flag>0)?flag:CREATE_NEW, // open or create
		FILE_ATTRIBUTE_NORMAL,    // normal file
		NULL);                    // no attr. template
	if (hAppend == INVALID_HANDLE_VALUE)
		return FALSE;
	while (ReadFile(hFile, buff, sizeof(buff), &dwBytesRead, NULL) && dwBytesRead > 0)
	{
		dwPos = SetFilePointer(hAppend, 0, NULL, FILE_END);
		LockFile(hAppend, dwPos, 0, dwBytesRead, 0);
		WriteFile(hAppend, buff, dwBytesRead, &dwBytesWritten, NULL);
		UnlockFile(hAppend, dwPos, 0, dwBytesRead, 0);
	}
	CloseHandle(hFile);
	CloseHandle(hAppend);
	return TRUE;
}
