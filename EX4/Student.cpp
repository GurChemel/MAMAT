#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

#include "Student.h"

Student::Student(int personID, const char *personName):
	Person(personID, personName){
	EE_courses_num_ = 0;
	CS_courses_num_ = 0;
	EE_courses_ = new EE_Course*[MAX_COURSE_NUM];
	CS_courses_ = new CS_Course*[MAX_COURSE_NUM];
	for (int i = 0; i<MAX_COURSE_NUM; i++) {
		EE_courses_[i] = NULL; //initializing array
		CS_courses_[i] = NULL; //initializing array
	}
}// End Of Constructor

Student::~Student(){
	for (int i = 0; i<MAX_COURSE_NUM; i++) {
		if (EE_courses_[i] != NULL) {
			delete EE_courses_[i];
		}
		if (CS_courses_[i] != NULL) {
			delete CS_courses_[i];
		}
	}
	delete[] EE_courses_;
	delete[] CS_courses_;
	// delete[] personName_; removed in person.cpp
} // End Of Destructor

int Student::getCourseCnt() const{
	return (EE_courses_num_ + CS_courses_num_);
}// End of getCourseCnt

EE_Course* Student::getEE_Course(int EE_CourseNum) const {
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (EE_courses_[i] != NULL) {
			if (EE_courses_[i]->getNum() == EE_CourseNum) {
				return EE_courses_[i];
			}
		}
	}
	return NULL;
};// End of getEE_Course

CS_Course* Student::getCS_Course(int CS_CourseNum) const {
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (CS_courses_[i] != NULL) {
			if (CS_courses_[i]->getNum() == CS_CourseNum) {
				return CS_courses_[i];
			}
		}
	}
	return NULL;
};// End of getCS_Course

int Student::getAvg() const {
	double sum_of_grades = 0;
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (CS_courses_[i] != NULL) {
			sum_of_grades += CS_courses_[i]->getCourseGrade();
		}
		if (EE_courses_[i] != NULL) {
			sum_of_grades += EE_courses_[i]->getCourseGrade();
		}
	}
	int avg = 0;
	if ((EE_courses_num_ + CS_courses_num_) != 0) {
		avg = (0.5 + (sum_of_grades / ((double)EE_courses_num_ + (double)CS_courses_num_))); //"+0.5" is for rounding using int instead of math lib
	}
	return avg;
};// End of getAvg

void Student::print() const {
	
	char* temp_string = NULL; // new  char(MAX_LINE_SIZE);
	
	cout << "Student Name: " << personName_ << endl;
	cout << "Student ID: " << personID_ << endl;
	cout << "Average Grade: " << getAvg() << endl;
	cout << endl << "EE Courses:" << endl;
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (EE_courses_[i] != NULL) {
			temp_string = EE_courses_[i]->getName();
			cout << EE_courses_[i]->getNum() << " " << temp_string << ": " << EE_courses_[i]->getCourseGrade() << endl;
			free(temp_string);
		}
	}
	cout << endl << "CS Courses:" << endl;
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (CS_courses_[i] != NULL) {
			temp_string = CS_courses_[i]->getName();
			cout << CS_courses_[i]->getNum() << " " << temp_string << ": " << CS_courses_[i]->getCourseGrade() << endl;
			free(temp_string);
		}
	}
	cout << endl;

};// End of print

bool Student::addEE_Course(EE_Course* NewEE_Course) {
	if (NewEE_Course == NULL) return false;
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (EE_courses_[i] == NULL) {
			EE_courses_[i] = NewEE_Course;
			EE_courses_num_++;
			return true;
		}
	}
	return false;
};// End of addEE_Course

bool Student::addCS_Course(CS_Course* NewCS_Course) {
	if (NewCS_Course == NULL) return false;
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (CS_courses_[i] == NULL) {
			CS_courses_[i] = NewCS_Course;
			CS_courses_num_++;
			return true;
		}
	}
	return false;
};// End of addCS_Course

bool Student::remCourse(int CourseNumToRemove) {
	for (int i = 0; i < MAX_COURSE_NUM; i++) {
		if (EE_courses_[i] != NULL) {
			if (EE_courses_[i]->getNum() == CourseNumToRemove) {
				delete EE_courses_[i];
				EE_courses_[i] = NULL;
				return true;
			}
		}
		if (CS_courses_[i] != NULL) {
			if (CS_courses_[i]->getNum() == CourseNumToRemove) {
				delete CS_courses_[i];
				CS_courses_[i] = NULL;
				return true;
			}
		}
	}
	return false;
};// End of remCourse
