#pragma once

#include <string>
#include <unordered_map>
#include <vector>

class CApiDataReader
{
public:
    void getAllRegularSeasonEvents();
    void extractEventsFromWeeks();
    void getRegularSeasonEventDetails();

private:
    std::unordered_map<std::string, std::vector<std::string>> m_eventsPerWeek{};
};