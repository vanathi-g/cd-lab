%{
	#include <stdio.h>
	#include <math.h>
	void yyerror();

	struct info 
	{
		char var[10];
		char code[100];
		char true[10];
		char false[10];
		char out[10];

	};

	void newTemp(int count, char *var)
	{
		char str_count[3];
		char varname[] = "t";
		sprintf(str_count, "%d", count);
		strcat(varname, str_count);
		strcpy(var, varname);
	}

	void newLabel(int count, char *label)
	{
		char str_count[3];
		char labelname[] = "L";
		sprintf(str_count, "%d", count);
		strcat(labelname, str_count);
		strcpy(label, labelname);
	}
	
	struct info* makeNode(int count, char type) 
	{
		struct info *temp;
		temp = malloc(sizeof(struct info));

		if(type == 't')
		{
			newTemp(count, temp->var);
		}
		else
		{
			newLabel(count, temp->true);
			if(type == 'i')
				newLabel(count+1, temp->out);
			else {
				newLabel(count+1, temp->false);
				newLabel(count+2, temp->out);
			}
			
		}

		strcpy(temp->code, "");
		
		return temp;
	}

	int err_flag = 0;
	int tempvar_count=0;
	int label_count=0;
	
%}

%union {
	struct info *node;
	char name[50];
}

%token <name> ID RELOP IF THEN ELSE ENDIF BEG END
%type <node> AS I T F E

%%
START : BEG S END

S : AS {printf("%s", $1->code);}
  | I {printf("%s", $1->code);}

I : IF'('ID RELOP ID')' THEN AS ELSE AS ENDIF{
			$$ = makeNode(label_count, 'e');
			label_count += 3;

			char if_code[30];
			sprintf(if_code, "\tif %s %s %s goto %s\n\tgoto %s\n", $3, $4, $5, $$->true, $$->false);

			sprintf($$->code, "%s%s:%s\tgoto %s\n%s:%s%s:", if_code, $$->true, $8->code, $$->out, $$->false, $10->code, $$->out);
		}
  | IF'('ID RELOP ID')' THEN AS ENDIF{
  			$$ = makeNode(label_count, 'i');
  			label_count += 2;

  			char if_code[30];
  			sprintf(if_code, "\tif %s %s %s goto %s\n\tgoto %s\n", $3, $4, $5, $$->true, $$->out);

			sprintf($$->code, "%s%s:%s%s:", if_code, $$->true, $8->code, $$->out);
  		}

AS : ID'='E';'{
			$$ = makeNode(0, 't');
			sprintf($$->code, "%s\t%s = %s\n", $3->code, $1, $3->var);
		}

E : T'*'E{
			$$ = makeNode(tempvar_count, 't'); 
		  	tempvar_count++; 
		  	sprintf($$->code, "%s%s\t%s = %s * %s\n", $1->code, $3->code, $$->var, $1->var, $3->var);
		}

  | T'/'E{
  			$$ = makeNode(tempvar_count, 't'); 
		  	tempvar_count++; 
		  	sprintf($$->code, "%s%s\t%s = %s / %s\n", $1->code, $3->code, $$->var, $1->var, $3->var);
  		}

  | T {$$ = $1;}

T : T'+'F{
			$$ = makeNode(tempvar_count, 't'); 
			tempvar_count++; 
			sprintf($$->code, "%s%s\t%s = %s + %s\n", $3->code, $1->code, $$->var, $1->var, $3->var);
		}

  | T'-'F{
  			$$ = makeNode(tempvar_count, 't'); 
  			tempvar_count++; 
  			sprintf($$->code, "%s%s\t%s = %s - %s\n", $3->code, $1->code, $$->var, $1->var, $3->var);
  			if(strlen($3->code) > 0)
		  		strcat($$->code, $3->code);
  		}

  | F {$$ = $1;}

F : ID {$$ = makeNode(0, 't'); strcpy($$->var, $1);}

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

