#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "Proj.h"
#include "Course.h"
#include "CS_Course.h"

CS_Course::CS_Course(int courseNum ,const char* courseName, int hwNum, double hwWeigh, bool takefSet, const char* bookNameSet):
Course(courseNum,courseName,hwNum,hwWeigh),takef(takefSet){
	int namelen = strlen(bookNameSet);
	bookName = new char[namelen +1];
	strcpy(bookName, bookNameSet);

};// End Of Constructor

CS_Course::~CS_Course(){
	delete[] bookName;
}// End Of Destructor

bool CS_Course::isTakef(){
	return takef;
}// End Of  isTakef

char* CS_Course::getBook() const{
	return strdup(bookName); //TODO may cause memory leak issues.
}// End Of getBook

bool CS_Course::setBook(char* newBook){
	//checking paramets
	if ( newBook == NULL) return false;
	//variable for memory allocation
	int newNameLen = (int)strlen(newBook) +1;
	// freeing memory (in case of need)
	if (bookName != NULL) delete [] bookName;
	bookName = new char[newNameLen];
	strcpy(bookName, newBook);
	if (strcmp(bookName, newBook) == 0) {
		//bookname is identical to newbook
		return true;
	}else{
		//bookname is NOT identical to newbook
		return false;
	}
}

bool CS_Course::setTakef(bool TakefSet){
	takef = TakefSet;
	return true;
}// End Of setTakef

//virtual function
int CS_Course::getCourseGrade() const{
	int gradeWithHW = Course::getCourseGrade();
	if (takef == true){
		return gradeWithHW;
	}
	else{
		if (examGrade > gradeWithHW){
			return examGrade;
		}
		else{
			return gradeWithHW;
		}

	}
}// End Of getCourseGrade
