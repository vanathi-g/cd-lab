%{ 
	#include <stdio.h>
	#include "y.tab.c"
	extern YYSTYPE yylval;
%}

relop "<"|"<="|"=="|"!="|">"|">="
unop "++"|"--"

%%
"if" {return IF;}
"else" {return ELSE;}
"for" {return FOR;}
{relop} {return RELOP;}
{unop} {return UNOP;}
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