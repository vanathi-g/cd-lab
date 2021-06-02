#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROD 50
#define MAXLEN 20

void main()
{
	char grammar[MAXPROD][MAXLEN];
	int n, i, l;
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

	if(rec_c > 0)
	{
		printf("\nGrammar is left recursive. LR Productions are:\n");
		for(i=0; i<rec_c; i++)
			printf("%s\n",grammar[rec[i]]);
	}
	else
		printf("Grammar is not left recursive.\n");
}

/* productions : 
E->E+T
E->T
T->T+F
T->F
F->i
*/