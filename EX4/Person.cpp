#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "Proj.h"
#include "Person.h"

Person::Person(int personID = 0, const char *personName = "Jane Doh"):
	personID_(personID), personName_(strdup(personName)){
	//personName_ = new char[MAX_LINE_SIZE];
	//personName_ = strcpy(personName_, personName);
}// End Of Constructor

Person::~Person(){
	delete personName_;
} // End Of Destructor

int Person::getID() const{
	return personID_;
}// End of getID

char* Person::getName() const{
	return strdup(personName_);//TODO may cause memory leak issues.
}// End of getName

