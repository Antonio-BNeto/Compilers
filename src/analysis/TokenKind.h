#pragma once

enum class TokenKind
{
    PAY,    // print
    YIELD,  // return
    IMPORT, // import
    VOL,    // variable
    KEEP,   // while
    CYCLE,  // for
    MINT,   // function declaration

    IF,
    ELSE,

    KW_INT,
    KW_FLOAT,
    KW_STRING,
    KW_BOOL,

    LIT_INT,    // ex: 42
    LIT_FLOAT,  // ex: 3.14
    LIT_STRING, // ex: "hello"
    LIT_TRUE,   // true
    LIT_FALSE,  // false

    IDENTIFIER, // ID

    PLUS,    // +
    MINUS,   // -
    STAR,    // *
    SLASH,   // /
    PERCENT, // %

    ASSIGN,      // =
    EQUAL_EQUAL, // ==
    LESS,        // <
    GREATER,     // >
    LESS_EQ,     // <=
    GREATER_EQ,  // >=

    AND, // and
    OR,  // or

    LBRACE,    // {
    RBRACE,    // }
    LPAREN,    // (
    RPAREN,    // )
    SEMICOLON, // ;
    COMMA,     // ,
    DOLLAR,    // $

    END_OF_FILE, // fim do arquivo
    ERROR        // caractere inválido

};

const char *tokenKindToString(TokenKind kind);