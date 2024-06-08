#include "CApiDataCompiler.hpp"
#include "CApiDataReader.hpp"
#include "CSiteContentFactory.hpp"
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
    auto data = apiCompiler->compileApiData();

    //----------------------------------------------------
    //---CREATE SITE CONTENT------------------------------
    //----------------------------------------------------
    auto contentFactory = std::make_unique<CSiteContentFactory>();
    auto list = contentFactory->createGameList(data.at(0).m_gamesPerWeek.at(0));
    std::cout << list << std::endl;
    contentFactory->saveSiteContent();

    std::cout << "\nend";
    return 0;
}
