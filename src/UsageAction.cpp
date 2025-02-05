#include "UsageAction.h"

UsageAction::UsageAction(ESDConnectionManager *esd_connection, const std::string &action, const std::string &context)
    : ESDAction(esd_connection, action, context)
{
}

void UsageAction::UpdateUsage(const uint32_t usage)
{
    SetTitle(std::to_string(usage) + "%");
}
