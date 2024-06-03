#include <iostream>
#include <memory>
#include "CApiDataReader.hpp"

int main(int argc, char const* argv[]) {
    std::cout << "start\n";

    auto apiReader = std::make_unique<CApiDataReader>();
    // apiReader->getAllRegularSeasonEvents();
    apiReader->extractEventsFromWeeks();
    apiReader->getRegularSeasonEventDetails();

    // CHttpClient gameReader("54.71.61.211", 80);
    // gameReader.start();

    // gameReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/18/events", "week18_events.json");


    std::cout << "\nend";
    return 0;
}
