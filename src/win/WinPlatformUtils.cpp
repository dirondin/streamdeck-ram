#include "WinPlatformUtils.h"

#include <windows.h>

MemInfo WinPlatformUtils::GetTotalRamUsage()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    return {statex.ullTotalPhys, statex.ullTotalPhys - statex.ullAvailPhys};
}