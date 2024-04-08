#include "utils.h"
#include <fstream>

namespace Utils
{
    std::string getFileString(std::string path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::runtime_error("Error: file '" + path + "' not found");
            return "";
        }

        std::string content((std::istreambuf_iterator<char>(file)),
                            (std::istreambuf_iterator<char>()));

        file.close();
        return content;
    }

    std::vector<std::string> getFileStringVec(std::string path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            throw std::runtime_error("Error: file '" + path + "' not found");
            return {};
        }

        std::vector<std::string> content;
        std::string line;

        while (std::getline(file, line))
        {
            content.push_back(line);
        }

        file.close();
        return content;
    }

    std::string sanitizeString(const std::string &str)
    {
        std::string sanitized = str;

        size_t p = 0;
        while ((p = sanitized.find('\n', p)) != std::string::npos)
        {
            sanitized.replace(p, 1, "\\n");
            p += 2; // Move past the inserted "\\n"
        }

        return sanitized;
    }

    std::vector<std::string> split(const std::string &str, const std::string &delim)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;

        do
        {
            pos = str.find(delim, prev);
            if (pos == std::string::npos)
                pos = str.length();

            std::string token = str.substr(prev, pos - prev);
            if (!token.empty())
                tokens.push_back(token);

            prev = pos + delim.length();
        } while (pos < str.length() && prev < str.length());

        return tokens;
    }

    std::vector<std::string> splitByWhitespace(const std::string &str)
    {
        std::vector<std::string> tokens;
        size_t prev = 0, pos = 0;

        do
        {
            pos = str.find_first_of(" \t", prev);
            if (pos == std::string::npos)
                pos = str.length();

            std::string token = str.substr(prev, pos - prev);
            if (!token.empty())
                tokens.push_back(token);

            prev = pos + 1;
        } while (pos < str.length() && prev < str.length());

        return tokens;
    }
};
