#include <fstream>
#include <iostream>
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
    while (std::getline(file, line))
    {
        // get string until first whitespace or equals sign

        if (line[0] == '#')
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
        // regex.print_tokens();
        // regex.print_ast();
        // return 0;
        if (argc == 2)
        {
            if (regex.match(argv[1]))
            {
                std::cout << "Perfect" << std::endl;
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