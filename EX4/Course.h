
#ifndef _Course_
#define _Course_

class Course {
	public:
	//constructor & default constructor
	Course(int courseNum = 0 ,const char *courseName = "default", int hwNum = 0, double hwWeigh = 0);
	//class constant methods
	int 	getNum() const;
	char*	getName() const;
	int 	getExamGrade() const;
	int 	getHwGrade(int exerciseNum) const;
	int 	getHwNum() const;
	double 	getHwWeigh() const;
	double 	getHwAverage() const;

	//class setting methods
	bool 	setExamGrade(int grade);
	bool 	setHwGrade(int exerciseNum, int exerciseGrade);

	//virtual methods
	virtual int getCourseGrade() const;

	//destructor
	virtual ~Course();

	protected:
	const int 		courseNum_;
	char*		courseName_;
	const int 		hwNum_;
	const double 	hwWeigh_;
	int 			examGrade;
	int* 			hwGrades;

};

#endif //End Of _Course_
