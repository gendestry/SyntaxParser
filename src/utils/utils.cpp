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
};
