
#ifndef _EE_Course_
#define _EE_Course_

#include "Course.h"

class EE_Course : public Course{

public:
	//constructor & default constructor
	EE_Course(int courseNum = 0 ,const char* courseName = "default", int hwNum = 0, double hwWeigh = 0);

	//class constant methods
	int 	getFactor() const;

	//virtual methods methods
	int 	getCourseGrade() const;//overrides class Course method

	//class setting methods
	bool 	setFactor(int _factor);

	~EE_Course();

protected:
	int factor;

}; // End Of EE_Course

#endif// End Of _EE_Course_
