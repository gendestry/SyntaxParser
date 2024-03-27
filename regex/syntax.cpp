#include "syntax.h"

namespace Regex
{
    bool Syntax::isInter()
    {
        return isParen() || isOps();
    }

    bool Syntax::isOps()
    {
        return isEscapeOp() || isTxtOp();
    }

    bool Syntax::isParen()
    {
        auto isOr = [&]() -> bool
        {
            Pos old = m_TokenPos;
            if (m_Tokens[m_TokenPos++].type == Token::OR)
            {
                if (isOps())
                {
                    return true;
                }
            }

            m_TokenPos = old;
            return false;
        };

        Pos old = m_TokenPos;
        if (m_Tokens[m_TokenPos].type == Token::LPAREN)
        {
            std::vector<AstNodeOps *> ops;
            m_TokenPos++;
            if (isOps())
            {
                while (isOr())
                    ;

                if (m_Tokens[m_TokenPos++].type == Token::RPAREN)
                {
                    return true;
                }
            }
            return false;
        }

        m_TokenPos = old;
        return false;
    }

    bool Syntax::isEscapeOp()
    {
        if (isEscape())
        {
            if (isOperator())
            {
            }
            return true;
        }
        return false;
    }

    bool Syntax::isTxtOp()
    {
        Pos old = m_TokenPos;
        if (m_Tokens[m_TokenPos].type == Token::TXT)
        {
            m_TokenPos++;
            if (isOperator())
            {
            }
            return true;
        }

        m_TokenPos = old;
        return false;
    }

    bool Syntax::isEscape()
    {
        switch (m_Tokens[m_TokenPos].type)
        {
        case Token::CHAR:
        case Token::BIG_CHAR:
        case Token::ANY_CHAR:
        case Token::DIGIT:
        case Token::NEWLINE:
            m_TokenPos++;
            return true;
        }

        return false;
    }

    bool Syntax::isOperator()
    {
        switch (m_Tokens[m_TokenPos].type)
        {
        case Token::PLUS:
        case Token::ASTERIX:

            m_TokenPos++;
            return true;
        }

        return false;
    }
};