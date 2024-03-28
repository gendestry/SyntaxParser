#include "syntax.h"
#include <iostream>

namespace Regex
{
    bool Syntax::isInter()
    {
        if (isParen())
        {
            m_AstTree.push_back(new AstNodeParen(m_Ops));
            return true;
        }
        else
        {
            int o = isOps();
            if (o == 1)
            {
                m_AstTree.push_back(new AstNodeEscape(m_EscapeType, m_OpType));
                return true;
            }
            else if (o == 2)
            {
                m_AstTree.push_back(new AstNodeTxt(m_Tokens[m_TokenPos].txt_value, m_OpType));
                return true;
            }
            return false;
        }

        return false;
    }

    int Syntax::isOps()
    {
        if (isEscapeOp())
        {

            return 1;
        }
        else if (isTxtOp())
        {

            return 2;
        }
        return 0;
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
                ops.push_back(m_Ops.back());
                while (isOr())
                {
                    ops.push_back(m_Ops.back());
                }

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
            isOperator();

            m_Ops.push_back(new AstNodeEscape(m_EscapeType, m_OpType));
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
            isOperator();

            m_Ops.push_back(new AstNodeTxt(m_Tokens[old].txt_value, m_OpType));
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
            m_EscapeType = EscapeType::CHAR;
            break;
        case Token::BIG_CHAR:
            m_EscapeType = EscapeType::BIG_CHAR;
            break;
        case Token::ANY_CHAR:
            m_EscapeType = EscapeType::ANY_CHAR;
            break;
        case Token::DIGIT:
            m_EscapeType = EscapeType::DIGIT;
            break;
        case Token::NEWLINE:
            m_EscapeType = EscapeType::NEWLINE;
            break;
        default:
            return false;
        }
        m_TokenPos++;
        return true;
    }

    bool Syntax::isOperator()
    {
        switch (m_Tokens[m_TokenPos].type)
        {
        case Token::PLUS:
            m_OpType = AstNodeOps::PLUS;
            m_TokenPos++;
            return true;
        case Token::ASTERIX:
            m_OpType = AstNodeOps::ASTERIX;
            m_TokenPos++;
            return true;
        }

        m_OpType = OpType::NONE;
        return false;
    }

    void Syntax::printAst()
    {
        for (auto &node : m_AstTree)
        {
            std::cout << node->toString() << std::endl;
        }
    }
};