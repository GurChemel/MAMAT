
#include "MySharedPtr.h"
#include "Variable.h"
#include "Scalar.h"
#include "Matrix.h"
#include "ScriptExceptions.h"

using namespace std;

int main(){
	
	VarPtr p1(new Scalar(7));
	VarPtr p2(new Scalar(5));
	VarPtr m_2_3(new Matrix(2,3,4));
	(*m_2_3)[3]=7;
	IdxVec resIdx = { 1,3 };
	(*m_2_3)[resIdx]=17;
	VarPtr m_3_4(new Matrix(3,4,1));
	cout << "Created all." << endl;
			
	try {
		cout << "Matrix:" << endl << (m_2_3) << endl;
		cout << "p1:" << p1 << ". p2:" << p2 << endl;
		
		VarPtr p3 = ((*p1) > (*p2));
		cout << "VarPtr p3 = ((*p1) > (*p2))" << endl;
		cout << p3 << endl << endl;
		p3 = ((*m_2_3) > (*p2));
		cout << "p3 = ((*m_2_3) > (*p2))" << endl;
		cout << p3 << endl << endl;
		p3 = ((*p2) > (*m_2_3));
		cout << "p3 = ((*p2) > (*m_2_3))" << endl;
		cout << p3 << endl << endl;
		p3 = ((*m_2_3) == (*p1));
		cout << "p3 = ((*m_2_3) == (*p1))" << endl;
		cout << p3 << endl << endl;
		p3 = ((*p2) && (*p1));
		cout << "p3 = ((*p2) && (*p1))" << endl;
		cout << p3 << endl << endl;
		p3 = ((*p2) || (*p1));
		cout << "p3 = ((*p2) || (*p1))" << endl;
		cout << p3 << endl << endl;
		
				
		
		/*
		p3 = ((*p1) + (*m_2_3));
		cout << "Matrix + 3:" << endl << p3 << endl;
		p3 = ((*p3) + (*m_2_3));
		cout << "Matrix all 11:" << endl << p3 << endl;
		cout << "Matrix 2x3:" << endl << (m_2_3) << endl;
		IdxVec resIdx = { 2, 1};
		(*m_2_3)[resIdx] = 7;
		cout << "Matrix 2x3:" << endl << (m_2_3) << endl;
		cout << "Matrix 3x4:" << endl << (m_3_4) << endl;
		*/
	} 
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	catch (...)
	{
		cout << "Unexpected Error" << endl;
		return 1;
	}

	return 0;
}
