#pragma once

#include <vector>
#include <sstream>

namespace fix::com::utils
{
    template<char C>
    std::vector<std::string> split(const std::string &_str)
    {
        std::vector<std::string> result;
        std::istringstream ss(_str);
        std::string token;

        while (std::getline(ss, token, C))
            result.push_back(token);
        return result;
    }
}