#pragma once
#include <vector>
#include <string>
#include "../utils/font.h"

namespace Regex
{

    class AstNode
    {
    public:
        virtual std::string toString() = 0;
    };

    class AstNodeOps : public AstNode
    {
    public:
        enum OpType
        {
            PLUS,
            ASTERIX,
            NONE
        } m_OpType = NONE;

        std::string toOpString()
        {
            switch (m_OpType)
            {
            case PLUS:
                return "\x1B[35m+\x1B[0m";
            case ASTERIX:
                return "\x1B[35m*\x1B[0m";
            default:
                return "\x1B[35mX\x1B[0m";
            }
        }
    };

    class AstNodeParen : public AstNodeOps
    {
    public:
        std::vector<AstNodeOps *> ops;

        AstNodeParen(std::vector<AstNodeOps *> ops, OpType optype = OpType::NONE) : ops(ops)
        {
            m_OpType = optype;
        }

        ~AstNodeParen()
        {
            for (auto &op : ops)
            {
                delete op;
            }
        }

        std::string toString() override
        {
            std::string str = "AstOrNode<" + toOpString() + ">[";
            for (auto &op : ops)
            {
                str += op->toString() + ",";
            }
            str += "]";
            return str;
        }
    };

    class AstNodeEscape : public AstNodeOps
    {
    public:
        enum EscapeType
        {
            CHAR,
            BIG_CHAR,
            ANY_CHAR,
            DIGIT,
            NEWLINE
        } m_EscapeType;

        std::string toEscapeString()
        {
            switch (m_EscapeType)
            {
            case CHAR:
                return "\x1B[31mc\x1B[0m";
            case BIG_CHAR:
                return "\x1B[31mC\x1B[0m";
            case ANY_CHAR:
                return "\x1B[31mT\x1B[0m";
            case DIGIT:
                return "\x1B[31md\x1B[0m";
            case NEWLINE:
                return "\x1B[31mn\x1B[0m";
            default:
                return "\x1B[31mX\x1B[0m";
            }
        }

        AstNodeEscape(EscapeType escapeType, OpType optype = OpType::NONE) : m_EscapeType(escapeType)
        {
            m_OpType = optype;
        }

        std::string toString() override
        {
            return "EscapeNode<" + toOpString() + ">[" + toEscapeString() + "]";
        }
    };

    class AstNodeTxt : public AstNodeOps
    {
    public:
        std::string txt;
        AstNodeTxt(std::string txt, OpType optype = OpType::NONE) : txt(txt)
        {
            m_OpType = optype;
        }

        std::string toString() override
        {
            return "TxtNode<" + toOpString() + ">[\x1B[36m'" + txt + "'\x1B[0m]";
        }
    };
};