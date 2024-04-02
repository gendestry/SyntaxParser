#include "ast.h"

namespace Regex
{
    unsigned int AstNodeParen::_match(std::string text, unsigned int start)
    {
        for (auto &op : m_Ops)
        {
            auto [matched, current] = op->match(text, start);
            if (matched)
                return current;
        }

        return start;
    }

    Match AstNodeParen::match(std::string text, unsigned int start)
    {
        if (start >= text.size())
            return {false, start};

        unsigned int s = start;
        unsigned int m = _match(text, start);

        switch (m_OpType)
        {
        case NONE:
            return {m != s, m};
        case PLUS:
            if (m != s)
            {
                s = m;
                m = _match(text, s);

                while (m != s)
                {
                    s = m;
                    m = _match(text, s);
                }

                return {true, m};
            }

            return {false, s};
        case ASTERIX:
            while (m != s)
            {
                s = m;
                m = _match(text, s);
            }

            return {true, m};
        case QUESTION_MARK:
            return {true, m};
        }

        return {false, s};
    }

    unsigned int AstNodeEscape::_match(std::string text, unsigned int start)
    {
        if (start >= text.size())
            return start;

        auto checkSmallChar = [](char c) -> bool
        { return c >= 'a' && c <= 'z'; };

        auto checkBigChar = [](char c) -> bool
        { return c >= 'A' && c <= 'Z'; };

        auto checkDigit = [](char c) -> bool
        { return c >= '0' && c <= '9'; };

        switch (m_EscapeType)
        {
        case CHAR:
            if (checkSmallChar(text[start]))
            {
                return start + 1;
            }
        case BIG_CHAR:
            if (checkBigChar(text[start]))
            {
                return start + 1;
            }
        case ANY_CHAR:
            if (checkSmallChar(text[start]) || checkBigChar(text[start]))
            {
                return start + 1;
            }
        case DIGIT:
            if (checkDigit(text[start]))
            {
                return start + 1;
            }
        case NEWLINE:
            if (text[start] == '\n')
            {
                return start + 1;
            }
        }

        return start;
    }

    Match AstNodeEscape::match(std::string text, unsigned int start)
    {
        if (start >= text.size())
            return {false, start};

        unsigned int s = start;
        unsigned int m = _match(text, start);

        switch (m_OpType)
        {
        case NONE:
            return {m != s, m};
        case PLUS:
            if (m != s)
            {
                s = m;
                m = _match(text, s);

                while (m != s)
                {
                    s = m;
                    m = _match(text, s);
                }

                return {true, m};
            }

            return {false, s};
        case ASTERIX:
            while (m != s)
            {
                s = m;
                m = _match(text, s);
            }

            return {true, m};
        case QUESTION_MARK:
            return {true, m};
        }

        return {false, s};
    }

    unsigned int AstNodeTxt::_match(std::string text, unsigned int start)
    {
        if (start >= text.size() || start + txt.size() > text.size())
            return start;

        if (text.substr(start, txt.size()) == txt)
            return start + txt.size();

        return start;
    }

    Match AstNodeTxt::match(std::string text, unsigned int start)
    {
        if (start >= text.size() || start + txt.size() > text.size())
            return {false, start};

        unsigned int s = start;
        unsigned int m = _match(text, start);

        switch (m_OpType)
        {
        case NONE:
            return {m != s, m};
        case PLUS:
            if (m != s)
            {
                s = m;
                m = _match(text, s);

                while (m != s)
                {
                    s = m;
                    m = _match(text, s);
                }

                return {true, m};
            }

            return {false, s};
        case ASTERIX:
            while (m != s)
            {
                s = m;
                m = _match(text, s);
            }

            return {true, m};
        case QUESTION_MARK:
            return {true, m};
        }

        return {false, s};
    }
};