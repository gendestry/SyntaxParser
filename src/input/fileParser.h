#pragma once
#include <string>

namespace Input
{
    class FileParser
    {
        std::string m_FilePath;
        std::string m_FileContent;

    public:
        FileParser(std::string file_path);
        FileParser(const FileParser &other);
        FileParser(FileParser &&other) noexcept;

        bool parse();
        void print();
    };
};