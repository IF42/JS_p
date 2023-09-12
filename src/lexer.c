#include "lexer.h"

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>


#define __lexer_ref(T) \
    &((T)->code[(T)->state.index])


#define __lexer_char(T) \
    ((int) (T)->code[(T)->state.index])


#define __lexer_eof(T) \
    ((T)->state.index >= (T)->length || __lexer_char(T) == 0)


static int
__lexer_peek(Lexer * self)
{
    if(__lexer_char(self) == '\0')
        return '\0';
    else
        return self->code[self->state.index + 1];
}


static inline void 
__lexer_advance(Lexer * self)
{
    if(__lexer_char(self) == '\0')
        return;
    else if(__lexer_char(self) == '\n')
    {
        self->state.row ++;
        self->state.column = 1;
    }
    else
        self->state.column ++;

    self->state.index++;
}
    

static inline void
__lexer_skip_whitespace(Lexer * self)
{
    while(isspace(__lexer_char(self)))
        __lexer_advance(self);
}


static inline void
__lexer_skip_line_comment(Lexer * self)
{
    while(__lexer_eof(self) == false && __lexer_char(self) != '\n')
        __lexer_advance(self);
}


static inline void
__lexer_skip_block_comment(Lexer * self)
{
    while(__lexer_eof(self) == false 
		&& __lexer_char(self) != '*' 
		&& __lexer_peek(self) != '/')
	{
        __lexer_advance(self);
	}

    __lexer_advance(self);
    __lexer_advance(self);
}


/*
** TODO: treat excape sequences
*/
static inline Token
__lexer_read_string(Lexer * self)
{
    __lexer_advance(self);

    Token token = 
        Token(TokenType_String, __lexer_ref(self), self->state.index, 0);

    while(__lexer_eof(self) == false && __lexer_char(self) != '"')
    {
        if(__lexer_char(self) == '\\')
            __lexer_advance(self);

        __lexer_advance(self);
    }

    token.end = self->state.index;
    __lexer_advance(self);

    return token;
}


static inline Token
__lexer_read_number(Lexer * self)
{
    Token token = 
        Token(TokenType_Int, __lexer_ref(self), self->state.index, 0);

    while(isdigit(__lexer_char(self)) 
        || __lexer_char(self) == '.' 
        || tolower(__lexer_char(self)) == 'e')
    {
        if(__lexer_char(self) == '.' )
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
        if(tolower(__lexer_char(self)) == 'e')
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

        __lexer_advance(self);
    }   

    token.end  = self->state.index;

    return token;
}


static inline bool
__elem__(
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
__lexer_read_keyword(Lexer * self)
{
    Token token = 
        Token(TokenType_Keyword, __lexer_ref(self), self->state.index, 0);

    while(__lexer_eof(self) == false
            && isspace(__lexer_char(self)) == false
            && __elem__(symbol, __lexer_char(self)) == false)
    {
        __lexer_advance(self);
    }

    token.end = self->state.index;

    return token;
}


static inline Token
__lexer_read_symbol(Lexer * self)
{
    Token token = 
		Token(TokenType_Symbol, __lexer_ref(self), self->state.index, 0);

	__lexer_advance(self);

	token.end = self->state.index;

    return token;
}


Token
lexer_next_token(Lexer * self)
{
    while(__lexer_char(self) != 0)
    {
		if(isspace(__lexer_char(self)))
        {
            __lexer_skip_whitespace(self);
            continue;
        }
		else if(__lexer_char(self) == '/' 
			&& __lexer_peek(self) == '/')
		{
			__lexer_skip_line_comment(self);
			continue;
		}	
		else if(__lexer_char(self) == '/' 
			&& __lexer_peek(self) == '*')
		{
			__lexer_skip_block_comment(self);
			continue;
		}
		else if(__lexer_char(self) == '"')
            return __lexer_read_string(self);
        else if(isdigit(__lexer_char(self)))
            return __lexer_read_number(self);
        else if(__lexer_char(self) == '{')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '}')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '[')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == ']')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '(')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == ')')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '<')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '>')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '=')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '.')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == ',')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == ':')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '+')
            return __lexer_read_symbol(self);
        else if(__lexer_char(self) == '-')
            return __lexer_read_symbol(self);
        else 
            return __lexer_read_keyword(self);
    }        

    return Token(TokenType_EOF
            , NULL
            , self->state.index
            , self->state.index);
}




