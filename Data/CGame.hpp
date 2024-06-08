#pragma once

#include "../InternalDb.hpp"
#include <string>

struct CGame
{
    std::string     m_gameId{};
    std::string     m_homeTeam{};
    std::string     m_guestTeam{};
    std::string     m_date{};
    std::string     m_time{};
    std::string     m_day{};
    WatchOption     m_watchOption{ WatchOption::NOTSET };
    bool            m_seen{ false };
};
