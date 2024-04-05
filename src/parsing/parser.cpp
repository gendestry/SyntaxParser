#include "parser.h"

#include <iostream>

#include "../input/fileParser.h"
#include "../utils/font.h"
#include "../utils/utils.h"
#include "../utils/lineCounter.h"

using Utils::Font;

namespace Parsing
{
    TokenParser::TokenParser(std::string tokenPath) : m_TokenPath(tokenPath)
    {
        m_FileParser = std::make_unique<Input::FileParser>(tokenPath);
        try
        {
            m_FileParser->parse();
        }
        catch (const std::exception &e)
        {
            std::cout << e.what() << std::endl;
            return;
        }

        m_FileParser->print();
        m_TokenMap = std::move(m_FileParser->getTokenMaps());
    }

    TokenParser::~TokenParser()
    {
    }

    void TokenParser::parseFileInput(std::string inputFilePath)
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

        m_LineCounter = std::make_unique<Utils::LineCounter>(m_Input);

        std::cout << std::endl
                  << Font::fgreen << " --- INPUT ---- \n"
                  << Font::reset
                  << Font::forange << "'" << m_Input << "'" << Font::reset << "\n"
                  << std::endl;
    }

    bool TokenParser::parseTokens()
    {
        std::string intermediate = m_Input;
        unsigned int pos = 0;

        while (true)
        {
            if (pos >= m_Input.size())
                break;

            PRINT(std::cout << " === POS[" << pos << "] === " << std::endl;)
            intermediate = m_Input.substr(pos);

            bool matched = false;
            for (auto &token : m_TokenMap)
            {
                std::string printableIntermediate = Utils::sanitizeString(intermediate);
                std::cout << " - Testing token: "
                          << Font::fyellow << "'" << token.tokenName << "'" << Font::reset
                          << " on: " << Font::fcyan << "'" << printableIntermediate << "' " << Font::reset;

                if (token.regex.match(intermediate))
                {
                    std::cout << Font::fgreen << "ok" << Font::reset << std::endl;

                    unsigned int _maxMatch = token.regex.getMaxMatch();
                    unsigned int _numLinesBetween = m_LineCounter->numLinesInBetween(pos, pos + _maxMatch);
                    unsigned int _lineOffset = m_LineCounter->getXOffset(pos);
                    unsigned int _start = pos - _lineOffset;
                    unsigned int _end = pos + _maxMatch - _lineOffset;

                    unsigned int _line = m_LineCounter->accumulate(pos);

                    // std::cout << "Num lines in between: " << _numLinesBetween << std::endl;
                    // std::cout << "Start: " << pos << " "
                    //           << " End: " << pos + _maxMatch << std::endl;
                    // std::cout << pos << " " << _start << " " << _end << std::endl;
                    // std::cout << (pos + _maxMatch) << " " << _end << std::endl;
                    // std::cout << "Line offset: " << _lineOffset << " at line: " << _line << std::endl;

                    if (_numLinesBetween == 0)
                    {
                        std::cout << Font::fred << "Matched token[" << _line + 1 << "][";
                    }
                    else
                    {
                        std::cout << Font::fred << "Matched token[" << _line + 1 << "-" << _numLinesBetween << "][";
                    }

                    std::cout << _start << ", " << _end << "]: "
                              << Font::fyellow << "'" << token.tokenName << "'" << Font::reset << ": "
                              << Font::fcyan << "'" << Utils::sanitizeString(token.regex.getMatch()) << "'" << Font::reset << std::endl;

                    m_Tokens.push_back({pos, pos + _maxMatch, token.tokenName, token.ignore});

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
                return false;
            }
        }

        std::cout << Font::bold << Font::fgreen << "SUCCESS" << Font::reset << std::endl;

        return true;
    }

    void TokenParser::printTokens()
    {
        std::cout << "\n"
                  << Font::fgreen << " --- PARSED TOKENS ---- \n"
                  << Font::reset;

        unsigned int oldLine = 0;
        for (auto &token : m_Tokens)
        {
            unsigned int linesBetween = m_LineCounter->numLinesInBetween(token.start, token.end);
            if (!token.ignore)
            {
                std::cout << token.name << "[" << token.start << "," << token.end << "] ";
            }
            for (unsigned int i = 0; i < linesBetween; i++)
            {
                std::cout << std::endl;
            }
        }

        std::cout << std::endl;
    }

};