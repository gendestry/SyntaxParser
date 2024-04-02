#include "fileParser.h"
#include <fstream>

namespace Input
{
    FileParser::FileParser(std::string file_path) : m_FilePath(file_path)
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
        std::string line;
        // Parse the file content
    }

    void FileParser::print()
    {
        // Print the file content
    }
};