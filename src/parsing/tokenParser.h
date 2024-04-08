#pragma once
#include <string>
#include <memory>

#include "../input/fileParser.h"
#include "../utils/lineCounter.h"
#include "token.h"

namespace Parsing
{

    class TokenParser
    {
        std::unique_ptr<Input::FileParser> m_FileParser;
        std::unique_ptr<Utils::LineCounter> m_LineCounter;

        Tokens m_Tokens;
        Input::TokenMap m_TokenMap;
        std::string m_TokenPath;
        std::string m_Input;

    public:
        TokenParser(std::string tokenPath);
        ~TokenParser();

        void parseFileInput(std::string inputFilePath);
        bool parseTokens();

        void printTokens();

        inline const std::string &getInput() const
        {
            return m_Input;
        }

        inline const Tokens &getTokens() const
        {
            return m_Tokens;
        }
    };
};