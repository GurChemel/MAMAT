#ifndef _PERSON_H_
#define _PERSON_H_

typedef struct Person_ Person,*PPerson;

PPerson PersonCreate(char* perName, int perAge, int perID);
void	printPerson(PPerson);
PPerson clonePerson(PPerson);
void	destroyPerson(PPerson);
BOOL	comparePersons(PPerson,PPerson);


#endif
