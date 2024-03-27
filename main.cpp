#include <fstream>
#include <iostream>
#include "regex/tokenizer.h"
#include "regex/syntax.h"

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
        size_t namePos = line.find_first_of("= ");
        std::string name = line.substr(0, namePos);

        size_t patternPos = line.find_first_of("= ", namePos + 1);
        while (line[patternPos] == ' ' || line[patternPos] == '=')
            patternPos++;
        std::string pattern = line.substr(patternPos);

        // std::cout << "Var: " << name << " " << namePos << std::endl;
        // std::cout << "Pattern: " << pattern << " " << pattern.size() << std::endl;

        Regex::Tokenizer tokenizer(pattern);
        tokenizer.tokenize();
        tokenizer.print_tokens();

        Regex::Syntax syntax(tokenizer.get_tokens());
        std::cout << syntax.parse() << std::endl;
    }

    return 0;
}