#pragma once
#include <vector>
#include "token.h"
#include "ast.h"

namespace Regex
{
    using TokenArray = std::vector<Regex::Token>;
    using Pos = unsigned int;

    class Syntax
    {
    private:
        Pos m_TokenPos = 0;
        const TokenArray &m_Tokens;
        std::vector<AstNode *> m_AstTree;

    public:
        Syntax(const TokenArray &tokens) : m_Tokens(tokens)
        {
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
        bool isOps();

        bool isEscapeOp();
        bool isTxtOp();

        bool isEscape();
        bool isOperator();
    };
};