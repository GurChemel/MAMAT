
#ifndef _StArray_
#define _StArray_

#include "Proj.h"
#include "Student.h"

class StArray {
	public:
		//constructor & default constructor
		StArray();
		//class constant methods
		bool	printStudent(int studentID) const;
		void	printAll() const;

		//class setting methods
		bool	addStudent(int studentID, char* studentName);
		bool	addEE_Course(int studentID, int courseNum, char* courseName, int HwNum, int HwWeigh);
		bool	addCS_Course(int studentID, int courseNum, char* courseName, int HwNum, int HwWeigh, bool HwTakef, char* courseBook);
		bool	setHwGrade(int studentID, int courseNum, int HwNum, int grade);
		bool	setExamGrade(int studentID, int courseNum, int grade);
		bool	setFactor(int courseNum, int factor);
		bool	resetStArray();

		//virtual methods

		//destructor
		virtual ~StArray();

	protected:
		Student** StudentsArray_;
		int StudentsNum_;

};

#endif //End Of _StArray_
