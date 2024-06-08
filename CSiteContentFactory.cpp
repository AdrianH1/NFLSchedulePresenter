#include "CSiteContentFactory.hpp"
#include <fstream>
#include <iostream>
#include <string>


constexpr std::string_view UL_GAME_OPEN = "<ul id=\"ul_game\">";
constexpr std::string_view UL_GAME_CLOSE = "</ul>";
constexpr auto filePath = "..\\website\\script.js";
// constexpr std::string_view LI_GAME_TIME_OPEN = "<li class=\"li_game\" id=\"time\">";
// constexpr std::string_view LI_GAME_TEAM_OPEN = "<li class=\"li_game\" id=\"team\">";
// constexpr std::string_view LI_GAME_LOGO_OPEN = "<li class=\"li_game\" id=\"logo\">";
// constexpr std::string_view LI_GAME_AT_OPEN = "<li class=\"li_game\" id=\"at\">";
// constexpr std::string_view LI_GAME_WATCH_OPEN = "<li class=\"li_game\" id=\"watch\">";
// constexpr std::string_view LI_GAME_SEEN_OPEN = "<li class=\"li_game\" id=\"seen\">";
// constexpr std::string_view LI_GAME_CLOSE = "</li>";
// constexpr std::string_view IMG_TEAM_OPEN = "<img id=\"img_team\" src=\"";
// constexpr std::string_view IMG_TEAM_CLOSE = "\" alt=\"Logo\"";

//------------------------------------------------------------------
namespace
{
std::string createLiGame(const std::string& id, const std::string& content)
{
    // <li class="li_game" id="time">07:00PM</li>
    return "<li class=\"li_game\" id=\"" + id + "\">" + content + "</li>";

}
std::string createImgLogo(const std::string& team)
{
    //<img id="img_team" src="img/Buffalo Bills.png" alt="Logo">
    return "<img id=\"img_team\" src=\"img/" + team + ".png\" alt=\"team logo\">";
}

std::string createId(const std::string& id)
{
    //<!--123456-->
    return "<!--" + id + "-->";
}
}

//------------------------------------------------------------------
std::string CSiteContentFactory::createGameList(const CGame & game)
{
    std::string result{};

    //<!--123456-->
    result += createId(game.m_gameId);

    // <ul id="ul_game">
    result += UL_GAME_OPEN;

    // <li class="li_game" id="time">07:00PM</li>
    result += createLiGame("time", game.m_time);

    // <li class="li_game" id="team">Buffalo Bills</li>
    result += createLiGame("team", game.m_guestTeam);

    // <li class="li_game" id="logo"><img id="img_team" src="img/Buffalo Bills.png" alt="Logo"></li>
    result += createLiGame("logo", createImgLogo(game.m_guestTeam));

    // <li class="li_game" id="at">@</li>
    result += createLiGame("at", "@");

    // <li class="li_game" id="logo"><img id="img_team" src="img/Chicago Bears.png" alt="Logo"></li>
    result += createLiGame("logo", createImgLogo(game.m_homeTeam));

    // <li class="li_game" id="team">Chicago Bears</li>
    result += createLiGame("team", game.m_homeTeam);

    // <li class="li_game" id="watch">Full</li>
    result += createLiGame("watch", "Full");

    // <li class="li_game" id="seen">yes</li>
    result += createLiGame("seen", "no");

    result += UL_GAME_CLOSE;
    // </ul>

    return result;
}

//------------------------------------------------------------------
std::vector<std::string> CSiteContentFactory::createWeekList(const CWeek & week)
{
    std::vector<std::string> gameList{};
    for (const auto& game : week.m_gamesPerWeek)
    {
        gameList.push_back(createGameList(game));
    }
    return gameList;
}

//------------------------------------------------------------------
void CSiteContentFactory::saveSiteContent()
{
    std::ifstream ifs(filePath);

    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    std::string line;
    std::string keyword = "week2";
    int lineNumber = 0;
    bool found = false;

    // Loop through each line in the file
    while (std::getline(ifs, line)) {
        lineNumber++;
        // Find the keyword in the current line
        if (line.find(keyword) != std::string::npos) {
            std::cout << "Found '" << keyword << "' on line " << lineNumber << ": " << line << std::endl;
            found = true;
            break; // Stop after finding the first occurrence
        }
    }

    if (!found) {
        std::cout << "'" << keyword << "' not found in the file" << std::endl;
    }
}
