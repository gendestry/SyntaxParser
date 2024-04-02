#include <iostream>
#include "regex.h"

namespace Regex
{
    Regex::Regex(std::string pattern) : m_Pattern(pattern)
    {
        m_Tokenizer = std::make_unique<Tokenizer>(pattern);
        m_Tokenizer->tokenize();

        m_Syntax = std::make_unique<Syntax>(m_Tokenizer->get_tokens());
        m_Valid = m_Syntax->parse();
        if (!m_Valid)
        {
            std::cout << "Error: invalid syntax" << std::endl;
        }
    }

    void Regex::print_tokens()
    {
        m_Tokenizer->print_tokens();
    }

    void Regex::print_ast()
    {
        if (m_Valid)
            m_Syntax->printAst();
    }

    bool Regex::match(std::string text)
    {
        if (!m_Valid)
            return false;

        AstTree &ast = m_Syntax->getAstTree();
        unsigned int start = 0;

        for (Pos i = 0; i < ast.size(); i++)
        {
            std::cout << "Matching: " << ast[i]->toString() << std::endl;

            auto [matched, current] = ast[i]->match(text, start);
            if (matched)
            {
                std::cout << "Matched: '" << text.substr(start, current - start) << "'" << std::endl;
            }
            else
            {
                std::cout << "Not matched" << std::endl;
                return false;
            }
            start = current;
        }

        return start == text.size();
    }
};