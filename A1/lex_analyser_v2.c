// Recongnizes operators and numerical constants

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ENDTOKEN (c == ' ' || c == '\n')

void main()
{
	char c, prev;
	int err_flag = 0, digit_seen = 0;
	int state = 0; // 0 for start state; state after encountering a space

	// Keep reading characters until \n
	do
	{
		c = getchar();
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

		}
		if(err_flag == 1)
		{
			printf("Invalid token!\n");
			break;
		}
	}while(c != '\n');
	printf("Done...\n");

}

/* OUTPUT:
vanathi@vanathi-HP-Pavilion-x360:~/Desktop/Semester 6/Compiler Design/Lab/A1$ ./lc
1 123 12.3 123.001 45e10 4e10 4e1 4e-10 45e+10 5e1
NUMCONST NUMCONST NUMCONST NUMCONST NUMCONST NUMCONST NUMCONST NUMCONST NUMCONST NUMCONST Done...
*/