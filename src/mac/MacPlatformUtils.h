#pragma once

#include "PlatformUtils.h"

class MacPlatformUtils : public PlatformUtils
{
public:
    virtual ~MacPlatformUtils() = default;

    MemInfo GetTotalRamUsage() override;
};
