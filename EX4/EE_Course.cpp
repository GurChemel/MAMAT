#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "Proj.h"
#include "Course.h"
#include "EE_Course.h"

EE_Course::EE_Course(int courseNum,const char* courseName, int hwNum, double hwWeigh):
Course(courseNum, courseName, hwNum, hwWeigh){
	factor = 0;

}// End Of Constructor

int EE_Course::getFactor() const{
	return factor;
}// End Of getFactor

bool EE_Course::setFactor(int _factor){
	factor = _factor;
	return true;
}

int EE_Course::getCourseGrade() const{
	int grade = 0;
	grade = Course::getCourseGrade() + factor;
	if (grade > 100) grade = 100;
	if (grade < 0) grade = 0;
	return grade;

}// End Of getCourseGrade

EE_Course::~EE_Course(){};
