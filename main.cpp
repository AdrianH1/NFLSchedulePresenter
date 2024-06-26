#include "CApiDataCompiler.hpp"
#include "CApiDataReader.hpp"
#include "CInputValidator.hpp"
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
    // for (int i = 1; i <= 18; i++)
    // {
    //     apiReader->extractEventsFromWeeks(i);
    // }
    // apiReader->getRegularSeasonEventDetails();

    //----------------------------------------------------
    //---COMPILE API DATA---------------------------------
    //----------------------------------------------------
    auto apiCompiler = std::make_unique<CApiDataCompiler>();
    auto data = apiCompiler->compileApiData();

    //----------------------------------------------------
    //---CREATE SITE CONTENT------------------------------
    //----------------------------------------------------
    auto contentFactory = std::make_unique<CSiteContentFactory>();
    contentFactory->saveSiteContent(data);

    /*
        //----------------------------------------------------
        //---APPLICATION MAIN LOOP----------------------------
        //----------------------------------------------------
        while (true)
        {
            //----------------------------------------------------
            //---CMD line UI--------------------------------------
            //----------------------------------------------------
            auto inputValidator = std::make_unique<CInputValidator>();
            auto input = inputValidator->readInput();
            // set week3 5 watchOption Full
            auto gameid = data.at(input.at(1)).m_gamesPerWeek.at(std::stoi(input.at(2)) - 1).m_gameId;
            std::cout << gameid << std::endl;

            //----------------------------------------------------
            //---UPDATE SITE CONTENT------------------------------
            //----------------------------------------------------
            auto contentUpdater = std::make_unique<CSiteContentUpdater>();
            if (input.at(3) == "watchoption")
            {
                contentUpdater->searchLine(gameid, input.at(4), "");
            }
            else if (input.at(3) == "seen")
            {
                contentUpdater->searchLine(gameid, "", input.at(4));
            }
        }
    */

    std::cout << "\nend";
    return 0;
}
