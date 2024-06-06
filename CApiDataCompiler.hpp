#pragma once

#include <vector>
#include <string>
#include "Data/CWeek.hpp"
#include "libs/nlohmann/json.hpp"

using tGamesPerWeekMap = std::unordered_map<std::string, std::vector<std::string>>;
using tWeekVec = std::vector<CWeek>;
using tGameVec = std::vector<CGame>;

class CApiDataCompiler
{
public:
    void compileApiData();
private:
    CGame saveApiGameData(nlohmann::json& json_stream);
    CWeek saveApiWeekData(const std::string& weekName, tGameVec& games);

    tWeekVec m_allData{};
};
