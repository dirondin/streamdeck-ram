#pragma once

#include <StreamDeckSDK/ESDAction.h>

class UsageAction : public ESDAction
{
public:
    UsageAction(ESDConnectionManager *esd_connection, const std::string &action, const std::string &context);

    void UpdateUsage(const uint32_t usage);
};
