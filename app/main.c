#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/lexer.h"


int
main(void)
{
    char * code = ".-hello-world 27 3.14";

    Lexer lexer = Lexer("source", strlen(code), code);

	for(Token t = lexer_next_token(&lexer);; t = lexer_next_token(&lexer))
	{
		token_show(&t);

		if(t.type == TokenType_EOF || t.type == TokenType_Undefined)
			break;
	}
	
    printf("Program exit..\n");
    return EXIT_SUCCESS;
}
