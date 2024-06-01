#include <iostream>
#include "CApiReader.hpp"

int main(int argc, char const* argv[]) {
    std::cout << "start\n";

    CApiReader reader("54.71.61.211", 80);

    reader.addRequest("/v2/sports/football/leagues/nfl/events", "week1.json");
    reader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/2/events", "week2.json");
    reader.start();

    std::cout << "\nend";
    return 0;
}
