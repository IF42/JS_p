#include "parser.h"

#include <stdio.h>
#include <stdlib.h>



const char * data_type[] = 
{
    "int"
    , "uint"
    , "int8"
    , "int16"
    , "int32"
    , "int64"
    , "uint8"
    , "uint16"
    , "uint32"
    , "uint32"
    , "uint64"
    , "char"
    , "float"
    , "double"
};





static AST_Variable *
parse_variable(Parser * self)
{
   
}


static AST_Statement *
parse_statement(Parser * self)
{
    LexerState store        = self->lexer.state;

    AST_Variable * variable = parse_variable(self);

    if(variable != NULL)
    {
        AST_Statement * statement = malloc(sizeof(AST_Statement));
    
        if(statement != NULL)
        {
            *statement = (AST_Statement)
            {
                .type       = AST_Statement_Type_Variable
                , .variable = variable
                , .next     = parse_statement(self)
            };
        }

        return statement;
    }

    // TODO: parse next type of statements
    
    return NULL;    
}


static AST_Module *
parser_parse_module(Parser * self)
{
    AST_Module * module = malloc(sizeof(AST_Module));

    if(module != NULL)
    {
        *module = (AST_Module)
        {
            .name = self->lexer.filename
            , .statement = parse_statement(self)
        };
    }

    return module;
}


AST_Module * 
parser_rapse_file(char * filename)
{
    FILE * file = fopen(filename, "r");

    if(file == NULL)
    {
        fprintf(stderr, "Can't load file: %s\n", filename);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET); 

    char * content = malloc(sizeof(char)*length);

    Parser parser = 
        Parser(Lexer(filename, length, content));

    AST_Module * module = parser_parse_module(&parser);

    free(content);
    fclose(file);

    return module;
}



