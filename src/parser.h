#ifndef _PARSER_H_
#define _PARSER_H_

#include "lexer.h"

#include <stdbool.h>


typedef enum
{
    AST_Type_Module
}AST_Type;


#define AST_TYPE(T)                                 \
    T == AST_Type_Module ? "AST_Type_Module" :      \
                            "AST_Type_Unknown"


typedef struct AST_Expression
{
    struct AST_Expression * next;
}AST_Expression;


typedef struct
{
    char * type;
    char * name;
    bool constant;

    AST_Expression * expression;
}AST_Variable;


typedef struct AST_Module AST_Module;


typedef struct
{
    AST_Module * import_module;
    char * alias;
}AST_Import;


typedef enum
{
    AST_Statement_Type_Import
    , AST_Statement_Type_Variable
}AST_Statement_Type;


typedef struct AST_Statement
{
    AST_Statement_Type type;

    union
    {
        AST_Import * module_import;
        AST_Variable * variable;
    };

    struct AST_Statement * next;
}AST_Statement;


struct AST_Module
{
    char * name;
    AST_Statement * statement;
};


typedef struct
{
    Lexer lexer;
}Parser;


#define Parser(...)(Parser){__VA_ARGS__}


AST_Module * 
parser_rapse_file(char * filename);



#endif
