#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define ENDTOKEN (c == ' ' || c == '\n')

void main()
{
	char c, prev;
	int err_flag = 0;
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
>= <= == != > < = ! + - * / %
RELOP RELOP RELOP RELOP RELOP RELOP ASSIGN LOGOP ARITHOP ARITHOP ARITHOP ARITHOP ARITHOP Done...
*/