#ifndef _MY_SHARED_PTR_H_
#define _MY_SHARED_PTR_H_

#include<iostream>

using namespace std;

class PointerCounter {
private:
	int count; // Reference count
public:
	PointerCounter() { count = 0 ;};
	// Increment the reference count
	void AddRef() { count++;}
	// Return the reference count.
	int Get() {	return count;}
	// Decrement the reference count and
	// return the reference count.
	int Release() { return --count;}
};

template<class T>
class MySharedPtr {
public:
	// Empty Constructor:
	MySharedPtr() : pData(NULL) {
		Counter_ = new PointerCounter();
		//cout << "Empty Constructor. Counter is: " << Counter_->Get() << endl;
	};
	
	// Constructor:
	MySharedPtr(T* ptr) : pData(ptr) {
		Counter_ = new PointerCounter();
		Counter_->AddRef();
		//cout << "Constructor. Counter is: " << Counter_->Get() << endl;
	};

	// Copy Constructor:
	MySharedPtr(const MySharedPtr<T>& from) : pData(from.pData), Counter_(from.Counter_) {
		Counter_->AddRef();
		//cout << "Copy Constructor. Counter is: " << Counter_->Get() << endl;
	};

	// Destructor:
	~MySharedPtr() {
        if ((Counter_->Release()) == 0) {
            delete pData;
			delete Counter_;
		};
		//cout << "destructor" << endl;
	}

	// Derefrancing overloading:
	T& operator* () { return *pData; }
	T* operator-> () { return pData; }
	T* get() { return pData; }

	// Assignment operator:
	MySharedPtr<T>& operator= (const MySharedPtr<T>& from) {
		// Check if self assignment:
		if (this != &from) {
            if ((Counter_->Release()) == 0) {
				//cout << "Assignment. Old counter is: " << Counter_->Get() << endl;
				delete pData;
				delete Counter_;
			};

			pData = from.pData;
			Counter_ = from.Counter_;
			Counter_->AddRef();
			//cout << "Assignment. Counter is: " << Counter_->Get() << endl;
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
