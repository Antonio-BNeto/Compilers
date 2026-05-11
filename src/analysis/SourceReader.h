#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

class SourceReader
{
private:
    std::string source;
    size_t pos = 0;
    int line = 1;
    int column = 1;

public:
    explicit SourceReader(const std::string &filepath)
    {
        std::ifstream file(filepath);
        if (!file.is_open())
        {
            throw std::runtime_error("Não foi possível abrir o arquivo: " + filepath);
        }

        source = std::string(
            std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>());

        source.push_back('\0');
    }

    char peek() const
    {
        return source[pos];
    }

    char peekNext() const
    {
        if (pos + 1 < source.size())
            return source[pos + 1];
        return '\0';
    }

    char advance()
    {
        char c = source[pos++];
        if (c == '\n')
        {
            line++;
            column = 1;
        }
        else
        {
            column++;
        }
        return c;
    }

    bool isAtEndFile() const
    {
        return source[pos] == '\0';
    }

    int getLine() const { return line; }
    int getColumn() const { return column; }

    std::string slice(size_t start, size_t end) const
    {
        return source.substr(start, end - start);
    }

    size_t getPos() const { return pos; }
};
