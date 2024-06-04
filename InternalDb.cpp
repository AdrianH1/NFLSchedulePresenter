#include <string>

struct ApiUrl
{
public:
    static const std::string getWeekOverview(const std::string& week)
    {
        return "/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/" + week + "/events";
    }
};

struct JsonFilePath
{
public:
    static const std::string getWeekOverview(const std::string& week)
    {
        return "..\\apiData\\week" + week + "_events.json";
    }

    static const std::string getWeekDetail(const std::string& week, int num)
    {
        return "..\\apiData\\" + week + "\\eventDetails_" + std::to_string(num) + ".json";
    }
};

struct KeyValues
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