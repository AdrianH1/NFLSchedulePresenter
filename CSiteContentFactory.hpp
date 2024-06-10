#pragma once

#include "Data/CGame.hpp"
#include "Data/CWeek.hpp"
#include <string>
#include <vector>
#include <unordered_map>

class CSiteContentFactory
{
public:
    std::string createGameList(const CGame& game);
    std::vector<std::string> createWeekList(CWeek& week);
    void saveSiteContent(std::unordered_map<std::string, CWeek>& data);
};