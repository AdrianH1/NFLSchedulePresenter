#include <iostream>
#include <memory>
#include "CApiDataReader.hpp"
#include <fstream>
#include "libs/nlohmann/json.hpp"

int main(int argc, char const* argv[]) {
    std::cout << "start\n";

    auto apiReader = std::make_unique<CApiDataReader>();
    // apiReader->getAllRegularSeasonEvents();

    apiReader->extractEventsFromWeeks(13);
    apiReader->getRegularSeasonEventDetails();


    // Load the file and extract the JSON content
    // std::ifstream ifs("..\\apiData\\week17\\eventDetails_3.json");
    // std::stringstream buffer;
    // buffer << ifs.rdbuf();
    // std::string fileContent = buffer.str();

    // std::cout << fileContent << std::endl;
    // std::cout << "-----------------------------" << std::endl;

    // std::size_t start = fileContent.find('{');
    // std::size_t end = fileContent.rfind('}');
    // std::cout << start << std::endl;
    // std::cout << end << std::endl;
    // std::string jsonString = fileContent.substr(start, end + 1);
    // std::cout << jsonString << std::endl;

    // CHttpClient gameReader("54.71.61.211", 80);
    // gameReader.start();

    // gameReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/18/events", "week18_events.json");


    std::cout << "\nend";
    return 0;
}
