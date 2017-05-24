#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Person_ {
	int ID;
} Person, *PPerson;

PPerson perClone(PPerson perFrom) {
	PPerson perTo = malloc(sizeof(Person));
	if (perTo == NULL) return NULL;
	perTo->ID = perFrom->ID;
	return perTo;
};

void perDestroy(PPerson toKill) {
	free(toKill);
};

BOOL perCompare(PPerson perA, PPerson perB) {
	if ((perA == NULL) || (perB == NULL)) return FALSE;
	if (perA->ID == perB->ID) return TRUE;
	return FALSE;
};

void perPrint(PPerson toPrint) {
	printf("Person ID is: %d\n", toPrint->ID);
};

int main()
{
	//PList		ListCreate(clone, destroy, compare, print);
	//Result	ListAdd(PList list, PElement element);
	//Result	ListRemove(PList list, PElement element);
	//void		ListDestroy(PList list);
	//PElement	ListGetFirst(PList list);
	//PElement	ListGetNext(PList list);
	//BOOL		ListCompare(PList list_a, PList list_b);
	//void		ListPrint(PList list);

	PList perList = ListCreate(perClone, perDestroy, perCompare, perPrint);
	if (perList == NULL) { printf("Error creating list.\n"); return 0; };

	PPerson perA = malloc(sizeof(Person));
	perA->ID = 13;
	PPerson perB = malloc(sizeof(Person));
	perB->ID = 15;
	PPerson perC = malloc(sizeof(Person));
	perC->ID = 17;
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
		perPrint(temp);
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

	printf("Freeing space:\n");
	free(perA);
	printf("Killed perA\n");
	free(perB);
	printf("Killed perB\n");
	free(perC);
	printf("Killed perC\n");
	ListDestroy(perList);
	printf("Killed perList\n");

	return 0;
}


