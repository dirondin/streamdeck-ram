#include "UsageAction.h"
#include "PlatformUtils.h"

#include <sstream>
#include <iomanip>

UsageAction::UsageAction(ESDConnectionManager *esd_connection, const std::string &action, const std::string &context)
    : ESDActionWithExternalState(esd_connection, action, context)
{
}

void UsageAction::UpdateUsage(const MemInfo &info)
{
    if (skinUpdateCount > 0)
    {
        skinUpdateCount--;
        return;
    }

    switch (GetSettings().viewType)
    {
    case ViewType::Usage:
        SetTitle(std::to_string((info.used * 100) / info.total) + "%");
        break;
    case ViewType::FreeSpace:
        SetTitle("Free\n" + sizeToString(info.total - info.used));
        break;
    case ViewType::UsedSpace:
        SetTitle("Used\n" + sizeToString(info.used));
        break;
    }
}

void UsageAction::WillAppear()
{
}

void UsageAction::KeyDown()
{
    UsageActionSettings newSettings = GetSettings();
    int32_t newState = 0;
    std::string newTitle = "";
    switch (newSettings.viewType)
    {
    case ViewType::Usage:
        newSettings.viewType = ViewType::FreeSpace;
        newState = 1;
        newTitle = "Free";
        break;
    case ViewType::FreeSpace:
        newSettings.viewType = ViewType::UsedSpace;
        newState = 1;
        newTitle = "Used";
        break;
    case ViewType::UsedSpace:
        newSettings.viewType = ViewType::Usage;
        newState = 0;
        newTitle = "%";
        break;
    }
    SetSettings(std::move(newSettings));
    SetState(newState);
    SetTitle(newTitle);
    skinUpdateCount += 2;
}

void UsageAction::SettingsDidChange(const UsageActionSettings &oldSettings, const UsageActionSettings &newSettings)
{
}

std::string UsageAction::sizeToString(uint64_t size)
{
    const char *sizes[] = {"B", "KB", "MB", "GB", "TB"};
    int div = 0;
    uint64_t rem = 0;

    while (size >= 1024 && div < (sizeof sizes / sizeof *sizes - 1))
    {
        rem = (size % 1024);
        div++;
        size /= 1024;
    }

    float sizeValue = (float)size + (float)rem / 1024.f;
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(2) << sizeValue << "\n" << sizes[div];
    return oss.str();
}

void from_json(const nlohmann::json &json, UsageActionSettings &settings)
{
    if (json.contains("view_type"))
    {
        settings.viewType = json.at("view_type");
    }
}

void to_json(nlohmann::json &json, UsageActionSettings &&settings)
{
    json["view_type"] = settings.viewType;
}

bool UsageActionSettings::operator==(const UsageActionSettings &rhs) const
{
    return viewType == rhs.viewType;
}
