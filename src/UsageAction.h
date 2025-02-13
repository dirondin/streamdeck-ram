#pragma once

#include <StreamDeckSDK/ESDActionWithExternalState.h>

struct MemInfo;

enum class ViewType
{
    Usage,
    FreeSpace,
    UsedSpace,
};

NLOHMANN_JSON_SERIALIZE_ENUM(
    ViewType,
    {
        {ViewType::Usage, "usage"},
        {ViewType::FreeSpace, "free_space"},
        {ViewType::UsedSpace, "used_space"},
    })

struct UsageActionSettings
{
    ViewType viewType = ViewType::Usage;

    bool operator==(const UsageActionSettings &rhs) const;
};
void from_json(const nlohmann::json &json, UsageActionSettings &settings);
void to_json(nlohmann::json &json, UsageActionSettings &&settings);

class UsageAction : public ESDActionWithExternalState<UsageActionSettings>
{
public:
    UsageAction(ESDConnectionManager *esd_connection, const std::string &action, const std::string &context);

    void UpdateUsage(const MemInfo& info);

    void WillAppear() override;
    void KeyDown() override;
    void SettingsDidChange(const UsageActionSettings& oldSettings, const UsageActionSettings& newSettings) override;

private:
    std::string sizeToString(uint64_t size);

    uint32_t skinUpdateCount = 0;
};
