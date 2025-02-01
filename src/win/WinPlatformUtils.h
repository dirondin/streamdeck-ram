#pragma once

#include "PlatformUtils.h"

class WinPlatformUtils : public PlatformUtils
{
public:
    virtual ~WinPlatformUtils() = default;

    uint32_t GetTotalRamUsage() override;
};
