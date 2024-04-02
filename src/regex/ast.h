#pragma once
#include <vector>
#include <string>

namespace Regex
{
    struct Match
    {
        bool matched = false;
        unsigned int current = 0;
    };

    class AstNodeOps
    {
    public:
        enum OpType
        {
            PLUS,
            ASTERIX,
            QUESTION_MARK,
            NONE
        } m_OpType = NONE;

        struct Location
        {
            int start;
            int end;
        } m_Location;

        AstNodeOps(Location location) : m_Location(location) {}

        virtual std::string toString() = 0;
        virtual unsigned int _match(std::string text, unsigned int start) = 0;
        virtual Match match(std::string text, unsigned int start) = 0;

        std::string toOpString()
        {
            switch (m_OpType)
            {
            case PLUS:
                return "\x1B[35m+\x1B[0m";
            case ASTERIX:
                return "\x1B[35m*\x1B[0m";
            case QUESTION_MARK:
                return "\x1B[35m?\x1B[0m";
            default:
                return "\x1B[35mX\x1B[0m";
            }
        }
    };

    class AstNodeParen : public AstNodeOps
    {
    public:
        std::vector<AstNodeOps *> m_Ops;

        AstNodeParen(Location loc, std::vector<AstNodeOps *> ops, OpType optype = OpType::NONE) : AstNodeOps(loc), m_Ops(ops)
        {
            m_OpType = optype;
        }

        ~AstNodeParen()
        {
            for (auto &op : m_Ops)
            {
                delete op;
            }
        }

        unsigned int _match(std::string text, unsigned int start) override;
        Match match(std::string text, unsigned int start) override;

        std::string toString() override
        {
            std::string str = "AstOrNode<" + toOpString() + ">[";
            for (auto &op : m_Ops)
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

        AstNodeEscape(Location loc, EscapeType escapeType, OpType optype = OpType::NONE) : AstNodeOps(loc), m_EscapeType(escapeType)
        {
            m_OpType = optype;
        }

        unsigned int _match(std::string text, unsigned int start) override;
        Match match(std::string text, unsigned int start) override;

        std::string toString() override
        {
            return "EscapeNode<" + toOpString() + ">[" + toEscapeString() + "]";
        }
    };

    class AstNodeTxt : public AstNodeOps
    {
    public:
        std::string txt;
        AstNodeTxt(Location loc, std::string txt, OpType optype = OpType::NONE) : AstNodeOps(loc), txt(txt)
        {
            m_OpType = optype;
        }

        unsigned int _match(std::string text, unsigned int start) override;
        Match match(std::string text, unsigned int start) override;

        std::string toString() override
        {
            return "TxtNode<" + toOpString() + ">[\x1B[36m'" + txt + "'\x1B[0m]";
        }
    };
};