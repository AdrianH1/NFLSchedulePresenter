#pragma once

#include "Data/CGame.hpp"
#include "Data/CWeek.hpp"
#include <string>
#include <vector>

class CSiteContentFactory
{
public:
    std::string createGameList(CGame& game);
    std::vector<std::string> createWeekList(CWeek& week);
};