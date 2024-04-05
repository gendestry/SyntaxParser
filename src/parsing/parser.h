#pragma once
#include <string>
#include <memory>

#include "../input/fileParser.h"
#include "../utils/lineCounter.h"

namespace Parsing
{
    struct Token
    {
        unsigned int start, end;
        std::string name;
        bool ignore = false;
    };

    class TokenParser
    {
        std::unique_ptr<Input::FileParser> m_FileParser;
        std::unique_ptr<Utils::LineCounter> m_LineCounter;

        std::vector<Token> m_Tokens;
        Input::TokenMap m_TokenMap;
        std::string m_TokenPath;
        std::string m_Input;

    public:
        TokenParser(std::string tokenPath);
        ~TokenParser();

        void parseFileInput(std::string inputFilePath);
        bool parseTokens();

        void printTokens();

        const std::string &getInput() const
        {
            return m_Input;
        }
    };
};