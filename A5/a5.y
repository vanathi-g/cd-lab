%{
	#include <stdio.h>
	#include <math.h>
	#define YYSTYPE double
	void yyerror();
	
	int err_flag = 0;
	
%}
%token NUM
/* for prec., first declared = lowest prec and left, right used to specify associativity */
%left '|'
%left '&'
%left '+' '-'
%left '*' '/'
%right '^'
%right '!'
%left '(' ')'
%%

S : E {printf("Result: %.2f\n",$$);}
E : E'+'E {$$ = $1 + $3;}
  | E'-'E {$$ = $1 - $3;}
  | E'*'E {$$ = $1 * $3;}
  | E'/'E {$$ = $1 / $3;}
  | E'^'E {$$ = pow($1, $3);}
  | E'&'E {$$ = $1 && $3;}
  | E'|'E {$$ = $1 || $3;}
  | '!'E {$$ = !$2;}
  | '('E')' {$$ = $2;}
  | NUM {$$ = $1;}

%%

void yyerror()
{
	err_flag = 1;
	return;
}

void main()
{
	printf("CALCULATOR\n");
	yyparse();
	if(err_flag)
	{
		printf("Enter numbers and operators only!\n");
	}
	
}

