#include "syntaxParser.h"
#include <fstream>
#include <iostream>
#include <utility>
#include <iterator>

#include "../utils/font.h"
#include "../utils/utils.h"
#include "../utils/lineCounter.h"
#include "rule.h"

using Utils::Font;
using Utils::StringVec;

namespace Parsing
{
    SyntaxParser::SyntaxParser(std::string syntaxPath, const Tokens &tokens)
        : m_SyntaxPath(syntaxPath), m_Tokens(tokens)
    {
    }

    SyntaxParser::~SyntaxParser()
    {
    }

    /*
        // -- private

        void SyntaxParser::parseSyntaxFile()
        {
            auto splitBySymbol = [](StringVec &input, std::string str)
                -> std::pair<StringVec, StringVec>
            {
                for (auto it = input.begin(); it != input.end(); it++)
                {
                    if (*it == str)
                    {
                        StringVec patterns(input.begin(), it);
                        StringVec tokens(it + 1, input.end());
                        return {patterns, tokens};
                    }
                }

                return {};
            };

            auto fixSpecialCharacters = [](StringVec &tokens)
            {
                const std::vector<char> specialChars = {'|', '*', '+', '?', '(', ')', '[', ']', '{', '}'};

                for (unsigned int i = 0; i < tokens.size(); i++)
                {
                    std::string &token = tokens[i];

                    if (token.size() == 1)
                        continue;

                    for (unsigned int j = 0; j < token.size(); j++)
                    {
                        char c = token[j];
                        // if (c == '#')
                        // {
                        //     std::cout << "Warning: Found comment character in token: " << token << std::endl;
                        //     std::cout << "Removing comment character from token: " << token << std::endl;

                        //     std::string first = token.substr(0, j);
                        //     std::string second = token.substr(j + 1);
                        //     // print
                        //     std::cout << "First: " << first << std::endl;
                        //     std::cout << "Second: " << second << std::endl;
                        //     return;
                        //     // tokens.insert(tokens.begin() + i, token.substr(0, j));
                        //     // tokens.insert(tokens.begin() + i + 1, token.substr(j + 1));

                        //     token = token.erase(j, 1);

                        //     break;
                        // }
                        for (auto special : specialChars)
                        {
                            if (c == special)
                            {
                                std::cout << "Found special character: " << token << ": " << j << std::endl;

                                std::string first = token.substr(0, j);
                                std::string second = token.substr(j + 1);
                                // print
                                std::cout << "First: " << first << std::endl;
                                std::cout << "Second: " << second << std::endl;
                                tokens.insert(tokens.begin() + i, token.substr(0, j));
                                tokens.insert(tokens.begin() + i, token.substr(j, 1));
                                if (j + 1 < token.size())
                                    tokens.insert(tokens.begin() + i + 1, token.substr(j + 1));
                                tokens.erase(tokens.begin() + i + 2);

                                // if (j == 0)
                                // {
                                //     std::string first = token.substr(0, j);
                                //     std::string second = token.substr(j + 1);

                                //     tokens.insert(tokens.begin() + i, first);
                                //     tokens.insert(tokens.begin() + i + 1, second);
                                // }
                                break;
                            }
                        }
                    }
                }
            };

            std::string input = Utils::getFileString(m_SyntaxPath);
            input = Utils::removeNewline(input);

            StringVec splitLines = Utils::split(input, ";");
            for (auto &line : splitLines)
            {
                StringVec whitespace = Utils::splitByWhitespace(line);
                fixSpecialCharacters(whitespace);
                auto [name, tokens] = splitBySymbol(whitespace, "=");

                if (name.empty() || name[0].empty() || tokens.empty())
                    continue;

                // TODO: watch out for null!
                std::cout << Font::fyellow << "'" << name[0] << "'" << Font::reset << " = ";
                for (auto token : tokens)
                {
                    std::cout << Font::fblue << "[" << token << "]" << Font::reset << " ";
                }
                std::cout << std::endl;
            }

            // unsigned int prevPos = 0;
            // for (unsigned int i = 0; i < input.size(); i++)
            // {
            //     if (input[i] == '#')
            //     {
            //         while (input[i] != '\n')
            //             i++;
            //         prevPos = i;
            //     }
            //     else if (input[i] == ';')
            //         else if (input[i] == '\n')
            //         {
            //             continue;
            //         }
            // else
            // {
            //     std::string name;
            //     StringVec tokens;

            //     while (input[i] != '=')
            //     {
            //         name += input[i];
            //         i++;
            //     }

            //     i++;

            //     while (input[i] == ' ')
            //         i++;

            //     while (input[i] != '\n')
            //     {
            //         std::string token;
            //         while (input[i] != ' ' && input[i] != '\n')
            //         {
            //             token += input[i];
            //             i++;
            //         }
            //         tokens.push_back(token);
            //         i++;
            //     }

            //     m_ParsedLines.push_back({name, tokens});
            // }
            // }
            // StringVec lines = Utils::getFileStringVec(m_SyntaxPath);

            // for (auto &line : lines)
            // {
            //     bool ignore = false;

            //     if (line[0] == '#' || line.empty())
            //         continue;

            //     size_t namePos = line.find_first_of("= ");
            //     std::string name = line.substr(0, namePos);

            //     size_t patternPos = line.find_first_of("= ", namePos + 1);
            //     while (line[patternPos] == ' ' || line[patternPos] == '=')
            //         patternPos++;
            //     std::string pattern = line.substr(patternPos);

            //     auto patternTokens = Utils::splitByWhitespace(pattern);
            //     m_ParsedLines.push_back({name, patternTokens});
            // }
        }
    */

    // public

    void SyntaxParser::parseFileInput(std::string inputFilePath)
    {
        try
        {
            m_Input = Utils::getFileString(inputFilePath);
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            return;
        }
    }

    bool SyntaxParser::parseSyntax()
    {
        std::string syntaxStr = Utils::getFileString(m_SyntaxPath);
        if (syntaxStr.size() < 2)
            return false;

        // check if we have trailing ';;'
        {
            std::string testStr = Utils::removeWhitespaces(syntaxStr);
            size_t size = testStr.size();

            // print teststr and size
            if (testStr[size - 1] != ';' && testStr[size - 2] != ';')
            {
                std::cout << Font::fred << "Error: Syntax file does not end with a semicolon" << Font::reset << std::endl;
                std::cout << Font::fred << "Syntax: '" << testStr << "'" << Font::reset << std::endl;
                return false;
            }
        }

        StringVec rules = Utils::split(syntaxStr, ";;");
        Utils::LineCounter counter(syntaxStr);

        // print rules
        unsigned int lineIndex = 0;
        for (auto &rule : rules)
        {
            if (rule.empty() || Utils::removeWhitespaces(rule).empty())
                continue;

            int res = parseSyntaxRule(rule);
            if (res == 1)
            {
                std::cout << Font::fred << "Error[" << (counter[lineIndex] + 2) << "]: Rule is not in the correct format: '" << rule << "'" << Font::reset << std::endl;
                return false;
            }
            else if (res == 2)
            {
                return false;
            }

            lineIndex += rule.size();
        }
        return true;
    }

    int SyntaxParser::parseSyntaxRule(const std::string &rule)
    {
        std::string rulePart = Utils::replaceNewlineBySpace(rule);
        std::string rulePartSanitized = Utils::removeEnclosingWhitespaces(Utils::sanitizeWhitespace(rulePart));

        std::cout << Font::italic << Font::byColorCode(90, 90, 90) << "[" << rulePartSanitized << "]" << Font::reset << std::endl;

        StringVec nameAndRule = Utils::split(rulePartSanitized, "->");
        if (nameAndRule.size() != 2)
        {
            return 1;
        }

        std::string left = Utils::removeEnclosingWhitespaces(nameAndRule[0]);
        std::string right = Utils::removeEnclosingWhitespaces(nameAndRule[1]);

        Rule ruleObj(left, right);

        if (m_RuleNameToVec.find(ruleObj.m_Name) == m_RuleNameToVec.end())
        {
            m_Rules.push_back(ruleObj);
            m_RuleNameToVec.insert(std::make_pair(ruleObj.m_Name, m_Rules.size() - 1));
        }
        else
        {
            std::cout << Font::fred << "Rule: '" << ruleObj.m_Name << "' already exists!" << Font::reset << std::endl;
            return 2;
        }

        return 0;
    }

    // print

    void SyntaxParser::printRules()
    {
        // print size
        std::cout << "\n"
                  << Font::fgreen << " ==== PARSED SYNTAX ==== \n"
                  << Font::reset;
        for (auto &rule : m_Rules)
        {
            rule.print();
        }
    }

    void SyntaxParser::printSyntax()
    {
    }
}
