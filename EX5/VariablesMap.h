#ifndef _VARIABLES_MAP_H_
#define _VARIABLES_MAP_H_

#include<iostream>
#include<vector>
#include<map>
#include"MySharedPtr.h"
#include"Variable.h"
#include"Scalar.h"
#include"Matrix.h"

using namespace std;


#define VALID_VAR_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_"


class VariablesMap {
public:
	VariablesMap() {
        Saved_ = "";
        tmp_counter = 0;
	};

	void SetSavedName(const string& newSavedName) {
        Saved_ = newSavedName;
        //valMap_[Saved_];
	}
	
	string GetTmpVariable();
	void ClearTmpVars();
	VarPtr& operator[](const string& x);
	VarPtr& at(const string& x);
	void erase(const string& x);


private:
	map<string, VarPtr> valMap_;
    map<int, string> tmpNamesMap_;
    int tmp_counter;
	string tmpName_;
	string Saved_;
};

bool legal_name(const string& x);
void gen_random(string& s);

#endif // _VARIABLES_MAP_H_
