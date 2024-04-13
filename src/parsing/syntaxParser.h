#pragma once

#include <string>
#include <unordered_map>
#include "rule.h"
#include "token.h"

namespace Parsing
{

    class SyntaxParser
    {
        std::string m_SyntaxPath;
        std::string m_Input;
        Tokens m_Tokens;

        std::vector<Rule> m_Rules;
        std::unordered_map<std::string, unsigned int> m_RuleNameToVec;

    public:
        SyntaxParser(std::string syntaxPath, const Tokens &tokens);
        ~SyntaxParser();

        void parseFileInput(std::string inputFilePath);

        // goes through the syntax file and looks for ';;'
        // it splits by ';;' and then goes through each rule
        bool parseSyntax();

        // parses a single rule
        int parseSyntaxRule(const std::string &rule);

        void printRules();
        void printSyntax();

    private:
        // void parseSyntaxFile();
    };

}
