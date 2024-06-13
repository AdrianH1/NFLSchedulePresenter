#include "CInputValidator.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

// set week3 5 watchOption Full
// set week4 6 seen yes

constexpr auto sSet = "set";

//------------------------------------------------------------------
std::vector<std::string> CInputValidator::readInput()
{
    std::string inputLine;
    std::vector<std::string> input;

    while (!inputValid(&input))
    {
        std::cout << std::endl << ">>>";
        std::getline(std::cin, inputLine);
        inputLine = lowerCase(inputLine);
        input = separateInput(&inputLine);
    }
    return input;
}

//------------------------------------------------------------------
bool CInputValidator::inputValid(std::vector<std::string>* input)
{
    if (input->size() == 0) { return false; }
    std::string command = input->at(0);
    size_t argsCount = input->size();

    //Search if the given command is part of the moduleCmd vector and therefore is a valid command.
    if (std::find(m_cmd.begin(), m_cmd.end(), command) != m_cmd.end())
    {
        if (command == sSet && argsCount == 5)
        {
            return true;
        }
    }
    std::cout << "ERROR: invalid command\n";
    return false;
}

//------------------------------------------------------------------
std::vector<std::string> CInputValidator::separateInput(std::string* inputLine)
{
    std::vector<std::string> input;
    std::stringstream ss(*inputLine);
    std::string word;

    while (ss >> word)
    {
        input.push_back(word);
    }

    return input;
}

//------------------------------------------------------------------
std::string CInputValidator::lowerCase(std::string inputline)
{
    std::string result = "";
    for (char c : inputline)
    {
        result += std::tolower(c);
    }
    return result;
}