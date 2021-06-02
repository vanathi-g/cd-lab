%{ 
	#include <stdio.h>
	#include "y.tab.c"
%}

%%

[a-zA-Z]+ {strcpy(yylval.name, yytext); return ID;}
[' '] { };
['\n'] {return 0;}
. return yytext[0];

%%

int yywrap(){
	return 1;
}