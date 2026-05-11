#pragma once
#include <string>
#include <unordered_map>
#include "Token.h"
#include "TokenKind.h"
#include "SourceReader.h"

class Lexer
{
private:
    static bool isAlpha(char c)
    {
        return (c >= 'a' && c <= 'z') ||
               (c >= 'A' && c <= 'Z') ||
               c == '_';
    }

    static bool isDigit(char c)
    {
        return (c >= '0' && c <= '9');
    }

    static bool isAlphaNumeric(char c)
    {
        return isAlpha(c) || isDigit(c);
    }

    Token makeToken(TokenKind kind, const std::string &lexeme)
    {
        return Token(kind, lexeme, reader.getLine(), reader.getColumn());
    }

    SourceReader reader;

    std::unordered_map<std::string, TokenKind> keywords;

    void initKeywords()
    {
        // Palavras-chave da linguagem Coin
        keywords["pay"] = TokenKind::PAY;
        keywords["yield"] = TokenKind::YIELD;
        keywords["import"] = TokenKind::IMPORT;
        keywords["vol"] = TokenKind::VOL;
        keywords["keep"] = TokenKind::KEEP;
        keywords["cycle"] = TokenKind::CYCLE;
        keywords["mint"] = TokenKind::MINT;
        keywords["if"] = TokenKind::IF;
        keywords["else"] = TokenKind::ELSE;

        // Tipos
        keywords["int"] = TokenKind::KW_INT;
        keywords["float"] = TokenKind::KW_FLOAT;
        keywords["string"] = TokenKind::KW_STRING;
        keywords["bool"] = TokenKind::KW_BOOL;

        // Operadores lógicos
        keywords["and"] = TokenKind::AND;
        keywords["or"] = TokenKind::OR;

        // Literais booleanos
        keywords["true"] = TokenKind::LIT_TRUE;
        keywords["false"] = TokenKind::LIT_FALSE;
    }

    Token scanIdentifierOrKeyword(char first, int line, int col)
    {
        std::string lexeme(1, first);

        while (isAlphaNumeric(reader.peek()))
        {
            lexeme += reader.advance();
        }

        auto it = keywords.find(lexeme);
        if (it != keywords.end())
        {
            return Token(it->second, lexeme, line, col);
        }

        return Token(TokenKind::IDENTIFIER, lexeme, line, col);
    }

    Token scanNumber(char first, int line, int col)
    {
        std::string lexeme(1, first);

        while (isDigit(reader.peek()))
        {
            lexeme += reader.advance();
        }

        if (reader.peek() == '.' && isDigit(reader.peekNext()))
        {
            lexeme += reader.advance();
            while (isDigit(reader.peek()))
            {
                lexeme += reader.advance();
            }
            return Token(TokenKind::LIT_FLOAT, lexeme, line, col);
        }

        return Token(TokenKind::LIT_INT, lexeme, line, col);
    }

    Token scanString(int line, int col)
    {
        std::string lexeme;

        while (!reader.isAtEndFile() && reader.peek() != '"')
        {
            if (reader.peek() == '\\')
            {
                reader.advance();
                char esc = reader.advance();
                switch (esc)
                {
                case 'n':
                    lexeme += '\n';
                    break;
                case 't':
                    lexeme += '\t';
                    break;
                case '"':
                    lexeme += '"';
                    break;
                case '\\':
                    lexeme += '\\';
                    break;
                default:
                    lexeme += esc;
                }
            }
            else if (reader.peek() == '\n')
            {
                return Token(TokenKind::ERROR,
                             "Não existe um token para essa string", line, col);
            }
            else
            {
                lexeme += reader.advance();
            }
        }

        if (reader.isAtEndFile())
        {
            Token(TokenKind::ERROR,
                  "Não existe um token para essa string", line, col);
        }

        reader.advance();
        return Token(TokenKind::LIT_STRING, lexeme, line, col);
    }

    void skipWhitespaceAndComments()
    {
        while (!reader.isAtEndFile())
        {
            char c = reader.peek();

            if (c == ' ' || c == '\t' || c == '\r' || c == '\n')
            {
                reader.advance();
                continue;
            }

            if (c == '/' && reader.peekNext() == '/')
            {
                while (!reader.isAtEndFile() && reader.peek() != '\n')
                {
                    reader.advance();
                }
                continue;
            }
            break;
        }
    }

public:
    explicit Lexer(SourceReader reader)
        : reader(std::move(reader))
    {
        initKeywords();
    }

    Token nextToken()
    {
        skipWhitespaceAndComments();

        if (reader.isAtEndFile())
        {
            return makeToken(TokenKind::END_OF_FILE, "");
        }

        int startLine = reader.getLine();
        int startCol = reader.getColumn();
        size_t startPos = reader.getPos();

        char c = reader.advance();

        if (isAlpha(c))
        {
            return scanIdentifierOrKeyword(c, startLine, startCol);
        }

        if (c == '"')
        {
            return scanString(startLine, startCol);
        }

        if (c == '$')
        {
            return Token(TokenKind::DOLLAR, "$", startLine, startCol);
        }

        switch (c)
        {
        case '+':
            return Token(TokenKind::PLUS, "+", startLine, startCol);
        case '-':
            return Token(TokenKind::MINUS, "-", startLine, startCol);
        case '*':
            return Token(TokenKind::STAR, "*", startLine, startCol);
        case '/':
            return Token(TokenKind::SLASH, "/", startLine, startCol);
        case '%':
            return Token(TokenKind::PERCENT, "%", startLine, startCol);

        case '=':
            if (reader.peek() == '=')
            {
                reader.advance();
                return Token(TokenKind::EQUAL_EQUAL, "==", startLine, startCol);
            }
            return Token(TokenKind::ASSIGN, "=", startLine, startCol);

        case '<':
            if (reader.peek() == '=')
            {
                reader.advance();
                return Token(TokenKind::LESS_EQ, "<=", startLine, startCol);
            }
            return Token(TokenKind::LESS, "<", startLine, startCol);

        case '>':
            if (reader.peek() == '=')
            {
                reader.advance();
                return Token(TokenKind::GREATER_EQ, ">=", startLine, startCol);
            }
            return Token(TokenKind::GREATER, ">", startLine, startCol);

        case '{':
            return Token(TokenKind::LBRACE, "{", startLine, startCol);
        case '}':
            return Token(TokenKind::RBRACE, "}", startLine, startCol);
        case '(':
            return Token(TokenKind::LPAREN, "(", startLine, startCol);
        case ')':
            return Token(TokenKind::RPAREN, ")", startLine, startCol);
        case ';':
            return Token(TokenKind::SEMICOLON, ";", startLine, startCol);
        case ',':
            return Token(TokenKind::COMMA, ",", startLine, startCol);

        default:
            return Token(TokenKind::ERROR,
                         std::string(1, c), startLine, startCol);
        }
    }
};
