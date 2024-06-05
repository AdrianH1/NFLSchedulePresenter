#include "CApiDataCompiler.hpp"
#include "CApiDataReader.hpp"
#include "libs/nlohmann/json.hpp"
#include <iostream>
#include <memory>
#include <fstream>

int main(int argc, char const* argv[]) {
    std::cout << "start\n";

    //----------------------------------------------------
    //---READ API DATA------------------------------------
    //----------------------------------------------------
    // auto apiReader = std::make_unique<CApiDataReader>();
    // apiReader->getAllRegularSeasonEvents();
    // apiReader->extractEventsFromWeeks(13);
    // apiReader->getRegularSeasonEventDetails();

    //----------------------------------------------------
    //---COMPILE API DATA---------------------------------
    //----------------------------------------------------
    auto apiCompiler = std::make_unique <CApiDataCompiler>();
    apiCompiler->compileApiData();


    std::cout << "\nend";
    return 0;
}
