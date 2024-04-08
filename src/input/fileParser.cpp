#include "fileParser.h"
#include <fstream>
#include <iostream>

#include "../utils/font.h"

using Utils::Font;

namespace Input
{
    FileParser::FileParser(const std::string &file_path) : m_FilePath(file_path)
    {
    }

    FileParser::FileParser(const FileParser &other)
        : m_FilePath(other.m_FilePath),
          m_FileContent(other.m_FileContent)
    {
    }

    FileParser::FileParser(FileParser &&other) noexcept
        : m_FilePath(std::move(other.m_FilePath)),
          m_FileContent(std::move(other.m_FileContent))
    {
    }

    bool FileParser::parse()
    {
        std::ifstream file(m_FilePath);

        if (!file.is_open())
        {
            throw std::runtime_error("Error: file '" + m_FilePath + "' not found");
            return false;
        }

        std::string line;

        while (std::getline(file, line))
        {
            bool ignore = false;

            if (line[0] == '#' || line.empty())
                continue;

            if (line[0] == '!')
            {
                ignore = true;
                line = line.substr(1);
            }

            size_t namePos = line.find_first_of("= ");
            std::string name = line.substr(0, namePos);

            size_t patternPos = line.find_first_of("= ", namePos + 1);
            while (line[patternPos] == ' ' || line[patternPos] == '=')
                patternPos++;
            std::string pattern = line.substr(patternPos);

            tokenMaps.push_back({name, Regex::Regex(pattern), ignore});
        }
        return false;
        // Parse the file content
    }

    void FileParser::print()
    {
        std::cout << Font::bold << Font::fgreen << " ==== INPUT TOKENS ==== " << Font::reset << std::endl;
        for (auto &token : tokenMaps)
        {
            std::cout << Font::fyellow << "'" << token.tokenName << "'" << Font::reset << ": "
                      << Font::fcyan << token.regex.getPattern() << Font::reset;

            if (token.ignore)
                std::cout << Font::fred << " [IGNORED]" << Font::reset;

            std::cout << std::endl;
        }
    }
};