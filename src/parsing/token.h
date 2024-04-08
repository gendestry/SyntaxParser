#pragma once
#include <vector>
#include <string>

namespace Parsing
{

    struct Token
    {
        unsigned int start, end;
        std::string name;
        bool ignore = false;
    };

    using Tokens = std::vector<Token>;
};