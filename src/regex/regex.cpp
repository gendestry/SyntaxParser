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

    Regex::Regex(const Regex &other)
        : m_Pattern(other.m_Pattern),
          m_Valid(other.m_Valid),
          m_Tokenizer(std::make_unique<Tokenizer>(*other.m_Tokenizer)),
          m_Syntax(std::make_unique<Syntax>(*other.m_Syntax))
    {
    }

    Regex::Regex(Regex &&other) noexcept
        : m_Pattern(std::move(other.m_Pattern)),
          m_Tokenizer(std::move(other.m_Tokenizer)),
          m_Syntax(std::move(other.m_Syntax)),
          m_Valid(other.m_Valid)
    {
    }

    // operators
    Regex &Regex::operator=(const Regex &other)
    {
        if (this != &other)
        {
            m_Pattern = other.m_Pattern;
            m_Valid = other.m_Valid;
            m_Tokenizer = std::make_unique<Tokenizer>(*other.m_Tokenizer);
            m_Syntax = std::make_unique<Syntax>(*other.m_Syntax);
        }

        return *this;
    }

    Regex &Regex::operator=(Regex &&other) noexcept
    {
        if (this != &other)
        {
            m_Pattern = std::move(other.m_Pattern);
            m_Tokenizer = std::move(other.m_Tokenizer);
            m_Syntax = std::move(other.m_Syntax);
            m_Valid = other.m_Valid;
        }

        return *this;
    }

    void Regex::printTokens()
    {
        m_Tokenizer->print_tokens();
    }

    void Regex::printAst()
    {
        if (m_Valid)
            m_Syntax->printAst();
    }

    void Regex::prettyPrint()
    {
        if (m_Valid)
        {
            for (auto &p : m_Syntax->getPattern())
            {
                std::cout << p->toPrettyString();
            }
            std::cout << std::endl;
        }
    }

    bool Regex::match(std::string text)
    {
        if (!m_Valid)
            return false;

        Pattern &pattern = m_Syntax->getPattern();
        unsigned int start = 0;

        for (Pos i = 0; i < pattern.size(); i++)
        {
            std::cout << "Matching: " << pattern[i]->toPrettyString() << std::endl;

            auto [matched, current] = pattern[i]->match(text, start);
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