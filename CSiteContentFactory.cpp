#include "CSiteContentFactory.hpp"

constexpr std::string_view UL_GAME_OPEN = "<ul id=\"ul_game\">";
constexpr std::string_view UL_GAME_CLOSE = "</ul>";
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
}

// <ul id="ul_game">
// <li class="li_game" id="time">07:00PM</li>
// <li class="li_game" id="team">Buffalo Bills</li>
// <li class="li_game" id="logo"><img id="img_team" src="img/Buffalo Bills.png" alt="Logo">
// </li>
// <li class="li_game" id="at">@</li>
// <li class="li_game" id="logo"><img id="img_team" src="img/Chicago Bears.png" alt="Logo">
// </li>
// <li class="li_game" id="team">Chicago Bears</li>
// <li class="li_game" id="watch">Full</li>
// <li class="li_game" id="seen">yes</li>
// </ul>

//------------------------------------------------------------------
std::string CSiteContentFactory::createGameList(CGame & game)
{
    std::string result{};

    // <ul id="ul_game">
    result += UL_GAME_OPEN;

    // <li class="li_game" id="time">07:00PM</li>
    result += createLiGame("time", game.m_date);

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
    // </ul>

    return result;
}

//------------------------------------------------------------------
std::vector<std::string> CSiteContentFactory::createWeekList(CWeek & week)
{
    return std::vector<std::string>();
}
