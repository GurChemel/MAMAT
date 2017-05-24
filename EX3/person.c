#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "defs.h"
#include "person.h"

typedef struct Person_ {
	char*	name;
	int		age;
	int		ID;
};

PPerson PersonCreate(char* perName, int perAge, int perID) {
	// Check inputs:
	if (perName == NULL) return NULL;
	// Allocate memory:
	PPerson new_person = malloc(sizeof(Person));
	if (new_person == NULL) return NULL;
	new_person->name = malloc(sizeof(perName));
	if (new_person->name == NULL) return NULL;
	// Copy the relevant data:
	new_person->ID = perID;
	new_person->age = perAge;
	if (strcpy(new_person->name, perName) == NULL) return NULL;
	// Return the person's pointer:
	return new_person;
};

void	destroyPerson(void* toKill) {
	PPerson perToKill = (PPerson)toKill;
	if (perToKill == NULL) return;
	free(perToKill->name);
	free(perToKill);
	return;
};

PPerson clonePerson(void* source) {
	PPerson old_person = (PPerson)source;
	return PersonCreate(old_person->name, old_person->age, old_person->ID);
};

BOOL	comparePersons(void* sourceA, void* sourceB) {
	PPerson perA = (PPerson)sourceA;
	PPerson perB = (PPerson)sourceB;
	if ((perA == NULL) || (perB == NULL)) return FALSE;
	return (perA->ID == perB->ID);
};

void	printPerson(void* toPrint) {
	PPerson perToPrint = (PPerson)toPrint;
	printf("Name: %s, ID: %d, Age %d\n", perToPrint->name, perToPrint->ID, perToPrint->age);
};

