#ifndef _PERSON_H_
#define _PERSON_H_

typedef struct Person_ Person,*PPerson;

PPerson PersonCreate(char* perName, int perAge, int perID);
void	printPerson(void*);
PPerson clonePerson(void*);
void	destroyPerson(void*);
BOOL	comparePersons(void*, void*);


#endif
