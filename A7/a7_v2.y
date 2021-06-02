%{
	#include <stdio.h>
	#include <math.h>
	void yyerror();

	struct info 
	{
		char var[10];
		char code[100];
	};
	
	struct info* makeNode(int count) 
	{
		struct info *temp;
		temp = malloc(sizeof(struct info));
		char str_count[3];
		sprintf(str_count, "%d", count);

		char varname[] = "t";
		strcat(varname, str_count);
		strcpy(temp->var, varname);
		strcpy(temp->code, "");
		
		return temp;
	}

	int err_flag = 0;
	int count=0;
	
%}

%union {
	struct info *node;
	char name[50];
}

%token <name> ID
%type <node> AS T F E

%%

AS : ID'='E {printf("%s%s = %s\n", $3->code, $1, $3->var);}

E : T'*'E{
			$$ = makeNode(count); 
		  	count++; 
		  	sprintf($$->code, "%s%s%s = %s * %s\n", $1->code, $3->code, $$->var, $1->var, $3->var);
		  }

  | T'/'E{
  			$$ = makeNode(count); 
		  	count++; 
		  	sprintf($$->code, "%s%s%s = %s / %s\n", $1->code, $3->code, $$->var, $1->var, $3->var);
  		}

  | T {$$ = $1;}

T : T'+'F{
			$$ = makeNode(count); 
			count++; 
			sprintf($$->code, "%s%s%s = %s + %s\n", $3->code, $1->code, $$->var, $1->var, $3->var);
		}

  | T'-'F{
  			$$ = makeNode(count); 
  			count++; 
  			sprintf($$->code, "%s%s%s = %s - %s\n", $3->code, $1->code, $$->var, $1->var, $3->var);
  			if(strlen($3->code) > 0)
		  		strcat($$->code, $3->code);
  		}

  | F {$$ = $1;}

F : ID {$$ = makeNode(0); strcpy($$->var, $1);}

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

