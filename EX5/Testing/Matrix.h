#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix : public Variable
{
public:
	Matrix(int rows, int cols, int val);
	Matrix(int startVal, int endVal);
	Matrix(const Matrix& from);
	~Matrix() {
		delete[] Mat_;
	};
	// ToDo: complete class definition
	
	/*virtual*/ VarPtr Conv(VarPtr rhs) const;
	/*virtual*/ VarPtr Copy() const;
	/*virtual*/ VarPtr NumElems() const;
	/*virtual*/ VarPtr Size() const;
	/*virtual*/ VarPtr Size(int dim) const;
	/*virtual*/ VarPtr Transpose() const;

	/*virtual*/ int& operator[](int idx);
	/*virtual*/ int& operator[](IdxVec V);

	VarPtr operator+(const Variable&) const {};
	VarPtr operator+(const Scalar&) const;
	VarPtr operator+(const Matrix&) const;

	VarPtr operator*(const Scalar&) const;
	VarPtr operator*(const Matrix&) const;

	VarPtr operator>(const Scalar&) const;
	VarPtr operator>(const Matrix&) const;

	VarPtr operator<(const Scalar&) const;
	VarPtr operator<(const Matrix&) const;

	VarPtr operator==(const Scalar&) const;
	VarPtr operator==(const Matrix&) const;

	VarPtr operator&&(const Scalar&) const;
	VarPtr operator&&(const Matrix&) const;

	VarPtr operator||(const Scalar&) const;
	VarPtr operator||(const Matrix&) const;


private:
	int* Mat_;
	int rows_;
	int cols_;
	int elements_num;
};




#endif // _MATRIX_H_
