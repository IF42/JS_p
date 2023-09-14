#include "lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>


#define lexer_ref(T) \
    &((T)->code[(T)->state.index])


#define lexer_char(T) \
    ((int) (T)->code[(T)->state.index])


#define lexer_eof(T) \
    ((T)->state.index >= (T)->length || lexer_char(T) == 0)


static int
lexer_peek(Lexer * self)
{
    if(lexer_char(self) == '\0')
        return '\0';
    else
        return self->code[self->state.index + 1];
}


static inline void 
lexer_advance(Lexer * self)
{
    if(lexer_char(self) == '\0')
        return;
    else if(lexer_char(self) == '\n')
    {
        self->state.row ++;
        self->state.column = 1;
    }
    else
        self->state.column ++;

    self->state.index++;
}
    

static inline void
lexer_skip_whitespace(Lexer * self)
{
    while(isspace(lexer_char(self)))
        lexer_advance(self);
}


static inline void
lexer_skip_line_comment(Lexer * self)
{
    while(lexer_eof(self) == false 
        && lexer_char(self) != '\n')
    {
        lexer_advance(self);
    }
}


static inline void
lexer_skip_block_comment(Lexer * self)
{
    while(lexer_eof(self) == false 
		&& lexer_char(self) != '*' 
		&& lexer_peek(self) != '/')
	{
        lexer_advance(self);
	}

    lexer_advance(self);
    lexer_advance(self);
}


/*
** TODO: treat excape sequences
*/
static inline Token
lexer_read_string(Lexer * self)
{
    lexer_advance(self);

    Token token = 
        Token(
            TokenType_String
            , self->state.row
            , self->state.column
            , lexer_ref(self)
            , self->state.index, 0);

    while(lexer_eof(self) == false 
        && lexer_char(self) != '"')
    {
        if(lexer_char(self) == '\\')
            lexer_advance(self);

        lexer_advance(self);
    }

    token.end = self->state.index;
    lexer_advance(self);

    return token;
}


static inline Token
lexer_read_number(Lexer * self)
{
    Token token = 
        Token(
            TokenType_Int
            , self->state.row
            , self->state.column
            , lexer_ref(self)
            , self->state.index, 0);

    while(isdigit(lexer_char(self)) 
        || lexer_char(self) == '.' 
        || tolower(lexer_char(self)) == 'e')
    {
        if(lexer_char(self) == '.' )
        {
            if(token.type == TokenType_Frac)
            {
                token.type = TokenType_Undefined;
                token.end  = self->state.index;

                return token;
            }
            else
                token.type = TokenType_Int;
        }
        if(tolower(lexer_char(self)) == 'e')
        {
            if(token.type == TokenType_Frac)
            {
                token.type = TokenType_Undefined;
                token.end  = self->state.index;

                return token;
            }
            else
                token.type = TokenType_Frac;
        }

        lexer_advance(self);
    }   

    token.end  = self->state.index;

    return token;
}


static inline bool
elem(
    char * array
    , char c)
{
    while(*array != 0)
    {
        if(*(++array) == c)
            return true;
    }

    return false;
}


static char symbol[] = "+-=<>{}[]().:\'\",";


static inline Token
lexer_read_keyword(Lexer * self)
{
    Token token = 
        Token(
            TokenType_Keyword
            , self->state.row
            , self->state.column
            , lexer_ref(self)
            , self->state.index, 0);

    while(lexer_eof(self) == false
            && isspace(lexer_char(self)) == false
            && elem(symbol, lexer_char(self)) == false)
    {
        lexer_advance(self);
    }

    token.end = self->state.index;

    return token;
}


static inline Token
lexer_read_symbol(Lexer * self)
{
    Token token = 
		Token(
            TokenType_Symbol
            , self->state.row
            , self->state.column
            , lexer_ref(self)
            , self->state.index, 0);

	lexer_advance(self);

	token.end = self->state.index;

    return token;
}


Token
lexer_next_token(Lexer * self)
{
    while(lexer_char(self) != 0)
    {
		if(isspace(lexer_char(self)))
        {
            lexer_skip_whitespace(self);
            continue;
        }
		else if(lexer_char(self) == '/' 
			&& lexer_peek(self) == '/')
		{
			lexer_skip_line_comment(self);
			continue;
		}	
		else if(lexer_char(self) == '/' 
			&& lexer_peek(self) == '*')
		{
			lexer_skip_block_comment(self);
			continue;
		}
		else if(lexer_char(self) == '"')
            return lexer_read_string(self);
        else if(isdigit(lexer_char(self)))
            return lexer_read_number(self);
        else if(lexer_char(self) == '{')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '}')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '[')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == ']')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '(')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == ')')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '<')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '>')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '=')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '.')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == ',')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == ':')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '+')
            return lexer_read_symbol(self);
        else if(lexer_char(self) == '-')
            return lexer_read_symbol(self);
        else 
            return lexer_read_keyword(self);
    }        

    return Token(TokenType_EOF
            , self->state.row
            , self->state.column
            , NULL
            , self->state.index
            , self->state.index);
}




