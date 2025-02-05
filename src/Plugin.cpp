#include "Plugin.h"
#include "PlatformUtils.h"
#include "ThreadTimer.h"
#include "UsageAction.h"

#ifdef __APPLE__
#include "mac/MacPlatformUtils.h"
#elif _WIN32
#include "win/WinPlatformUtils.h"
#endif

#include <atomic>

Plugin::Plugin()
{
#ifdef __APPLE__
    PlatformUtils = std::make_unique<MacPlatformUtils>();
#elif _WIN32
    PlatformUtils = std::make_unique<WinPlatformUtils>();
#endif

    Timer = std::make_unique<ThreadTimer>();
    Timer->Start(1000, [this]()
                 { this->UpdateTimer(); });
}

Plugin::~Plugin() = default;

std::shared_ptr<ESDAction> Plugin::GetOrCreateAction(const std::string &action, const std::string &context)
{
    std::scoped_lock lock(ActionsMutex);

    auto it = Actions.find(context);
    if (it != Actions.end())
    {
        return it->second;
    }

    if (action == "eu.dirondin.streamdeck.ram.usage")
    {
        auto act = std::make_shared<UsageAction>(mConnectionManager, action, context);
        Actions[context] = act;
        return act;
    }

    return nullptr;
}

void Plugin::UpdateTimer()
{
    std::scoped_lock lock(ActionsMutex);

    int currentValue = PlatformUtils->GetTotalRamUsage();
    for (const auto &[_, action] : Actions)
    {
        action->UpdateUsage(currentValue);
    }
}
