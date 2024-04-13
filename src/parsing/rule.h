#pragma once

#include <string>
#include <vector>

namespace Parsing
{

    struct Rule
    {
        std::string m_Name;
        std::string m_Return;

        std::vector<std::string> m_Patterns;

        Rule(const std::string &left, const std::string &right);

        bool ParseLeft(const std::string &left);
        bool ParseRight(const std::string &right);

        void print();
    };

}