#include "CApiDataReader.hpp"
#include "CHttpClient.hpp"
#include "libs/nlohmann/json.hpp"
#include "InternalDb.hpp"
#include <fstream>
#include <iostream>

//------------------------------------------------------------------
void CApiDataReader::getAllRegularSeasonEvents()
{
    CHttpClient httpClient(KeyValues::getApiServerIp(), 80);

    for (auto i = 1; i <= 18; ++i)
    {
        auto weekNum = std::to_string(i);
        httpClient.addRequest(ApiUrl::getWeekOverview(weekNum), JsonFilePath::getWeekOverview(weekNum));
    }

    httpClient.start();
}

//------------------------------------------------------------------
void CApiDataReader::extractEventsFromWeeks(int weekNum)
{
    std::ifstream ifs(JsonFilePath::getWeekOverview(std::to_string(weekNum)));
    auto json_stream = nlohmann::json::parse(ifs);

    std::cout << json_stream.at("$meta") << std::endl;

    std::vector<std::string> eventsPerWeek{};
    auto data = json_stream.at("items");
    for (auto it = data.begin(); it != data.end(); ++it)
    {
        eventsPerWeek.emplace_back(it.value().at("$ref"));
    }

    m_mapEventsPerWeek.try_emplace(KeyValues::getWeekOverview(std::to_string(weekNum)), eventsPerWeek);
}

//------------------------------------------------------------------
void CApiDataReader::getRegularSeasonEventDetails()
{
    CHttpClient httpClient(KeyValues::getApiServerIp(), 80);

    for (const auto& [key, value] : m_mapEventsPerWeek)
    {
        int num = 1;
        for (const auto& url : value)
        {
            std::cout << JsonFilePath::getWeekDetail(key, num) << std::endl;
            std::cout << url << std::endl;
            httpClient.addRequest(url, JsonFilePath::getWeekDetail(key, num));
            ++num;
        }
    }

    httpClient.start();
}
