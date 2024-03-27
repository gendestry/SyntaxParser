#pragma once
#include <vector>
#include <string>

namespace Regex
{

    class AstNode
    {
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
    };

    class AstNodeParen : public AstNodeOps
    {
    public:
        std::vector<AstNodeOps *> ops;

        AstNodeParen(std::vector<AstNodeOps *> ops, OpType optype = NONE) : ops(ops)
        {
            m_OpType = optype;
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

        AstNodeEscape(EscapeType escapeType, OpType optype = NONE) : m_EscapeType(escapeType)
        {
            m_OpType = optype;
        }
    };
    class AstNodeTxt : public AstNodeOps
    {
    public:
        std::string txt;
        AstNodeTxt(std::string txt, OpType optype = NONE) : txt(txt)
        {
            m_OpType = optype;
        }
    };

};