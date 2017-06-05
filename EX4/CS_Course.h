
#ifndef _CS_CCOURSE_
#define _CS_CSOURSE_

#include "Course.h"

class CS_Course: public Course{

public:
	//constructor & default constructor
	CS_Course(int courseNum = 0 ,const char* courseName = "default", int hwNum = 0, double hwWeigh = 0, bool takefSet = false, const char* bookNameSet = "noName");

	//class constant methods
	bool isTakef();
	char* getBook() const;

	//class setting methods
	bool setTakef(bool Takef);
	bool setBook(char* newBook);

	//virtual function
	int getCourseGrade() const;

	//destructor
	~CS_Course();


protected:

	bool	takef;
	char* 	bookName;


}; // End Of CS_Course


#endif // End Of _CS_COURSE_
