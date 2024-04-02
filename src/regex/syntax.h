#pragma once
#include <vector>
#include "token.h"
#include "ast.h"

namespace Regex
{
    using TokenArray = std::vector<Regex::Token>;
    using OpType = AstNodeOps::OpType;
    using EscapeType = AstNodeEscape::EscapeType;
    using Pos = unsigned int;

    class Syntax
    {
    private:
        Pos m_TokenPos = 0;
        const TokenArray &m_Tokens;

        std::vector<AstNodeOps *> m_AstTree;

        AstNodeOps *m_Op;
        OpType m_OpType = OpType::NONE;
        EscapeType m_EscapeType = EscapeType::CHAR;

    public:
        Syntax(const TokenArray &tokens) : m_Tokens(tokens)
        {
        }

        ~Syntax()
        {
            for (auto &node : m_AstTree)
            {
                delete node;
            }
        }

        bool parse()
        {
            if (isInter())
            {
                while (isInter())
                    ;
                return true;
            }

            return false;
        }

        bool isInter();

        bool isParen();
        bool isEscapeOp();
        bool isTxtOp();

        bool isEscape();
        bool isOperator();

        void printAst();
    };
};