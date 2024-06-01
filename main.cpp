#include <iostream>
#include "CApiReader.hpp"

int main(int argc, char const* argv[]) {
    std::cout << "start\n";

    CApiReader eventReader("54.71.61.211", 80);

    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/1/events", "..\\apiData\\week1_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/2/events", "..\\apiData\\week2_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/3/events", "..\\apiData\\week3_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/4/events", "..\\apiData\\week4_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/5/events", "..\\apiData\\week5_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/6/events", "..\\apiData\\week6_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/7/events", "..\\apiData\\week7_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/8/events", "..\\apiData\\week8_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/9/events", "..\\apiData\\week9_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/10/events", "..\\apiData\\week10_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/11/events", "..\\apiData\\week11_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/12/events", "..\\apiData\\week12_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/13/events", "..\\apiData\\week13_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/14/events", "..\\apiData\\week14_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/15/events", "..\\apiData\\week15_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/16/events", "..\\apiData\\week16_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/17/events", "..\\apiData\\week17_events.json");
    eventReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/18/events", "..\\apiData\\week18_events.json");
    eventReader.start();

    // CApiReader gameReader("54.71.61.211", 80);
    // gameReader.start();

    // gameReader.addRequest("/v2/sports/football/leagues/nfl/seasons/2024/types/2/weeks/18/events", "week18_events.json");


    std::cout << "\nend";
    return 0;
}
