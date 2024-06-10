#pragma once

#include <vector>
#include <string>
#include "Data/CWeek.hpp"
#include "libs/nlohmann/json.hpp"

using tGamesPerWeekMap = std::unordered_map<std::string, std::vector<std::string>>;
using tWeekVec = std::unordered_map<std::string, CWeek>;
using tGameVec = std::vector<CGame>;

class CApiDataCompiler
{
public:
    tWeekVec compileApiData();
private:
    CGame saveApiGameData(nlohmann::json& json_stream);
    CWeek saveApiWeekData(const std::string& weekName, tGameVec& games);

    tWeekVec m_allData{};
};
