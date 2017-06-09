#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

#include "Proj.h"
#include "Course.h"

Course::Course(int courseNum,const char* courseName, int hwNum, double hwWeigh):
courseNum_(courseNum),courseName_(strdup(courseName)),hwNum_(hwNum),hwWeigh_(hwWeigh){
	hwGrades = new int[hwNum]; //saving the exercise grades in an array
	for (int i=0;i<hwNum;i++){
		hwGrades[i] = 0; //initializing array
	}
	examGrade = -1;	//initialing variable
}// End Of Constructor

Course::~Course(){
	delete courseName_;
	delete hwGrades;
} // End Of Destructor


int Course::getNum() const{
	return courseNum_;
}// End of getNum

char* Course::getName() const{
	return strdup(courseName_);//TODO may cause memory leak issues.
}// End of getName

int Course::getExamGrade() const{
	return examGrade;
}// End of getExamGrade

int Course::getHwGrade(int exerciseNum) const{
	if (exerciseNum < 0 || exerciseNum >= hwNum_) return -1; //checking input
	return hwGrades[exerciseNum];
}// End of getHwGrade

int Course::getHwNum() const{
	return hwNum_;
}// End of getHwNum

double Course::getHwWeigh() const{
	return hwWeigh_;
}// End of getHwWeigh

double Course::getHwAverage() const{
	if (hwNum_ == 0) return 0;
	double sum = 0 , avg = 0; // parameters initialization
	for(int i = 0;i < hwNum_;i++){
		sum += hwGrades[i]; //summing all Hw grades
	}
	avg = sum/hwNum_;
	return avg;

}// End Of getHwAverage

int Course::getCourseGrade() const{
	double 	hwAverage = getHwAverage();
	int 	couraeGrade = (int)((1-hwWeigh_)*examGrade +hwWeigh_*hwAverage + 0.5);//"+0.5" is for rounding using int instead of math lib
	return couraeGrade;

}// End Of Course::getCourseGrade

bool Course::setHwGrade(int exerciseNum, int exerciseGrade) {
	if (exerciseNum < 0 || exerciseNum >= hwNum_) return false; //checking input
	hwGrades[exerciseNum]=exerciseGrade;
	return true;
}// End Of setHwGrade

bool Course::setExamGrade(int grade){
	if (grade < 0 || grade > 100) return false; //checking input
	examGrade = grade;
	return true;
}// End Of setExamGrade
