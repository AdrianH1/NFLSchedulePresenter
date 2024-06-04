#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class CApiDataReader
{
public:
    void getAllRegularSeasonEvents();
    void extractEventsFromWeeks(int weekNum);
    void getRegularSeasonEventDetails();

private:
    std::unordered_map<std::string, std::vector<std::string>> m_mapEventsPerWeek{};
};