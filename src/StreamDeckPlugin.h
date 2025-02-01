#include <StreamDeckSDK/ESDBasePlugin.h>

#include <mutex>
#include <set>

using json = nlohmann::json;

class PlatformUtils;
class ThreadTimer;

class StreamDeckPlugin : public ESDBasePlugin
{
public:
    StreamDeckPlugin();
    virtual ~StreamDeckPlugin();

    void KeyDownForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID) override;
    void KeyUpForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID) override;

    void WillAppearForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID) override;
    void WillDisappearForAction(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID) override;

    void DeviceDidConnect(const std::string &inDeviceID, const json &inDeviceInfo) override;
    void DeviceDidDisconnect(const std::string &inDeviceID) override;

    void SendToPlugin(const std::string &inAction, const std::string &inContext, const json &inPayload, const std::string &inDeviceID) override;

private:
    void UpdateTimer();

    std::mutex VisibleContextsMutex;
    std::set<std::string> VisibleContexts;

    std::unique_ptr<PlatformUtils> PlatformUtils;
    std::unique_ptr<ThreadTimer> Timer;
};
