#include"ScriptExceptions.h"
#include<stdexcept>
#include<string>
#include"VariablesMap.h"

using namespace std;

// ###############################################
// #
// #	Temp vaariable handeling:
// #
// ###############################################

// Creates a random string from 10 VALID_VAR_CHARS.
void gen_random(string& s) {
    static const char alphanum[] = VALID_VAR_CHARS;
    char char_array[10];
    for (int i = 0; i < 10; ++i) {
        char_array[i] = alphanum[rand() % (sizeof(VALID_VAR_CHARS) - 1)];
    }
    char_array[10]=0;
    s = string(char_array);
}

string VariablesMap::GetTmpVariable(){
	gen_random(tmpName_);
    // Make sure the name isn't taken and isn't saved:
    while ((valMap_.count(tmpName_) != 0) && (tmpName_ != Saved_)) {
        gen_random(tmpName_);
	}
    tmpNamesMap_[tmp_counter]=tmpName_;
    tmp_counter++;
	return tmpName_;
}

void VariablesMap::ClearTmpVars() {
	int i = 0;
    string to_delete;
	while ( i < tmp_counter) {
        to_delete=tmpNamesMap_[i];
		(*this).erase(tmpNamesMap_[i]);
		i++;
	}
}

// ###############################################
// #
// #	Map Manipulating functions:
// #
// ###############################################

VarPtr& VariablesMap::operator[](const string& x) {
    if ( legal_name(x) == false ) { throw INVALID_VAR_NAME(x); };
	if (valMap_.count(x) == 0) { valMap_.insert(std::make_pair(x,VarPtr(new Scalar(0)))) ;};
    return valMap_[x];
}

VarPtr& VariablesMap::at(const string& x) {
    std::out_of_range oor("out_of_range"); // Created for throwing if neeeded.
	if (valMap_.count(x) == 0) { throw oor; };
	return valMap_.at(x);
}

void VariablesMap::erase(const string& x) {
	valMap_.erase(x);
}

bool legal_name(const string& x) {
	if (x.length()==0) {return false;};
    std::string::const_iterator iter;
	string valid_chars = string(VALID_VAR_CHARS);
	int found_pos;
	// Iterate over the given name:
    for (iter = x.begin(); iter != x.end(); ++iter) {
		// Check if the current char is in the Valid Chars. if not then return false:
        found_pos = valid_chars.find(*iter);
        if (found_pos == -1) { return false; };
	}
	return true;
}

