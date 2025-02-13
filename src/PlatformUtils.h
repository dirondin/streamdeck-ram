#pragma once

#include <cstdint>

struct MemInfo
{
    uint64_t total;
    uint64_t used;
};

class PlatformUtils
{
public:
    virtual ~PlatformUtils() = default;

    virtual MemInfo GetTotalRamUsage() = 0;
};
