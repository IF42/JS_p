#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"

typedef enum
{
    AST_Type_Module
}AST_Type;


typedef struct AST
{
    AST_Type type;

    const char * filename;
    
    Token * value;
    struct AST * attribute;

    struct AST * child;
}AST;



#endif
