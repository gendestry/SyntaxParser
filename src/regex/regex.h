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

        void print_tokens();
        void print_ast();

        bool match(std::string text);
    };
};