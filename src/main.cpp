#include <fstream>
#include <iostream>
#include <vector>
#include <map>

#include "regex/regex.h"
#include "utils/font.h"
#include "utils/lineCounter.h"
#include "utils/utils.h"
#include "input/fileParser.h"

using Utils::Font;

struct Token
{
    unsigned int start, end;
    std::string name;
    bool ignore = false;
};

std::vector<Token> tokens;

int main(int argc, char **argv)
{
    Input::FileParser fileParser("tokens.txt");
    try
    {
        fileParser.parse();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return -1;
    }

    fileParser.print();
    Input::TokenMap &tokenMaps = fileParser.getTokenMaps();

    // read input file
    std::string input;
    try
    {
        input = Utils::getFileString("input.txt");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return -1;
    }

    std::cout << std::endl
              << Font::fgreen << " --- INPUT ---- \n"
              << Font::reset
              << Font::forange << "'" << input << "'" << Font::reset << "\n"
              << std::endl;

    std::cout << Font::fgreen << " --- PARSING ---- " << Font::reset << std::endl;

    // parse input file using tokens obtained from tokens.txt
    Utils::LineCounter lineCounter(input);
    std::string intermediate = input;
    unsigned int pos = 0;

    while (true)
    {
        if (pos >= input.size())
            break;

        PRINT(std::cout << " === POS[" << pos << "] === " << std::endl;)
        intermediate = input.substr(pos);

        bool matched = false;
        for (auto &token : tokenMaps)
        {
            std::string printableIntermediate = Utils::sanitizeString(intermediate);
            std::cout << " - Testing token: "
                      << Font::fyellow << "'" << token.tokenName << "'" << Font::reset
                      << " on: '" << printableIntermediate << "' ";

            if (token.regex.match(intermediate))
            {
                std::cout << Font::fgreen << "ok" << Font::reset << std::endl;

                unsigned int _maxMatch = token.regex.getMaxMatch();
                unsigned int _numLinesBetween = lineCounter.numLinesInBetween(pos, pos + _maxMatch);
                unsigned int _lineOffset = lineCounter.getXOffset(pos);
                unsigned int _start = pos - _lineOffset;
                unsigned int _end = pos + _maxMatch - _lineOffset;

                unsigned int _line = lineCounter[pos];

                // std::cout << "Num lines in between: " << _numLinesBetween << std::endl;
                // std::cout << "Start: " << pos << " "
                //           << " End: " << pos + _maxMatch << std::endl;
                // std::cout << pos << " " << _start << " " << _end << std::endl;
                // std::cout << (pos + _maxMatch) << " " << _end << std::endl;
                // std::cout << "Line offset: " << _lineOffset << " at line: " << _line << std::endl;

                if (_numLinesBetween == 0)
                {
                    std::cout << Font::fred << "Matched token[" << _line << "][";
                }
                else
                {
                    std::cout << Font::fred << "Matched token[" << _line << "-" << _numLinesBetween - 1 << "][";
                }

                std::cout << _start << ", " << _end << "]: "
                          << Font::fyellow << "'" << token.tokenName << "'" << Font::reset << ": "
                          << Font::fcyan << "'" << Utils::sanitizeString(token.regex.getMatch()) << "'" << Font::reset << std::endl;

                tokens.push_back({pos, pos + _maxMatch, token.tokenName, token.ignore});

                pos += _maxMatch;
                matched = true;
                break;
            }
            else
            {
                std::cout << Font::fred << "err" << Font::reset << std::endl;
            }
        }

        if (!matched)
        {
            std::cout << Font::bold << Font::fred << "NO MATCH FOUND FOR: '" << intermediate << "'" << Font::reset << std::endl;
            return -1;
        }
    }

    std::cout << Font::bold << Font::fgreen << "SUCCESS" << Font::reset << std::endl;

    std::cout << "\n"
              << Font::fgreen << " --- PARSED TOKENS ---- \n"
              << Font::reset;

    unsigned int oldLine = 0;
    for (auto &token : tokens)
    {
        unsigned int linesBetween = lineCounter.numLinesInBetween(token.start, token.end);
        if (!token.ignore)
        {
            std::cout << token.name << "[" << token.start << "," << token.end << "] ";
        }
        for (unsigned int i = 0; i < linesBetween; i++)
        {
            std::cout << std::endl;
        }
    }

    std::cout << "\n"
              << std::endl;
    return 0;
}