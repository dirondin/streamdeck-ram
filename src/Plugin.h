#pragma once

#include <StreamDeckSDK/ESDPlugin.h>

#include <mutex>
#include <set>

class PlatformUtils;
class ThreadTimer;
class UsageAction;

class Plugin : public ESDPlugin
{
public:
    Plugin();
    virtual ~Plugin();

    std::shared_ptr<ESDAction> GetOrCreateAction(const std::string &action, const std::string &context) override;

private:
    void UpdateTimer();

    std::mutex ActionsMutex;
    std::map<std::string, std::shared_ptr<UsageAction>> Actions;

    std::unique_ptr<PlatformUtils> PlatformUtils;
    std::unique_ptr<ThreadTimer> Timer;
};
