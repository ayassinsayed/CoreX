#include <Windows.h>

BOOL ServiceInstall(LPCTSTR ServiceName, LPCTSTR BinaryPathName, DWORD dwServiceType = SERVICE_KERNEL_DRIVER, DWORD dwStartType= SERVICE_DEMAND_START);
BOOL ServiceRemove(LPCTSTR ServiceName);
BOOL ServiceStart(LPCTSTR ServiceName);
BOOL ServiceStop(LPCTSTR ServiceName);
BOOL ServiceExists(LPCTSTR ServiceName);
BOOL ServiceRunning(LPCTSTR ServiceName);
BOOL OpenDevice(LPCTSTR ServiceName);