%{ 
	#include <stdio.h>
	#include "y.tab.c"
	extern YYSTYPE yylval;
%}

%%

[a-zA-Z] {yylval = yytext[0]; return ID;}
[\t] ;
[\n] return 0;
. return yytext[0];

%%

int yywrap(){
	return 1;
}
