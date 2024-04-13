#pragma once
#include <vector>
#include <string>

namespace Utils
{
    class LineCounter
    {
        // positions of newlines in 1d

    public:
        std::vector<unsigned int> lines;

        // input = string with newlines so the whole file in a string lets say
        LineCounter(const std::string &input);

        // returns the number of new lines (accumulated) at index
        unsigned int accumulate(unsigned int index, unsigned int accOffset = 1);
        unsigned int operator[](unsigned int index);
        unsigned int getXOffset(unsigned int index);
        unsigned int numLinesInBetween(unsigned int start, unsigned int end);

        inline std::vector<unsigned int> getLines() const
        {
            return lines;
        }

    private:
    };
};