#include "CSiteContentUpdater.hpp"
#include <fstream>
#include <iostream>
#include <regex>

constexpr auto filePath = "..\\website\\script.js";

//------------------------------------------------------------------
std::string CSiteContentUpdater::updateWatchOption(const std::string & gameId, const std::string& line, const std::string& newWatchOption)
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
        return newHtml;
    }
    else
    {
        std::cout << "no regex found";
        return std::string{};
    }
}

//------------------------------------------------------------------
std::string CSiteContentUpdater::updateSeen(const std::string& gameId, const std::string& line, const std::string& newSeenOption)
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
        std::string watchPattern = R"(<li class="li_game" id="seen">.*?</li>)";
        std::regex watchRegex(watchPattern);

        // Replace the content with newContent
        std::string newBlock = std::regex_replace(block, watchRegex, R"(<li class="li_game" id="seen">)" + newSeenOption + R"(</li>)");

        // Construct the new HTML string
        std::string newHtml = match.prefix().str() + "<!--" + gameId + "--><ul id=\"ul_game\">" + newBlock + "</ul>" + match.suffix().str();
        return newHtml;
    }
    else
    {
        std::cout << "no regex found";
        return std::string{};
    }
}

//------------------------------------------------------------------
std::string CSiteContentUpdater::searchLine(const std::string & gameId, const std::string& newWatchOption, const std::string& newSeenOption)
{
    std::ifstream inputFile(filePath);
    if (!inputFile) {
        std::cerr << "Could not open the file for reading: " << filePath << std::endl;
        return std::string{};
    }

    std::ostringstream tempBuffer;
    std::string line;
    std::string idPattern = "<!--" + gameId + "-->";

    while (std::getline(inputFile, line)) {
        if (line.find(idPattern) != std::string::npos) {
            std::string newLine = line;
            auto lineChanged{ false };
            if (!newWatchOption.empty())
            {
                newLine = updateWatchOption(gameId, newLine, newWatchOption);
                lineChanged = true;
            }
            if (!newSeenOption.empty())
            {
                newLine = updateSeen(gameId, newLine, newSeenOption);
                lineChanged = true;
            }

            if (lineChanged)
            {
                tempBuffer << newLine << "\n";
            }
            else
            {
                tempBuffer << line << "\n";
            }
        }
        else {
            tempBuffer << line << "\n";
        }
    }

    inputFile.close();

    std::ofstream outputFile(filePath);
    if (!outputFile) {
        std::cerr << "Could not open the file for writing: " << filePath << std::endl;
        return std::string{};
    }

    outputFile << tempBuffer.str();
    outputFile.close();
    return std::string{};
}
