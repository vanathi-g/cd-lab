%{
	#include <stdio.h>
	#include <math.h>
	#define YYSTYPE double
	void yyerror();
	
	int err_flag = 0;
	
%}
%token ID
%token IF
%token NUM
%token ELSE
%token RELOP

%%
S : IF'('C')''{'D'}'ELSE'{'D'}' {printf("Syntactically Correct!\n");}
C : ID RELOP ID
  | ID RELOP NUM
  | NUM RELOP ID
  | NUM RELOP NUM
D : ID'='E
E : E'+'T
  | T
T : T'*'F
  | F
F : ID
  | NUM
  ;

%%

void yyerror()
{
	//err_flag = 1;
	return;
}

void main()
{
	printf("Conditional Statement Syntax Checker\n");
	yyparse();
	
}

