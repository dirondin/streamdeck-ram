#include "WinPlatformUtils.h"

#include <windows.h>

uint32_t WinPlatformUtils::GetTotalRamUsage()
{
    MEMORYSTATUSEX statex;
    statex.dwLength = sizeof(statex);

    GlobalMemoryStatusEx(&statex);

    return static_cast<uint32_t>(statex.dwMemoryLoad);
}