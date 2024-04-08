#include <iostream>

#include "utils/font.h"
#include "parsing/tokenParser.h"
#include "parsing/syntaxParser.h"

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

    Parsing::SyntaxParser syntaxParser("syntax.txt", parser.getTokens());
    syntaxParser.parseSyntax();
    syntaxParser.printParsedLines();
    return 0;
}