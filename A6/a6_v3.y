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
%token FOR
%token UNOP

%%
P : S {printf("Syntactically Correct!\n");}
S : D
  | '{'B'}'
  | F
  | I
B : B S
  | S
F : FOR'('A';'C';'O')'S
O : A
  | U
I : IF'('C')'S ELSE S
C : ID RELOP ID
  | ID RELOP NUM
  | NUM RELOP ID
  | NUM RELOP NUM
A : ID'='E
D : ID'='E';'
E : E'+'T
  | E'-'T
  | T
T : T'*'F
  | T'/'F
  | F
F : ID
  | NUM
U : ID UNOP
  | UNOP ID 
  ;

%%
void yyerror()
{
	//err_flag = 1;
	return;
}

void main()
{             
	printf("\n--------------\nSyntax Checker\n--------------\n\n");
	yyparse();
	
}

