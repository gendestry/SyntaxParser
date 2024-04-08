#pragma once

#include <string>
#include "token.h"

namespace Parsing
{
    class SyntaxParser
    {
        std::string m_SyntaxPath;
        std::string m_Input;
        Tokens m_Tokens;

        struct ParsedLine
        {
            std::string name;
            std::vector<std::string> tokens;
        };

        std::vector<ParsedLine> m_ParsedLines;

    public:
        SyntaxParser(std::string syntaxPath, const Tokens &tokens);
        ~SyntaxParser();

        void parseFileInput(std::string inputFilePath);
        bool parseSyntax();

        void printParsedLines();
        void printSyntax();

    private:
        void parseSyntaxFile();
    };

}
