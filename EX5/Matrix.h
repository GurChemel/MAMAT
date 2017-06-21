#ifndef _MATRIX_H_
#define _MATRIX_H_

#include"Variable.h"
#include"Scalar.h"


class Matrix // ????????
{
public:
	Matrix(int rows, int cols, int val);
	Matrix(int startVal, int endVal);
	
	// ToDo: complete class definition
	
	virtual VarPtr Conv(VarPtr rhs) const;


private:
	
};




#endif // _MATRIX_H_
