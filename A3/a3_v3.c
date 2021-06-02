#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROD 50
#define MAXLEN 20

void main()
{
	char grammar[MAXPROD][MAXLEN], prod[MAXLEN], temp[3];
	char symbol;
	int n, i, j, l, ptr, posn;
	int rec[MAXPROD], rec_c=0;

	// Input and Output of productions of the grammar

	printf("Enter total number of productions: ");
	scanf("%d", &n);
	printf("\nEnter the productions:\n");

	for(i=0; i<n; i++)
		scanf("%s", grammar[i]);

	// Checking whether the grammar is left recursive

	for(i=0; i<n; i++)
	{
		l = strlen(grammar[i]);
		if(grammar[i][0] == grammar[i][3])
			rec[rec_c++] = i;
	}

	/* Removing left recursion:
		1. A -> beta is already a production, we just have to append A' to the end of it
		2. Modifying A -> A(alpha) to A'->(alpha)A' can be done in-place
		3. Add new production A' -> e after this
	*/

	char epsilon[] = "->e";

	for(i=0; i<rec_c; i++)
	{
		posn = rec[i];
		strcpy(prod, grammar[posn]);
		l = strlen(prod);
		symbol = prod[0];

		for(j=0; j<n; j++)
		{
			if(j!=posn && grammar[j][0] == symbol)
				break;
		}

		// new symbol 
		temp[0] = symbol;
		temp[1] = '\'';
		temp[2] = '\0';

		strcat(grammar[j], temp);
		strcpy(grammar[posn], grammar[j]);

		grammar[j][1] = '\'';
		grammar[j][2] = '-';
		grammar[j][3] = '>';

		for(ptr=4; ptr<l; ptr++)
			grammar[j][ptr] = prod[ptr];
		grammar[j][ptr] = '\0';
		strcat(grammar[j], temp);

		grammar[n][0] = '\0';
		strcpy(grammar[n], temp);
		strcat(grammar[n], epsilon);
		n++;
	}
	printf("\nAfter Removing LR:\n");
	for(i=0; i<n; i++)
		printf("%s\n", grammar[i]);

}

/* productions : 
E->E|T
E->T
T->T&F
T->F
F->!F
F->t
F->f

Grammar : 
E -> E or T | T
T -> T & F | F
F -> !F | true | false
*/