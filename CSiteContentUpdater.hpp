#pragma once

#include <string>

class CSiteContentUpdater
{
public:
    std::string searchLine(const std::string & gameId, const std::string& newWatchOption, const std::string& newSeenOption);
private:
    std::string updateWatchOption(const std::string& gameId, const std::string& line, const std::string& newWatchOption);
    std::string updateSeen(const std::string& gameId, const std::string& line, const std::string& newSeenOption);
};