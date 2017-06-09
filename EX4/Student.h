
#ifndef _Student_
#define _Student_

#include "Proj.h"
#include "Person.h"
#include "CS_Course.h"
#include "EE_Course.h"

class Student : public Person{
	public:
		//constructor & default constructor
		Student(int StudentID, const char *StudentName);
		//class constant methods
		int 	getCourseCnt() const;
		EE_Course*	getEE_Course(int EE_CourseNum) const;
		CS_Course*	getCS_Course(int CS_CourseNum) const;
		int 	getAvg() const;
		void	print() const;

		//class setting methods
		bool	addEE_Course(EE_Course* NewEE_Course);
		bool	addCS_Course(CS_Course* NewCS_Course);
		bool	remCourse(int CourseNumToRemove);

		//virtual methods

		//destructor
		virtual ~Student();

	protected:
		EE_Course** EE_courses_;
		int EE_courses_num_;
		CS_Course** CS_courses_;
		int CS_courses_num_;

};

#endif //End Of _Student_
