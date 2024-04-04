#pragma once
#include <string>
#include "../regex/regex.h"

namespace Input
{

    struct TokenMaper
    {
        std::string tokenName;
        Regex::Regex regex;
        bool ignore = false;
    };

    using TokenMap = std::vector<TokenMaper>;

    class FileParser
    {
        std::string m_FilePath;
        std::string m_FileContent;

        TokenMap tokenMaps;

    public:
        FileParser(const std::string &file_path);
        FileParser(const FileParser &other);
        FileParser(FileParser &&other) noexcept;

        bool parse();
        void print();

        inline TokenMap &getTokenMaps()
        {
            return tokenMaps;
        }
    };
};