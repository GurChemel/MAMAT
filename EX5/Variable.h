#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include<iostream>
#include<vector>
#include"MySharedPtr.h"

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
	
	virtual VarPtr Copy() const = 0;
	
	virtual VarPtr operator+(const Variable&) const = 0;
	virtual VarPtr operator+(const Scalar&) const = 0;
	virtual VarPtr operator+(const Matrix&) const = 0;

};




#endif // _VARIABLE_H_
