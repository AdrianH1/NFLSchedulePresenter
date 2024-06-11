#pragma once

#include <string>

class CSiteContentUpdater
{
public:
    void updateWatchOption(const std::string& gameId, const std::string& line, const std::string& newWatchOption);
    void updateSeen(const std::string& gameId);
};