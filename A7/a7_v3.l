%{ 
	#include <stdio.h>
	#include "y.tab.c"
%}

letter [a-zA-Z]
digit [0-9]
relop "<"|"<="|"=="|"!="|">"|">="

%%

"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"endif" {return ENDIF;}

{relop} {strcpy(yylval.name, yytext); return RELOP;}
{letter}({letter}|{digit})* {strcpy(yylval.name, yytext); return ID;}
[' '] { };
['\t'] { };
['\n'] { };
. return yytext[0];

%%

int yywrap(){
	return 1;
}