#pragma once

#include <string>
#include <vector>

class CInputValidator
{
public:
    std::vector<std::string> readInput();
private:

    bool inputValid(std::vector<std::string>* input);
    std::vector<std::string> separateInput(std::string* inputLine);
    void lowerCase(std::vector<std::string>& inputline);

    std::vector<std::string> m_cmd = { "set" };
};