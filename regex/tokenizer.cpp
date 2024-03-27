#include "tokenizer.h"
#include <iostream>

using namespace Regex;

void Tokenizer::tokenize(bool ignore_whitespace)
{
    std::vector<Regex::Token> &tokens = m_Tokens;
    std::string &pattern = m_Pattern;
    bool string = false;
    int start = 0;
    for (int i = 0; i < pattern.size(); i++)
    {
        char prev = pattern[i - 1];
        char c = pattern[i];

        switch (c)
        {
        case '\'':
            start = i++;
            for (; i < pattern.size(); i++)
            {
                c = pattern[i];

                if (c == '\'' && prev != '\\')
                {
                    tokens.push_back(Token(start, i, Token::TXT, pattern.substr(start + 1, i - start - 1)));
                    break;
                }

                prev = c;
            }
            break;

        case '\\':
            c = pattern[++i];
            if (c == 'c')
            {
                tokens.push_back(Token(i - 1, i, Token::CHAR));
            }
            else if (c == 'C')
            {
                tokens.push_back(Token(i - 1, i, Token::BIG_CHAR));
            }
            else if (c == 'T')
            {
                tokens.push_back(Token(i - 1, i, Token::ANY_CHAR));
            }
            else if (c == 'd')
            {
                tokens.push_back(Token(i - 1, i, Token::DIGIT));
            }
            else if (c == 'n')
            {
                tokens.push_back(Token(i - 1, i, Token::NEWLINE));
            }
            else
            {
                std::cout << "Error: unknown escape sequence" << std::endl;
            }
            break;

        case ' ':
            if (!ignore_whitespace)
                tokens.push_back(Token(i, i, Token::WHITE_SPACE));
            break;
        case '\t':
            if (!ignore_whitespace)
                tokens.push_back(Token(i, i, Token::TAB));
            break;
        case '+':
            tokens.push_back(Token(i, i, Token::PLUS));
            break;
        case '*':
            tokens.push_back(Token(i, i, Token::ASTERIX));
            break;
        case '-':
            tokens.push_back(Token(i, i, Token::MINUS));
            break;
        case '[':
            tokens.push_back(Token(i, i, Token::LBRACK));
            break;
        case ']':
            tokens.push_back(Token(i, i, Token::RBRACK));
            break;
        case '(':
            tokens.push_back(Token(i, i, Token::LPAREN));
            break;
        case ')':
            tokens.push_back(Token(i, i, Token::RPAREN));
            break;
        case '|':
            tokens.push_back(Token(i, i, Token::OR));
            break;
        };
    }
}

void Tokenizer::print_tokens()
{
    for (int i = 0; i < m_Tokens.size(); i++)
    {
        std::cout << m_Tokens[i].toString() << "[" << m_Tokens[i].startPos << "," << m_Tokens[i].endPos << "] ";
    }

    std::cout << std::endl;
}
