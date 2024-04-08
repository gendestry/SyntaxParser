#include "syntaxParser.h"
#include <fstream>
#include <iostream>

#include "../utils/font.h"
#include "../utils/utils.h"

using Utils::Font;

namespace Parsing
{
    SyntaxParser::SyntaxParser(std::string syntaxPath, const Tokens &tokens)
        : m_SyntaxPath(syntaxPath), m_Tokens(tokens)
    {
    }

    SyntaxParser::~SyntaxParser()
    {
    }

    // -- private

    void SyntaxParser::parseSyntaxFile()
    {
        std::vector<std::string> lines = Utils::getFileStringVec(m_SyntaxPath);

        for (auto &line : lines)
        {
            bool ignore = false;

            if (line[0] == '#' || line.empty())
                continue;

            size_t namePos = line.find_first_of("= ");
            std::string name = line.substr(0, namePos);

            size_t patternPos = line.find_first_of("= ", namePos + 1);
            while (line[patternPos] == ' ' || line[patternPos] == '=')
                patternPos++;
            std::string pattern = line.substr(patternPos);

            auto patternTokens = Utils::splitByWhitespace(pattern);
            m_ParsedLines.push_back({name, patternTokens});
        }
    }

    // public

    void SyntaxParser::parseFileInput(std::string inputFilePath)
    {
        try
        {
            m_Input = Utils::getFileString(inputFilePath);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }
    }

    bool SyntaxParser::parseSyntax()
    {
        parseSyntaxFile();
        return false;
    }

    // print

    void SyntaxParser::printSyntax()
    {
    }

    void SyntaxParser::printParsedLines()
    {

        std::cout << std::endl
                  << Font::fgreen << " ==== INPUT SYNTAX ===="
                  << Font::reset << std::endl;

        for (auto &line : m_ParsedLines)
        {
            std::cout << Font::fyellow << "'" << line.name << "'" << Font::reset << "= ";
            for (auto token : line.tokens)
            {
                std::cout << Font::fblue << "[" << token << "]" << Font::reset << " ";
            }
            std::cout << std::endl;
        }
    }
}
