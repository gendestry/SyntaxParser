#include "rule.h"

#include <iostream>
#include "../utils/font.h"
#include "../utils/utils.h"
using Utils::Font;

namespace Parsing
{
    Rule::Rule(const std::string &left, const std::string &right)
    {

        if (!ParseLeft(left))
            throw std::runtime_error("Error: Invalid left side of rule: " + left);

        if (!ParseRight(right))
            throw std::runtime_error("Error: Invalid right side of rule: " + right);
    }

    bool Rule::ParseLeft(const std::string &left)
    {
        if (left.size() == 0)
            return false;

        size_t pos = 0;
        if ((pos = left.find("[")) != std::string::npos)
        {
            m_Name = Utils::removeEnclosingWhitespaces(left.substr(0, pos));
            m_Return = Utils::removeEnclosingWhitespaces(left.substr(pos + 1, left.size() - pos - 2));
        }
        else
        {
            m_Name = Utils::removeEnclosingWhitespaces(left);
            m_Return = "";
        }

        return true;
    }

    bool Rule::ParseRight(const std::string &right)
    {
        if (right.size() == 0)
            return false;

        std::vector<std::string> patterns = Utils::split(right, "|");

        for (auto &pattern : patterns)
        {
            m_Patterns.push_back(Utils::removeEnclosingWhitespaces(pattern));
        }
        return true;
    }

    void Rule::print()
    {
        std::cout << Font::fyellow << m_Name;
        if (m_Return.size() > 0)
            std::cout << " -> " << m_Return;

        if (m_Patterns.size() == 1)
        {
            std::cout << " ( " << Font::reset
                      << Font::fcyan << m_Patterns[0] << Font::reset
                      << Font::fyellow << " )" << std::endl;

            return;
        }
        std::cout << Font::fyellow << " (\n"
                  << Font::reset;

        for (auto &pattern : m_Patterns)
        {
            std::cout << Font::fcyan << "  (" << pattern << ")\n";
        }

        std::cout << Font::fyellow << ")" << Font::reset << std::endl;
    }
};
