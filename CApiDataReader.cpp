#include "CApiDataReader.hpp"
#include "CHttpClient.hpp"
#include "InternalDB.cpp"
#include "libs/nlohmann/json.hpp"
#include <fstream>
#include <iostream>

//------------------------------------------------------------------
void CApiDataReader::getAllRegularSeasonEvents()
{
    CHttpClient httpClient(KeyValues::getApiServerIp(), 80);

    httpClient.addRequest(ApiUrl::getWeekOverview("1"), JsonFilePath::getWeekOverview("1"));
    httpClient.addRequest(ApiUrl::getWeekOverview("2"), JsonFilePath::getWeekOverview("2"));
    httpClient.addRequest(ApiUrl::getWeekOverview("3"), JsonFilePath::getWeekOverview("3"));
    httpClient.addRequest(ApiUrl::getWeekOverview("4"), JsonFilePath::getWeekOverview("4"));
    httpClient.addRequest(ApiUrl::getWeekOverview("5"), JsonFilePath::getWeekOverview("5"));
    httpClient.addRequest(ApiUrl::getWeekOverview("6"), JsonFilePath::getWeekOverview("6"));
    httpClient.addRequest(ApiUrl::getWeekOverview("7"), JsonFilePath::getWeekOverview("7"));
    httpClient.addRequest(ApiUrl::getWeekOverview("8"), JsonFilePath::getWeekOverview("8"));
    httpClient.addRequest(ApiUrl::getWeekOverview("9"), JsonFilePath::getWeekOverview("9"));
    httpClient.addRequest(ApiUrl::getWeekOverview("10"), JsonFilePath::getWeekOverview("10"));
    httpClient.addRequest(ApiUrl::getWeekOverview("11"), JsonFilePath::getWeekOverview("11"));
    httpClient.addRequest(ApiUrl::getWeekOverview("12"), JsonFilePath::getWeekOverview("12"));
    httpClient.addRequest(ApiUrl::getWeekOverview("13"), JsonFilePath::getWeekOverview("13"));
    httpClient.addRequest(ApiUrl::getWeekOverview("14"), JsonFilePath::getWeekOverview("14"));
    httpClient.addRequest(ApiUrl::getWeekOverview("15"), JsonFilePath::getWeekOverview("15"));
    httpClient.addRequest(ApiUrl::getWeekOverview("16"), JsonFilePath::getWeekOverview("16"));
    httpClient.addRequest(ApiUrl::getWeekOverview("17"), JsonFilePath::getWeekOverview("17"));
    httpClient.addRequest(ApiUrl::getWeekOverview("18"), JsonFilePath::getWeekOverview("18"));

    httpClient.start();
}

//------------------------------------------------------------------
void CApiDataReader::extractEventsFromWeeks()
{
    for (int i = 1; i <= 1; i++)
    {
        std::ifstream ifs(JsonFilePath::getWeekOverview(std::to_string(i)));
        auto json_stream = nlohmann::json::parse(ifs);

        std::cout << json_stream.at("$meta") << std::endl;

        std::vector<std::string> eventsPerWeek{};
        auto data = json_stream.at("items");
        for (auto it = data.begin(); it != data.end(); ++it)
        {
            eventsPerWeek.emplace_back(it.value().at("$ref"));
        }

        m_mapEventsPerWeek.try_emplace(KeyValues::getWeekOverview(std::to_string(i)), eventsPerWeek);
    }
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
