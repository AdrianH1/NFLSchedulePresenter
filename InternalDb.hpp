#pragma once

#include <string>
#include <filesystem>

namespace ApiUrl
{
static const std::string getWeekOverview(const std::string& week)
{
    return "/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/" + week + "/events";
}
};

namespace JsonFilePath
{
static const std::string getWeekOverview(const std::string& week)
{
    return "..\\apiData\\week" + week + "_events.json";
}

static const std::string getWeekDetail(const std::string& week, int num)
{
    return "..\\apiData\\" + week + "\\eventDetails_" + std::to_string(num) + ".json";
}

static const std::string getFolderPath(int num)
{
    return "..\\apiData\\week" + std::to_string(num);
}

static const std::size_t getNumOfFilesInDirecttory(std::filesystem::path path)
{
    using std::filesystem::directory_iterator;
    return std::distance(directory_iterator(path), directory_iterator{});
}
};

namespace KeyValues
{
static const std::string getWeekOverview(const std::string& week)
{
    return "week" + week;
}

static const std::string getApiServerIp()
{
    return "54.71.61.211";
}
};

enum class WatchOption
{
    FULL,
    FORTY,
    HIGHLIGHTS,
    PAYTONELI,
    REDZONE,
    NOTSET
};