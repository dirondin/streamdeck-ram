#include "StreamDeckPlugin.h"
#include "PlatformUtils.h"
#include "ThreadTimer.h"

#ifdef __APPLE__
#include "mac/MacPlatformUtils.h"
#elif _WIN32
#include "win/WinPlatformUtils.h"
#endif

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4267)
#endif

#include <StreamDeckSDK/ESDConnectionManager.h>

#ifdef __clang__
#pragma clang diagnostic pop
#elif _MSC_VER
#pragma warning(pop)
#endif

#include <atomic>

StreamDeckPlugin::StreamDeckPlugin()
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

StreamDeckPlugin::~StreamDeckPlugin()
{
}

void StreamDeckPlugin::UpdateTimer()
{
    if (mConnectionManager != nullptr)
    {
        VisibleContextsMutex.lock();
        int currentValue = PlatformUtils->GetTotalRamUsage();
        for (const std::string &context : VisibleContexts)
        {
            mConnectionManager->SetTitle(std::to_string(currentValue) + "%", context, kESDSDKTarget_HardwareAndSoftware);
        }
        VisibleContextsMutex.unlock();
    }
}

void StreamDeckPlugin::KeyDownForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID)
{
}

void StreamDeckPlugin::KeyUpForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID)
{
}

void StreamDeckPlugin::WillAppearForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID)
{
    VisibleContextsMutex.lock();
    VisibleContexts.insert(inContext);
    VisibleContextsMutex.unlock();
}

void StreamDeckPlugin::WillDisappearForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID)
{
    VisibleContextsMutex.lock();
    VisibleContexts.erase(inContext);
    VisibleContextsMutex.unlock();
}

void StreamDeckPlugin::DeviceDidConnect(const std::string &inDeviceID, const json &inDeviceInfo)
{
}

void StreamDeckPlugin::DeviceDidDisconnect(const std::string &inDeviceID)
{
}

void StreamDeckPlugin::SendToPlugin(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID)
{
}
