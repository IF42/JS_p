#ifndef _LEXER_H_
#define _LEXER_H_

#include <stddef.h>
#include <stdint.h>


typedef enum
{
    TokenType_Keyword
    , TokenType_Symbol
    , TokenType_Frac
    , TokenType_Int
    , TokenType_Char
    , TokenType_String
    , TokenType_Undefined
    , TokenType_EOF
}TokenType;


#define TOKEN_TYPE(T)                                   \
    T == TokenType_Keyword   ? "TokenType_Keyword":     \
    T == TokenType_Symbol    ? "TokenType_Symbol":      \
    T == TokenType_Frac      ? "TokenType_Frac":        \
    T == TokenType_Int       ? "TokenType_Int":         \
    T == TokenType_Char      ? "TokenType_Char":        \
    T == TokenType_String    ? "TokenType_String":      \
    T == TokenType_Undefined ? "TokenType_Undefined":   \
    T == TokenType_EOF       ? "TokenType_EOF":         \
                               "TokenType_Unknown"


typedef struct
{
    TokenType type;

    uint32_t row;
    uint32_t column;

    char * content;
    uint32_t start;
    uint32_t end;
}Token;


#define Token(...)(Token){__VA_ARGS__} 


#define token_strlen(T) \
   ((T)->end - (T)->start)


#define token_show(T)                                               \
    printf(                                                         \
        "Token {type: %s, content: \"%.*s\", start: %d, end: %d}\n" \
        , TOKEN_TYPE((T)->type)                                     \
        , token_strlen((T))                                         \
        , (T)->content                                              \
        , (T)->start                                                \
        , (T)->end)


typedef struct
{
    uint32_t index;
    uint32_t column;
    uint32_t row;
}LexerState;


typedef struct
{
    char * code;
    char * filename;

    uint32_t length;
    LexerState state;
}Lexer;


#define Lexer(filename, length, code) \
    (Lexer){code, filename, length, {0, 1, 1}}


Token
lexer_next_token(Lexer * self);


#endif



