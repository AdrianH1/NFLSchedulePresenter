#include <iostream>
#include <filesystem>
#include <unordered_map>
#include "CApiDataCompiler.hpp"
#include "InternalDb.hpp"

using tGamesPerWeekMap = std::unordered_map<std::string, std::vector<std::string>>;

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
std::vector<CWeek> CApiDataCompiler::compileApiData()
{
    readJsonFiles();
    return std::vector<CWeek>();
}

//------------------------------------------------------------------
void CApiDataCompiler::readJsonFiles()
{
    auto fileMap = collectFiles();
    std::cout << "break";
}

//------------------------------------------------------------------
void CApiDataCompiler::saveApiData()
{
}
