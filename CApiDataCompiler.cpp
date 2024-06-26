#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <unordered_map>
#include "CApiDataCompiler.hpp"
#include "InternalDb.hpp"
#include "Data/CGame.hpp"
#include "Data/CWeek.hpp"

//------------------------------------------------------------------
namespace
{
tGamesPerWeekMap collectFiles()
{
    tGamesPerWeekMap result{};

    for (int i = 1; i <= 18; i++)
    {
        std::vector<std::string> weeklyGames{};
        std::string week = "week" + std::to_string(i);
        for (int j = 1; j <= JsonFilePath::getNumOfFilesInDirecttory(JsonFilePath::getFolderPath(i)); j++)
        {
            weeklyGames.emplace_back(JsonFilePath::getWeekDetail(week, j));
        }
        result.try_emplace(week, weeklyGames);
    }

    return result;
}
}
//------------------------------------------------------------------
tWeekVec CApiDataCompiler::compileApiData()
{
    using json = nlohmann::json;

    auto fileMap = collectFiles();

    //key = weekX || value = json file path
    for (const auto& [key, value] : fileMap)
    {
        tGameVec games{};
        for (const auto& path : value)
        {
            try
            {
                std::ifstream ifs(path);
                json json_stream = json::parse(ifs);
                games.emplace_back(saveApiGameData(json_stream));
            }
            catch (const json::exception& e)
            {
                std::cerr << "Exception when parsing file:" << path << std::endl;
                std::cerr << e.what() << '\n';
            }
        }
        m_allData.try_emplace(key, saveApiWeekData(key, games));
        games.clear();
    }
    return m_allData;
}

//------------------------------------------------------------------
CWeek CApiDataCompiler::saveApiWeekData(const std::string& weekName, tGameVec& games)
{
    CWeek week;
    week.m_name = weekName;
    week.m_gamesPerWeek = games;
    return week;
}

namespace
{
void separateDate(std::string& fullDate, CGame& game)
{
    auto date = fullDate.substr(0, 10);
    auto time = fullDate.substr(11, 16);

    std::tm tm{};
    std::istringstream ss(date + time);
    ss >> std::get_time(&tm, "%Y-%m-%d %H:%M");

    std::ostringstream timeStream;
    timeStream << std::put_time(&tm, "%H:%M");
    time = timeStream.str();

    std::ostringstream dateStream;
    dateStream << std::put_time(&tm, "%d.%m.%Y");
    date = dateStream.str();

    // Extract the day of the week
    char dayBuffer[10];
    std::strftime(dayBuffer, sizeof(dayBuffer), "%A", &tm);
    std::string dayOfWeek(dayBuffer);

    game.m_date = date;
    game.m_time = time;
    game.m_day = dayOfWeek;
}
}

//------------------------------------------------------------------
CGame CApiDataCompiler::saveApiGameData(nlohmann::json& json_stream)
{
    CGame game;
    game.m_gameId = json_stream.at("id");
    std::string date = json_stream.at("date");
    separateDate(date, game);

    std::string teams = json_stream.at("name");
    std::string delimiter = " at ";

    size_t pos = teams.find(delimiter);

    if (pos != std::string::npos) {
        game.m_guestTeam = teams.substr(0, pos);
        game.m_homeTeam = teams.substr(pos + delimiter.length());
    }
    else {
        std::cerr << "Delimiter not found!" << std::endl;
    }

    return game;
}
