#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

#include<iostream>

using namespace std;

class PointerCounter {
public:
    // Constructor:
	PointerCounter() { count = 0 ;};
	
	void AddRef() { count++;}
	int Get() {	return count;}
	int Release() { return --count;}
private:
	int count; // Reference count
};

template<class T>
class MySharedPtr {
public:
	// Empty Constructor:
	MySharedPtr() : pData(NULL) {
		Counter_ = NULL;
	};
	
	// Constructor:
	MySharedPtr(T* ptr) : pData(ptr) {
		Counter_ = new PointerCounter();
		Counter_->AddRef();
	};

	// Copy Constructor:
	MySharedPtr(const MySharedPtr<T>& from) : pData(from.pData), Counter_(from.Counter_) {
		Counter_->AddRef();
	};

	// Destructor:
	~MySharedPtr() {
        if (Counter_ != NULL) {
            if ((Counter_->Release()) == 0) {
                delete pData;
                delete Counter_;
            };
        };
	}

	// Derefrancing overloading:
	T& operator* () { return *pData; }
	T* operator-> () { return pData; }
	T* get() { return pData; }

	// Assignment operator:
	MySharedPtr<T>& operator= (const MySharedPtr<T>& from) {
		// Check if self assignment:
		if (this != &from) {
            if (Counter_ != NULL) {
                if ((Counter_->Release()) == 0) {
                    delete pData;
                    delete Counter_;
                };
			};

			pData = from.pData;
			Counter_ = from.Counter_;
			Counter_->AddRef();
		};
		return *this;
	}

	// Print operator:
	friend ostream& operator<<(ostream& ro, const MySharedPtr<T>& obj) {
		obj.pData->Print(ro);
		return ro;
	}

private:
	T* pData;
	PointerCounter* Counter_;

};

#endif // _MY_SHARED_PTR_H_
