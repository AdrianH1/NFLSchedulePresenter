#pragma once

#include <string>
#include <vector>
#include "CGame.hpp"

struct CWeek
{
    std::string         m_name;
    std::vector<CGame>  m_gamesPerWeek{};
};