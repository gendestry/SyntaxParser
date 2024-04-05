#include <iostream>

#include "utils/font.h"
#include "parsing/parser.h"

using Utils::Font;

int main(int argc, char **argv)
{
    Parsing::TokenParser parser("tokens.txt");
    parser.parseFileInput("input.txt");

    if (!parser.parseTokens())
    {
        std::cout << Font::fred << "Error parsing tokens" << Font::reset << std::endl;
        return -1;
    }

    parser.printTokens();
    return 0;
}