#include<string>
#include<cstring>
#include<exception>
#include<stdexcept>
#include<iostream>
#include<string.h>
#include<string>

using namespace std;

#define SYNTAX_UNBALANCED ScriptException("Error: Expression or statement is incorrect--possibly unbalanced (, {, or [.")
#define SYNTAX_INCOMPLETE ScriptException("Error: Expression or statement is incomplete or incorrect.")
#define SYNTAX_UNDEFINED(x) ScriptException(string("Undefined function or variable '") += string(x) += "'")

#define MISSING_VAR ScriptException("Missing input arguments for operator or function.")
#define BAD_VAR_NUM ScriptException("Too many/few input arguments for operator or function.")
#define BAD_INPUT ScriptException("Invalid input arguments for operator or function.")
#define MISSING_BLOCK_END  ScriptException("At least one END is missing.")
#define SUBSCRIPT_MISMATCH ScriptException("Subscripted assignment dimension mismatch.")
#define INDEX_OUT_OF_RANGE ScriptException("Index exceeds matrix dimensions.")
#define BAD_MAT_DIMS(x) ScriptException(string("Error using  ") += string(x) += ", Matrix dimensions must agree.")
#define BAD_MAT_PROD ScriptException("Error using  *, Inner matrix dimensions must agree.")
#define INVALID_VAR_NAME(x) ScriptException(string("Invalid variable name '") += string(x) += "'")

#define UNEXPECTED(x)  ScriptException(x)

class ScriptException : public exception {
public:
	ScriptException(const char* string) {
		int length = strlen(string);
		String_ = new char[length + 1];
		String_ = strcpy(String_, string);
	}

	~ScriptException() throw() {
		delete[] String_;
	}
	
	virtual const char* what() const throw(){
		return String_;
	}

private:
	char* String_;

};


int main(){
	
	string str = "minion";
	
	try
	{
		throw SYNTAX_UNDEFINED(str);
	}
	catch (const exception& e)
	{
		cout << e.what() << endl;
	}
	
	return 0;
}
