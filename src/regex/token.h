#pragma once
#include <string>

namespace Regex
{
    class Token
    {
    public:
        int startPos;
        int endPos;

        int i_value;
        std::string txt_value;

        enum Type
        {
            CHAR,
            BIG_CHAR,
            ANY_CHAR,
            DIGIT,
            NEWLINE,
            TXT,

            PLUS,
            ASTERIX,
            MINUS,
            OR,

            LBRACK,
            RBRACK,
            LPAREN,
            RPAREN,

            WHITE_SPACE,
            TAB,

        } type;

        Token(int startPos, int endPos, Type type)
        {
            this->startPos = startPos;
            this->endPos = endPos;
            this->type = type;
        }

        Token(int startPos, int endPos, Type type, int i_value)
        {
            this->startPos = startPos;
            this->endPos = endPos;
            this->type = type;
            this->i_value = i_value;
        }

        Token(int startPos, int endPos, Type type, std::string txt_value)
        {
            this->startPos = startPos;
            this->endPos = endPos;
            this->type = type;
            this->txt_value = txt_value;
        }

        std::string toString()
        {
            std::string type;
            switch (this->type)
            {
            case Token::CHAR:
                type = "CHAR";
                break;
            case Token::BIG_CHAR:
                type = "BIG_CHAR";
                break;
            case Token::DIGIT:
                type = "DIGIT";
                break;
            case Token::NEWLINE:
                type = "NEWLINE";
                break;
            case Token::TXT:
                type = "TXT";
                break;
            case Token::PLUS:
                type = "PLUS";
                break;
            case Token::ASTERIX:
                type = "ASTERIX";
                break;
            case Token::MINUS:
                type = "MINUS";
                break;
            case Token::LBRACK:
                type = "LBRACK";
                break;
            case Token::RBRACK:
                type = "RBRACK";
                break;
            case Token::LPAREN:
                type = "LPAREN";
                break;
            case Token::RPAREN:
                type = "RPAREN";
                break;
            case Token::WHITE_SPACE:
                type = "WHITE_SPACE";
                break;
            case Token::TAB:
                type = "TAB";
                break;
            case Token::OR:
                type = "OR";
                break;
            default:
                type = "UNKNOWN";
                break;
            }

            // return type;
            if (this->type == Token::TXT)
                return type + "<" + txt_value + ">";

            return type;
        }
    };

};