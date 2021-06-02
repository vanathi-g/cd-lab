%{ 
	#include <stdio.h>
	#include "y.tab.c"
%}

letter [a-zA-Z]
digit [0-9]
relop "<"|"<="|"=="|"!="|">"|">="
type "integer"|"real"|"char"

digits {digit}+
optFrac \.{digits}
optExp E("+"|"-")?{digits}
numberconst {digits}({optFrac})?({optExp})?

charconst \'{letter}\'

constant {numberconst}|{charconst}

%%

"if" {return IF;}
"then" {return THEN;}
"else" {return ELSE;}
"endif" {return ENDIF;}
"begin" {return BEG;}
"end" {return END;}
{type} {yylval.keyword = yytext[0]; return TYPE;}

{constant} {strcpy(yylval.name, yytext); return CONST;}
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