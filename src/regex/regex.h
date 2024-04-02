#pragma once
#include <string>
#include <memory>
#include "tokenizer.h"
#include "syntax.h"

namespace Regex
{
    class Regex
    {
        bool m_Valid = true;
        std::string m_Pattern;
        std::unique_ptr<Tokenizer> m_Tokenizer;
        std::unique_ptr<Syntax> m_Syntax;

    public:
        Regex(std::string pattern);
        Regex(const Regex &other);
        Regex(Regex &&other) noexcept;

        Regex &operator=(const Regex &other);
        Regex &operator=(Regex &&other) noexcept;

        void printTokens();
        void printAst();
        void prettyPrint();

        bool match(std::string text);
    };
};