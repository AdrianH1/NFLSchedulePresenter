#include "CApiDataCompiler.hpp"
#include "CApiDataReader.hpp"
#include "CSiteContentFactory.hpp"
#include "CSiteContentUpdater.hpp"
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
    // auto apiCompiler = std::make_unique <CApiDataCompiler>();
    // auto data = apiCompiler->compileApiData();

    //----------------------------------------------------
    //---CREATE SITE CONTENT------------------------------
    //----------------------------------------------------
    // auto contentFactory = std::make_unique<CSiteContentFactory>();
    // auto list = contentFactory->createGameList(data.at(0).m_gamesPerWeek.at(0));
    // std::cout << list << std::endl;
    // contentFactory->saveSiteContent(data);

    //----------------------------------------------------
    //---UPDATE SITE CONTENT------------------------------
    //----------------------------------------------------
    auto contentUpdater = std::make_unique<CSiteContentUpdater>();
    std::string line = "<!--401671866--><ul id=\"ul_game\"><li class=\"li_game\" id=\"time\">18:00</li><li class=\"li_game\" id=\"team\">Detroit Lions</li><li class=\"li_game\" id=\"logo\"><img id=\"img_team\" src=\"img/Detroit Lions.png\" alt=\"team logo\"></li><li class=\"li_game\" id=\"at\">@</li><li class=\"li_game\" id=\"logo\"><img id=\"img_team\" src=\"img/Indianapolis Colts.png\" alt=\"team logo\"></li><li class=\"li_game\" id=\"team\">Indianapolis Colts</li><li class=\"li_game\" id=\"watch\">-</li><li class=\"li_game\" id=\"seen\">no</li></ul>";
    contentUpdater->updateWatchOption("401671866", line, "HUUG");

    std::cout << "\nend";
    return 0;
}
