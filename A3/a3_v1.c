#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXPROD 50
#define MAXLEN 20

void main()
{
	char grammar[MAXPROD][MAXLEN];
	int n, i;

	// Input and Output of productions of the grammar

	printf("Enter total number of productions: ");
	scanf("%d", &n);
	printf("\nEnter the productions:\n");

	for(i=0; i<n; i++)
		scanf("%s", grammar[i]);

	for(i=0; i<n; i++)
		printf("%s\n", grammar[i]);
}