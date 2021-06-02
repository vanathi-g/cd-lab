%{
	#include <stdio.h>
	#include <math.h>
	#define YYSTYPE struct info*
	void yyerror();

	struct info {
		char var;
		char *code;
	};

	struct info* makeNode() {
		struct info *temp;
		temp = malloc(sizeof(struct info));
		return temp;
	}

	int err_flag = 0;
	int count=0;
	
%}

%token ID

%%

S : ID'='E {printf("%c = %c\n", $1, $3->var);}
E : E'+'F{$$ = makeNode(); $$->var = 't'; printf("%c = %c + %c\n", $$->var, $1->var, $3->var);}
  | F {$$ = $1;}
F : ID {$$ = makeNode(); $$->var = $1;}

%%

void yyerror()
{
	return;
}

void main()
{
	printf("Intermediate Code Generation\n");
	yyparse();
}

