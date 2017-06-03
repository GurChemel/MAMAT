#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string.h>

#include "Proj.h"
#include "Course.h"

Course::Course(int courseNum, char* courseName, int hwNum, int hwWeigh):
courseNum_(courseNum),courseName_(courseName),hwNum_(hwNum),hwWeigh_(hwWeigh){
	hwGrades = new int[hwNum]; //allocating memory to make array with proper size
	examGrade = -1;	//initialing variable
}// End Of Constructor

Course::~Course(){
	delete [] hwGrades;
} // End Of Destructor

double Course::getHwAverage() const{
	double sum = 0 , avg = 0;
	for(int i = 0;i < hwNum_;i++){
		sum += hwGrades[i];
	}
	avg = sum/hwNum_;
	return avg;

}// End Of getHwAverage

int Course::getCourseGrade() const{
	double 	hwAverage = getHwAverage();
	int 	couraeGrade = (int)((1-hwWeigh_)*examGrade +hwWeigh_*hwAverage + 0.5);
	return couraeGrade;

}// End Of Course::getCourseGrade
