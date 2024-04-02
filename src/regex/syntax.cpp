#include "syntax.h"
#include <iostream>

namespace Regex
{
    bool Syntax::parse()
    {
        if (isInter())
        {
            while (isInter())
                ;
            return true;
        }

        return false;
    }

    bool Syntax::isInter()
    {
        Pos old = m_TokenPos;
        if (isParen())
        {
            m_AstTree.push_back(m_Op);
            return true;
        }
        else if (isEscapeOp())
        {
            m_AstTree.push_back(m_Op);
            return true;
        }
        else if (isTxtOp())
        {
            m_AstTree.push_back(m_Op);
            return true;
        }

        m_TokenPos = old;
        return false;
    }

    bool Syntax::isParen()
    {
        auto isOr = [&]() -> bool
        {
            Pos old = m_TokenPos;
            if (m_Tokens[m_TokenPos++].type == Token::OR)
            {
                if (isEscapeOp())
                {
                    return true;
                }
                else if (isTxtOp())
                {
                    return true;
                }
            }

            m_TokenPos = old;
            return false;
        };

        std::vector<AstNodeOps *> ops;
        Pos old = m_TokenPos;

        if (m_Tokens[m_TokenPos].type == Token::LPAREN)
        {
            m_TokenPos++;
            if (isEscapeOp() || isTxtOp())
            {
                ops.push_back(m_Op);
                if (isOr())
                {
                    ops.push_back(m_Op);
                }
                else
                {
                    m_TokenPos = old;
                    return false;
                }
                while (isOr())
                {
                    ops.push_back(m_Op);
                }

                if (m_Tokens[m_TokenPos++].type == Token::RPAREN)
                {
                    isOperator();
                    m_Op = new AstNodeParen({m_Tokens[old].startPos, m_Tokens[m_TokenPos].endPos}, ops, m_OpType);
                    return true;
                }
            }

            for (auto &op : ops)
            {
                delete op;
            }

            m_TokenPos = old;
            return false;
        }

        m_TokenPos = old;
        return false;
    }

    bool Syntax::isEscapeOp()
    {
        Pos old = m_TokenPos;
        if (isEscape())
        {
            isOperator();

            m_Op = new AstNodeEscape({m_Tokens[old].startPos, m_Tokens[m_TokenPos].endPos}, m_EscapeType, m_OpType);
            return true;
        }

        m_TokenPos = old;
        return false;
    }

    bool Syntax::isTxtOp()
    {
        if (m_TokenPos >= m_Tokens.size())
            return false;

        Pos old = m_TokenPos;
        if (m_Tokens[m_TokenPos].type == Token::TXT)
        {
            m_TokenPos++;
            isOperator();

            m_Op = new AstNodeTxt({m_Tokens[old].startPos, m_Tokens[m_TokenPos].endPos}, m_Tokens[old].txt_value, m_OpType);
            return true;
        }

        m_TokenPos = old;
        return false;
    }

    bool Syntax::isEscape()
    {
        if (m_TokenPos >= m_Tokens.size())
            return false;

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
        if (m_TokenPos >= m_Tokens.size())
        {
            m_OpType = OpType::NONE;
            return false;
        }

        switch (m_Tokens[m_TokenPos].type)
        {
        case Token::PLUS:
            m_OpType = AstNodeOps::PLUS;
            break;
        case Token::ASTERIX:
            m_OpType = AstNodeOps::ASTERIX;
            break;
        case Token::QUESTION_MARK:
            m_OpType = AstNodeOps::QUESTION_MARK;
            break;
        default:
            m_OpType = OpType::NONE;
            return false;
        }

        m_TokenPos++;
        return true;
    }

    void Syntax::printAst()
    {
        for (auto &node : m_AstTree)
        {
            std::cout << node->toString() << std::endl;
        }
    }
};