#include <fstream>
#include <iostream>
#include <unordered_map>
#include "regex/regex.h"

int main(int argc, char **argv)
{
    std::ifstream file("input.txt");

    if (!file.is_open())
    {
        std::cout << "Error: file not found" << std::endl;
        return 1;
    }

    std::string line;
    std::unordered_map<std::string, Regex::Regex &> tokenMap;
    while (std::getline(file, line))
    {
        if (line[0] == '#' || line.empty())
            continue;

        size_t namePos = line.find_first_of("= ");
        std::string name = line.substr(0, namePos);

        size_t patternPos = line.find_first_of("= ", namePos + 1);
        while (line[patternPos] == ' ' || line[patternPos] == '=')
            patternPos++;
        std::string pattern = line.substr(patternPos);

        // std::cout << "Var: " << name << " " << namePos << std::endl;
        // std::cout << "Pattern: " << pattern << " " << pattern.size() << std::endl;

        Regex::Regex regex(pattern);
        // tokenMap[name] = regex;
        // regex.print_tokens();
        // regex.printAst();
        regex.prettyPrint();
        if (argc == 2)
        {
            if (regex.match(argv[1]))
            {
                std::cout << "Matched token: '" << name << "'" << std::endl;
            }
            else
            {
                std::cout << "Invalid match" << std::endl;
            }
        }
        else
        {
            std::cout << "Missing input argument" << std::endl;
        }
    }

    return 0;
}