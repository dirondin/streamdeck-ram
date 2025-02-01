#pragma once

#include "PlatformUtils.h"

class MacPlatformUtils : public PlatformUtils
{
public:
    virtual ~MacPlatformUtils() = default;

    uint32_t GetTotalRamUsage() override;
};
