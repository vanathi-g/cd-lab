%{ 
	#include <stdio.h>
	#include "y.tab.c"
	extern YYSTYPE yylval;
%}

%%

([a-zA-Z])([a-zA-Z]|[0-9])* {return ID;}
[0-9]+ {return NUM;}
[\n] {return 0;}
. return yytext[0];

%%

int yywrap(){
	return 1;
}
