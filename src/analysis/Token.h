#pragma once
#include <string>
#include <variant>
#include "TokenKind.h"

struct Token
{
    TokenKind kind;
    std::string lexeme;
    int line;
    int column;

    Token(TokenKind kind, std::string lexeme, int line, int col)
        : kind(kind), lexeme(std::move(lexeme)), line(line), column(col) {}

    Token() : kind(TokenKind::ERROR), line(0), column(0) {}

    bool is(TokenKind k) const { return kind == k; }

    template <typename... Kinds>
    bool isAny(Kinds... kinds) const
    {
        return ((kind == kinds) || ...);
    }
};