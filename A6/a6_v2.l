%{ 
	#include <stdio.h>
	#include "y.tab.c"
	extern YYSTYPE yylval;
%}

relop "<"|"<="|"=="|"!="|">"|">="

%%
"if" {return IF;}
"else" {return ELSE;}
{relop} {return RELOP;}
([a-zA-Z])([a-zA-Z]|[0-9])* {return ID;}
[0-9]+ {return NUM;}
[\n] { }
[\t] { }
[' '] { }
. return yytext[0];

%%

int yywrap(){
	return 1;
}