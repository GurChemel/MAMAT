#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include<iostream>
#include<vector>
#include"MySharedPtr.h"

using namespace std;

class Variable;
class Scalar;
class Matrix;

typedef MySharedPtr<Variable> VarPtr;
typedef vector<int> IdxVec;

IdxVec operator+(const IdxVec& lhs, const IdxVec& rhs);


class Variable
{
public:
	
	// ToDo: complete class definition
	
	virtual VarPtr Conv(VarPtr rhs) const = 0;
	virtual VarPtr Copy() const = 0;
	virtual VarPtr Size() const = 0;
	virtual VarPtr NumElems() const = 0;
	virtual VarPtr Size(int dim) const = 0;
	virtual VarPtr Transpose() const = 0;
	virtual VarPtr operator+(const Variable&) const = 0;
	virtual VarPtr operator+(const Scalar&) const = 0;
	virtual VarPtr operator+(const Matrix&) const = 0;
	
	virtual int& operator[](int idx) = 0;
	virtual int& operator[](IdxVec V) = 0;


};




#endif // _VARIABLE_H_
