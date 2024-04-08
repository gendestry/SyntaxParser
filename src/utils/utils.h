#pragma once
#include <string>
#include <vector>

namespace Utils
{
    std::string getFileString(std::string path);
    std::vector<std::string> getFileStringVec(std::string path);
    std::string sanitizeString(const std::string &str);

    std::vector<std::string> split(const std::string &str, const std::string &delim);
    std::vector<std::string> splitByWhitespace(const std::string &str);
};
