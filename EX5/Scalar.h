#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar : public Variable
{
public:
	Scalar(int val) : Val_(val) {};
	Scalar(const Scalar& from) : Val_(from.Val_) {};
	
	/*virtual*/ bool IsScalar() const { return true; };

	/*virtual*/ VarPtr Conv(VarPtr rhs) const;
	/*virtual*/ VarPtr Copy() const;
	/*virtual*/ VarPtr NumElems() const;
	/*virtual*/ VarPtr Size() const;
	/*virtual*/ VarPtr Size(int dim) const;
	/*virtual*/ VarPtr Transpose() const {return Copy(); };
	
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
	int Val_;
};

#endif // _SCALAR_H_
