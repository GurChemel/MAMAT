#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

using std::cout;
using std::endl;

#include "StArray.h"

StArray::StArray() {
	StudentsNum_ = 0;
	StudentsArray_ = new Student*[MAX_STUDENT_NUM];
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		StudentsArray_[i] = NULL; //initializing array
	}
}; // End of Constructed

StArray::~StArray() {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			delete StudentsArray_[i];
		}
	}
	delete StudentsArray_;
}; // End Of Destructor

bool StArray::printStudent(int studentID) const {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			if (StudentsArray_[i]->getID == studentID) {
				StudentsArray_[i]->print;
				return true;
			}
		}
	}
	return false;
}; // End of printStudent

void StArray::printAll() const {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			StudentsArray_[i]->print;
		}
	}
}; // End of printAll

bool StArray::addStudent(int studentID, char* studentName) {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] == NULL) {
			StudentsArray_[i] = new Student(studentID, studentName);
			return true;
		}
	}
	return false;
}; // End of addStudent

bool StArray::addEE_Course(int studentID, int courseNum, char* courseName, int HwNum, int HwWeigh) {
	EE_Course* new_course = new EE_Course(courseNum, courseName, HwNum, HwWeigh);
	if (new_course == NULL) return false;
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			if (StudentsArray_[i]->getID == studentID) {
				StudentsArray_[i]->addEE_Course(new_course);
				return true;
			}
		}
	}
	return false;
}; // End of addEE_Course

bool StArray::addCS_Course(int studentID, int courseNum, char* courseName, int HwNum, int HwWeigh, bool HwTakef, char* courseBook) {
	CS_Course* new_course = new CS_Course(courseNum, courseName, HwNum, HwWeigh, HwTakef, courseBook);
	if (new_course == NULL) return false;
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			if (StudentsArray_[i]->getID == studentID) {
				StudentsArray_[i]->addCS_Course(new_course);
				return true;
			}
		}
	}
	return false;
}; // End of addCS_Course

bool StArray::setHwGrade(int studentID, int courseNum, int HwNum, int grade) {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			if (StudentsArray_[i]->getID == studentID) {
				CS_Course* CScurseToAddGrade = StudentsArray_[i]->getCS_Course(courseNum);
				EE_Course* EEcurseToAddGrade = StudentsArray_[i]->getEE_Course(courseNum);
				if ((CScurseToAddGrade == NULL) && (EEcurseToAddGrade == NULL)) return false;
				if (CScurseToAddGrade != NULL) {
					return CScurseToAddGrade->setHwGrade(HwNum, grade); // False if failed, True if succeded.
				}
				return EEcurseToAddGrade->setHwGrade(HwNum, grade); // False if failed, True if succeded.
			}
		}
	}
	return false;
}; // End of setHwGrade

bool StArray::setExamGrade(int studentID, int courseNum, int grade) {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			if (StudentsArray_[i]->getID == studentID) {
				CS_Course* CScurseToAddGrade = StudentsArray_[i]->getCS_Course(courseNum);
				EE_Course* EEcurseToAddGrade = StudentsArray_[i]->getEE_Course(courseNum);
				if ((CScurseToAddGrade == NULL) && (EEcurseToAddGrade == NULL)) return false;
				if (CScurseToAddGrade != NULL) {
					return CScurseToAddGrade->setExamGrade(grade); // False if failed, True if succeded.
				}
				return EEcurseToAddGrade->setExamGrade(grade); // False if failed, True if succeded.
			}
		}
	}
	return false;
}; // End of setExamGrade

bool StArray::setFactor(int courseNum, int factor) {
	bool successFlag = false;
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		if (StudentsArray_[i] != NULL) {
			EE_Course* EEcurseToAddGrade = StudentsArray_[i]->getEE_Course(courseNum);
			if (EEcurseToAddGrade != NULL) {
				if (EEcurseToAddGrade->setFactor(factor) == true) successFlag = true; // False if failed, True if succeded.
			}
		}
	}
	return false;
}; // End of setFactor

bool StArray::resetStArray() {
	for (int i = 0; i<MAX_STUDENT_NUM; i++) {
		StudentsArray_[i]->~Student;
	}
}; // End of resetStArray
