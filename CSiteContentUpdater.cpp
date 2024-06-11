#include "CSiteContentUpdater.hpp"
#include <fstream>
#include <iostream>
#include <regex>

constexpr auto filePath = "..\\website\\script.js";

//------------------------------------------------------------------
void CSiteContentUpdater::updateWatchOption(const std::string & gameId, const std::string& line, const std::string& newWatchOption)
{
    //<!--401671866--><ul id=\"ul_game\"><li class=\"li_game\" id=\"time\">18:00</li><li class=\"li_game\" id=\"team\">Detroit Lions</li><li class=\"li_game\" id=\"logo\"><img id=\"img_team\" src=\"img/Detroit Lions.png\" alt=\"team logo\"></li><li class=\"li_game\" id=\"at\">@</li><li class=\"li_game\" id=\"logo\"><img id=\"img_team\" src=\"img/Indianapolis Colts.png\" alt=\"team logo\"></li><li class=\"li_game\" id=\"team\">Indianapolis Colts</li><li class=\"li_game\" id=\"watch\">-</li><li class=\"li_game\" id=\"seen\">no</li></ul>

    // Regular expression to find the block for the specified ID
    std::string idPattern = "<!--" + gameId + "--><ul id=\"ul_game\">(.*?)</ul>";
    std::regex idRegex(idPattern, std::regex::extended);
    std::smatch match;

    // Check if the specified ID block is found
    if (std::regex_search(line, match, idRegex)) {
        // Extract the matched block
        std::string block = match.str(1);

        // Regular expression to find and replace the content within the <li id="watch"> tag
        std::string watchPattern = R"(<li class="li_game" id="watch">.*?</li>)";
        std::regex watchRegex(watchPattern);

        // Replace the content with newContent
        std::string newBlock = std::regex_replace(block, watchRegex, R"(<li class="li_game" id="watch">)" + newWatchOption + R"(</li>)");

        // Construct the new HTML string
        std::string newHtml = match.prefix().str() + "<!--" + gameId + "--><ul id=\"ul_game\">" + newBlock + "</ul>" + match.suffix().str();
        std::cout << newHtml;
    }
    else
    {
        std::cout << "no regex found";
    }
}

//------------------------------------------------------------------
void CSiteContentUpdater::updateSeen(const std::string & gameId)
{
}
