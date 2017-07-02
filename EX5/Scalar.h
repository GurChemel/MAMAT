#ifndef _SCALAR_H_
#define _SCALAR_H_

#include"Variable.h"

class Scalar : public Variable
{
public:
	Scalar(int val) : Val_(val) {};
	Scalar(const Scalar& from) : Val_(from.Val_) {};
	~Scalar() {};
	
	virtual bool IsScalar() const { return true;};
	
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
		os << Val_;
	};
	
	VarPtr self_add() const{
        return VarPtr(new Scalar(Val_*2));
    };

private:
	int Val_;
};


#endif // _SCALAR_H_
