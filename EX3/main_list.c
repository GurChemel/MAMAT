#include "list.h"
#include "person.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	PList perList = ListCreate(clonePerson, destroyPerson, comparePersons, printPerson);
	if (perList == NULL) { printf("Error creating list.\n"); return 0; };
	PList perListB = ListCreate(clonePerson, destroyPerson, comparePersons, printPerson);
	if (perListB == NULL) { printf("Error creating list.\n"); return 0; };
	PList perListC = ListCreate(clonePerson, destroyPerson, comparePersons, printPerson);
	if (perListC == NULL) { printf("Error creating list.\n"); return 0; };

	PPerson perA = PersonCreate("Alice", 13, 200);
	PPerson perB = PersonCreate("Bob", 11, 201);
	PPerson perC = PersonCreate("Charley", 14, 202);
	if (perA == NULL) { printf("Error creating perA.\n"); return 0; };
	if (perB == NULL) { printf("Error creating perB.\n"); return 0; };
	if (perC == NULL) { printf("Error creating perC.\n"); return 0; };

	if (ListAdd(perList, perA)==FAIL) { printf("Error Adding perA to list.\n");};
	ListPrint(perList);
	if (ListAdd(perList, perB) == FAIL) { printf("Error Adding perB to list.\n"); };
	ListPrint(perList);
	if (ListRemove(perList, perB) == FAIL) { printf("Error Removing perB from list.\n"); };
	ListPrint(perList);
	if (ListAdd(perList, perB) == FAIL) { printf("Error Adding perB to list.\n"); };
	ListPrint(perList);
	if (ListRemove(perList, perA) == FAIL) { printf("Error Removing perA from list.\n"); };
	ListPrint(perList);
	if (ListAdd(perList, perA) == FAIL) { printf("Error Adding perA to list.\n"); };
	ListPrint(perList);
	if (ListAdd(perList, perC) == FAIL) { printf("Error Adding perC to list.\n"); };
	ListPrint(perList);
	if (ListAdd(perList, perB) == FAIL) { printf("Error Adding perB to list.\n"); };
	ListPrint(perList);

	printf("Testing GetFirst and GetNext:\n");
	PPerson temp = ListGetFirst(perList);
	while (temp != NULL) {
		printPerson(temp);
		temp = ListGetNext(perList);
	};
	printf("\n");
	
	printf("Testing Remove with double ID:\n");
	if (ListRemove(perList, perB) == FAIL) { printf("Error Removing perB from list.\n"); };
	ListPrint(perList);

	if (ListRemove(perList, perC) == FAIL) { printf("Error Removing perC from list.\n"); };
	ListPrint(perList);
	printf("Testing Remove with FALSE ID:\n");
	if (ListRemove(perList, perC) == FAIL) { printf("Error Removing perC from list.\n"); };
	ListPrint(perList);

	// Building for list compare:
	if (ListAdd(perList, perC) == FAIL) { printf("Error Adding perC to perList.\n"); };

	if (ListAdd(perListB, perA) == FAIL) { printf("Error Adding perA to perListB.\n"); };
	if (ListAdd(perListB, perC) == FAIL) { printf("Error Adding perC to perListB.\n"); };
	if (ListAdd(perListB, perB) == FAIL) { printf("Error Adding perB to perListB.\n"); };

	if (ListAdd(perListC, perA) == FAIL) { printf("Error Adding perA to perListC.\n"); };
	if (ListAdd(perListC, perB) == FAIL) { printf("Error Adding perB to perListC.\n"); };
	if (ListAdd(perListC, perC) == FAIL) { printf("Error Adding perC to perListC.\n"); };

	printf("List A:\n");
	ListPrint(perList);
	printf("List B:\n");
	ListPrint(perListB);
	printf("List C:\n");
	ListPrint(perListC);

	(ListCompare(perList, perListB)) ? printf("A == B\n") : printf("A != B\n");
	(ListCompare(perList, perListC)) ? printf("A == C\n") : printf("A != C\n");
	(ListCompare(perListB, perListC)) ? printf("B == C\n") : printf("B != C\n");


	printf("Freeing space:\n");
	destroyPerson(perA);
	printf("Killed perA\n");
	destroyPerson(perB);
	printf("Killed perB\n");
	destroyPerson(perC);
	printf("Killed perC\n");
	ListDestroy(perList);
	printf("Killed perList\n");
	ListDestroy(perListB);
	printf("Killed perListB\n");
	ListDestroy(perListC);
	printf("Killed perListC\n");
	return 0;
}


