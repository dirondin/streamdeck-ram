#pragma once

#include "../PlatformUtils.h"

class WinPlatformUtils : public PlatformUtils
{
public:
    virtual ~WinPlatformUtils() = default;

    MemInfo GetTotalRamUsage() override;
};
