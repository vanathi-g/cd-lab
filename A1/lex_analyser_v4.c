// Recognizes operators, all constants, identifiers

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ENDTOKEN (c == ' ' || c == '\n')
#define MAX 32

typedef struct
{
	char name[MAX];
	int n;

}identifier;

int isKeyword(identifier id);


void main()
{
	char c, prev;
	int err_flag = 0, digit_seen = 0, char_seen = 0;
	int state = 0; // 0 for start state; state after encountering a space

	identifier id;
	strcpy(id.name, "");
	id.n = 0;

	// Keep reading characters until \n
	while((c = getchar()) != EOF)
	{
		switch(state)
		{
			case 0:
			{
				if(c == '<' || c == '>')
					state = 1;
				else if(c == '=')
					state = 2;
				else if(c == '!')
					state = 4;
				else if(c == '+' || c == '-' || c == '*' || c == '/' || c == '%')
					state = 5;
				else if(isdigit(c))
					state = 6;
				else if(c == '\'')
					state = 10;
				else if(c == '"')
					state = 11;
				else if(isalpha(c) || c == '_')
				{
					id.name[id.n++] = c;
					state = 14;
				}
				else
					err_flag = 1;
				break;
			}
			case 1:
			{
				if ENDTOKEN
				{
					printf("RELOP ");
					state = 0;
				}
				else if(c == '=')
					state = 3;
				else
					err_flag = 1;
				break;
			}
			case 2:
			{
				if ENDTOKEN
				{
					printf("ASSIGN ");
					state = 0;
				}
				else if(c == '=')
					state = 3;
				else
					err_flag = 1;
				break;
			}
			case 3:
			{
				if ENDTOKEN
				{
					printf("RELOP ");
					state = 0;
				}
				else
					err_flag = 1;
				break;
			}
			case 4:
			{
				if ENDTOKEN
				{
					printf("LOGOP ");
					state = 0;
				}
				else if(c == '=')
					state = 3;
				else
					err_flag = 1;
				break;
			}
			case 5:
			{
				if ENDTOKEN
				{
					printf("ARITHOP ");
					state = 0;
				}
				else
					err_flag = 1;
				break;
			}
			case 6:
			{
				if ENDTOKEN
				{
					printf("NUMCONST ");
					state = 0;
				}
				else if(isdigit(c))
					state = 6;
				else if(c == '.')
					state = 7;
				else if(c == 'E' || c == 'e')
					state = 8;
				else
					err_flag = 1;
				break;
			}
			case 7:
			{
				if(ENDTOKEN && digit_seen == 1)
				{
					printf("NUMCONST ");
					state = 0;
					digit_seen = 0;
				}
				else if(isdigit(c))
				{
					digit_seen = 1;
					state = 7;
				}
				else
					err_flag = 1;
				break;
			}
			case 8:
			{
				if(ENDTOKEN && digit_seen == 1)
				{
					printf("NUMCONST ");
					state = 0;
					digit_seen = 0;
				}
				else if(c == '+' || c == '-')
					state = 9;
				else if(isdigit(c))
				{
					digit_seen = 1;
					state = 8;
				}
				else
					err_flag = 1;
				break;
			}
			case 9:
			{
				if(ENDTOKEN && digit_seen == 1)
				{
					printf("NUMCONST ");
					state = 0;
					digit_seen = 0;
				}
				else if(isdigit(c))
				{
					digit_seen = 1;
					state = 9;
				}
				else
					err_flag = 1;
				break;

			}
			case 10:
			{
				if(c == '\'')
				{
					state = 12;
					char_seen = 0;
				}
				else if(c!='\n' && char_seen == 0)
				{
					char_seen = 1;
					state = 10;
				}
				else
					err_flag = 1;
				break;
			}
			case 11:
			{
				if(c == '"')
					state = 13;
				else if(c != '\n')
					state = 11;
				else
					err_flag = 1;
				break;
			}
			case 12:
			{
				if ENDTOKEN
				{
					printf("CHARCONST ");
					state = 0;
				}
				else
					err_flag = 1;
				break;
			}
			case 13:
			{
				if ENDTOKEN
				{
					printf("STRCONST ");
					state = 0;
				}
				else
					err_flag = 1;
				break;
			}
			case 14:
			{
				if ENDTOKEN
				{
					id.name[id.n]='\0';
					if(isKeyword(id))
						printf("KW ");
					else
						printf("ID ");
					state = 0;
					strcpy(id.name, "");
					id.n = 0;
				}
				else if(isalnum(c) || c == '_')
				{
					id.name[id.n++] = c;
					state = 14;
				}
				else
					err_flag = 1;
				break;
			}

		}
		if(err_flag == 1)
		{
			printf("Invalid token!\n");
			break;
		}
		if(c == '\n')
			printf("\n");
	}
	printf("\n");

}

int isKeyword(identifier id)
{
	char words[32][15] = {"auto", "break", "case", "char", "const", "continue", "default",
						 "do", "double", "else", "enum", "extern", "float", "for", "goto",
						 "if", "int", "long", "register", "return", "short", "signed", "sizeof",
						 "static", "struct", "switch", "typedef", "union", "unsigned", "void",
						 "volatile", "while"};
	for(int i=0; i<32; i++)
	{
		if(strcmp(id.name, words[i]) == 0)
			return 1;
	}
	return 0;
}

/*
int a = 5
char c = '6'
if "hello" >= "world !"
float _number_ = 123e-10

*/


/* OUTPUT:
vanathi@vanathi-HP-Pavilion-x360:~/Desktop/Semester 6/Compiler Design/Lab/A1$ ./lc
int a = 5
char c = '6'
if "hello" >= "world !"
float _number_ = 123e-10
KW ID ASSIGN NUMCONST 
KW ID ASSIGN CHARCONST 
KW STRCONST RELOP STRCONST 
KW ID ASSIGN NUMCONST 

*/