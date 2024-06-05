#pragma once

#include <vector>
#include <string>
#include "Data/CWeek.hpp"

class CApiDataCompiler
{
public:
    std::vector<CWeek> compileApiData();
private:
    void readJsonFiles();
    void saveApiData();

    std::vector<CWeek> m_allData{};

};
