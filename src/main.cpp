#include <iostream>
#include <iomanip>
#include "analysis/TokenKind.h"
#include "analysis/Token.h"
#include "analysis/SourceReader.h"
#include "analysis/Lexer.h"

const char *kindToStr(TokenKind k)
{
    switch (k)
    {
    case TokenKind::PAY:
        return "PAY";
    case TokenKind::YIELD:
        return "YIELD";
    case TokenKind::IMPORT:
        return "IMPORT";
    case TokenKind::VOL:
        return "VOL";
    case TokenKind::KEEP:
        return "KEEP";
    case TokenKind::CYCLE:
        return "CYCLE";
    case TokenKind::MINT:
        return "MINT";
    case TokenKind::IF:
        return "IF";
    case TokenKind::ELSE:
        return "ELSE";
    case TokenKind::KW_INT:
        return "KW_INT";
    case TokenKind::KW_FLOAT:
        return "KW_FLOAT";
    case TokenKind::KW_STRING:
        return "KW_STRING";
    case TokenKind::KW_BOOL:
        return "KW_BOOL";
    case TokenKind::LIT_INT:
        return "LIT_INT";
    case TokenKind::LIT_FLOAT:
        return "LIT_FLOAT";
    case TokenKind::LIT_STRING:
        return "LIT_STRING";
    case TokenKind::LIT_TRUE:
        return "LIT_TRUE";
    case TokenKind::LIT_FALSE:
        return "LIT_FALSE";
    case TokenKind::IDENTIFIER:
        return "IDENTIFIER";
    case TokenKind::PLUS:
        return "PLUS";
    case TokenKind::MINUS:
        return "MINUS";
    case TokenKind::STAR:
        return "STAR";
    case TokenKind::SLASH:
        return "SLASH";
    case TokenKind::PERCENT:
        return "PERCENT";
    case TokenKind::ASSIGN:
        return "ASSIGN";
    case TokenKind::EQUAL_EQUAL:
        return "EQUAL_EQUAL";
    case TokenKind::LESS:
        return "LESS";
    case TokenKind::GREATER:
        return "GREATER";
    case TokenKind::LESS_EQ:
        return "LESS_EQ";
    case TokenKind::GREATER_EQ:
        return "GREATER_EQ";
    case TokenKind::AND:
        return "AND";
    case TokenKind::OR:
        return "OR";
    case TokenKind::LBRACE:
        return "LBRACE";
    case TokenKind::RBRACE:
        return "RBRACE";
    case TokenKind::LPAREN:
        return "LPAREN";
    case TokenKind::RPAREN:
        return "RPAREN";
    case TokenKind::SEMICOLON:
        return "SEMICOLON";
    case TokenKind::COMMA:
        return "COMMA";
    case TokenKind::DOLLAR:
        return "DOLLAR";
    case TokenKind::END_OF_FILE:
        return "EOF";
    case TokenKind::ERROR:
        return "ERROR";
    default:
        return "UNKNOWN";
    }
}

int main()
{

    SourceReader reader("../src/programa.coin");
    Lexer lexer(reader);
    std::cout << std::left
              << std::setw(16) << "TIPO"
              << std::setw(22) << "LEXEMA"
              << std::setw(8) << "LINHA"
              << "COLUNA" << "\n";
    std::cout << std::string(54, '-') << "\n";

    int tokenCount = 0;
    while (true)
    {
        Token tok = lexer.nextToken();
        tokenCount++;

        std::cout << std::left
                  << std::setw(16) << kindToStr(tok.kind)
                  << std::setw(22) << ("'" + tok.lexeme + "'")
                  << std::setw(8) << tok.line
                  << tok.column << "\n";

        if (tok.is(TokenKind::END_OF_FILE))
            break;

        if (tok.is(TokenKind::ERROR))
        {
            std::cerr << "\n[ERRO LEXICO] linha " << tok.line
                      << ", coluna " << tok.column
                      << " — caractere inesperado: '"
                      << tok.lexeme << "'\n\n";
        }
    }

    std::cout << std::string(54, '-') << "\n";
    std::cout << tokenCount << " tokens lidos.\n";

    return 0;
}