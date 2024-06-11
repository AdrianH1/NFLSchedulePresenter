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
    result += createLiGame("watch", "-");

    // <li class="li_game" id="seen">yes</li>
    result += createLiGame("seen", "no");

    result += UL_GAME_CLOSE;
    // </ul>

    result += "\n";

    return result;
}

//------------------------------------------------------------------
std::vector<std::string> CSiteContentFactory::createWeekList(CWeek & week)
{
    std::vector<std::string> gameList{};
    std::string day{};
    for (const auto& game : week.m_gamesPerWeek)
    {
        if (game.m_day.compare(day))
        {
            gameList.push_back("<h1 id=\"day_title\">" + game.m_day + "</h1>");
            day = game.m_day;
        }
        gameList.push_back(createGameList(game));
    }
    return gameList;
}

//------------------------------------------------------------------
void CSiteContentFactory::saveSiteContent(std::unordered_map<std::string, CWeek>& data)
{
    std::ifstream ifs(filePath);

    if (!ifs.is_open()) {
        std::cerr << "Error opening file: " << filePath << std::endl;
        return;
    }

    // Read the entire file into a vector of strings
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(ifs, line)) {
        lines.push_back(line);
    }
    ifs.close(); // Close the file after reading

    for (const auto& [key, value] : data)
    {
        std::string keyword = value.m_name;
        bool found = false;

        // Iterate through the lines to find and replace the keyword
        for (auto& file_line : lines) {
            if (file_line.find(keyword) != std::string::npos) {
                std::cout << "Found '" << keyword << "' on line: " << file_line << std::endl;

                while (file_line.find("content") != std::string::npos)
                {
                    std::string fullWeekHtmlString{};
                    auto title = "Week " + key.substr(4, key.size());
                    fullWeekHtmlString += "<h1 id=\"site_title\">" + title + "</h1>";
                    for (const auto& s : createWeekList(data.at(key)))
                    {
                        fullWeekHtmlString += s;
                    }
                    file_line.replace(file_line.find("content"), 7, fullWeekHtmlString);
                }

                found = true;
                break; // Stop after finding the first occurrence
            }
        }

        if (!found) {
            std::cout << "'" << keyword << "' not found in the file" << std::endl;
        }
    }

    // Write the modified content back to the file
    std::ofstream ofs(filePath);
    if (!ofs) {
        std::cerr << "Failed to open the file for writing." << std::endl;
        return;
    }

    for (const auto& file_line : lines) {
        ofs << file_line << std::endl;
    }
    ofs.close(); // Close the file after writing

}
