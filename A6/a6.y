%{
	#include <stdio.h>
	#include <math.h>
	#define YYSTYPE double
	void yyerror();
	
	int err_flag = 0;
	
%}
%token ID
%token NUM

%%
S : ID'='E';' {printf("Syntactically Correct!\n");}
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
	printf("Assignment Statement Syntax Checker\n");
	yyparse();
	
}

