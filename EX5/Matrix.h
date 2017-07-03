#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix : public Variable
{
public:
	// Constructors:
    Matrix(int rows, int cols, int val);
	Matrix(int startVal, int endVal);
	
    // Copy Constructor:
    Matrix(const Matrix& from);

	// Destructor:
	~Matrix() {
        delete[] Mat_;
	};
	
	/*virtual*/ VarPtr Conv(VarPtr rhs) const;
	/*virtual*/ VarPtr Copy() const;
	/*virtual*/ VarPtr NumElems() const;
	/*virtual*/ VarPtr Size() const;
	/*virtual*/ VarPtr Size(int dim) const;
	/*virtual*/ VarPtr Transpose() const;

	/*virtual*/ int& operator[](int idx);
	/*virtual*/ int& operator[](IdxVec V);
	int operator[](int idx) const;
	int operator[](IdxVec V) const; 

	VarPtr operator+(const Variable&) const;
	VarPtr operator+(const Scalar&) const;
	VarPtr operator+(const Matrix&) const;

	VarPtr operator*(const Variable&) const;
	VarPtr operator*(const Scalar&) const;
	VarPtr operator*(const Matrix&) const;

	VarPtr operator>(const Variable&) const;
	VarPtr operator>(const Scalar&) const;
	VarPtr operator>(const Matrix&) const;

	VarPtr operator<(const Variable&) const;
	VarPtr operator<(const Scalar&) const;
	VarPtr operator<(const Matrix&) const;

	VarPtr operator==(const Variable&) const;
	VarPtr operator==(const Scalar&) const;
	VarPtr operator==(const Matrix&) const;

	VarPtr operator&&(const Variable&) const;
	VarPtr operator&&(const Scalar&) const;
	VarPtr operator&&(const Matrix&) const;

	VarPtr operator||(const Variable&) const;
	VarPtr operator||(const Scalar&) const;
	VarPtr operator||(const Matrix&) const;

	void Print(ostream& os) const{
		int i,j;
		for (i=0;i<rows_;i++){
			for (j=0;j<cols_;j++){
				os << Mat_[i+j*rows_] << "\t";
			}
			if (i != (rows_-1)) {
				os << "\n";
			}
		}
	};
	
private:
	int* Mat_;
	int rows_;
	int cols_;
	int elements_num;
};


#endif // _MATRIX_H_
