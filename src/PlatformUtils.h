#pragma once

#include <cstdint>

class PlatformUtils
{
public:
    virtual ~PlatformUtils() = default;

    virtual uint32_t GetTotalRamUsage() = 0;
};
