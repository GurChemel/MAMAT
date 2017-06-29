#include<iostream>

using namespace std;

class PointerCounter {
private:
	int count; // Reference count
public:
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
	// Constructor:
	MySharedPtr(T* ptr) : pData(ptr){
		Counter_ = new PointerCounter();
		Counter_->AddRef();
		cout << "Constructor. Counter is: " << Counter_->Get() << endl;
	};
	
	// Copy Constructor:
	MySharedPtr(MySharedPtr<T>& from) : pData(from.pData), Counter_(from.Counter_) {
		Counter_->AddRef();
		cout << "Copy Constructor. Counter is: " << Counter_->Get() << endl;
	};
	
	// Destructor:
	~MySharedPtr() { 
		if ((Counter_->Release()) == 0) {
			cout << "Deleted data. counter:" << Counter_->Get() << endl;
			delete pData;
			delete Counter_;
		};
		cout << "destructor" << endl;
	}
	
	T& operator* () { return *pData;}
	T* operator-> () { return pData;}
	T* get() { return pData;}
	
	// Assignment operator:
	MySharedPtr<T>& operator= (MySharedPtr<T>& from) {
		// Check if self assignment:
		if (this != &from) {
			if ((Counter_->Release()) == 0) {
				cout << "Assignment. Old counter is: " << Counter_->Get() << endl;
				delete pData;
				delete Counter_;
			};
	
			pData = from.pData;
			Counter_=from.Counter_;
			Counter_->AddRef();
			cout << "Assignment. Counter is: " << Counter_->Get() << endl;
		};
		return *this;
	}
	
	friend ostream& operator<<(ostream& ro, const MySharedPtr& Ptr){
		ro << (Ptr.pData);
		return ro;
	}
	
private:
	T* pData;
	PointerCounter* Counter_;

};

int main() {
	MySharedPtr<int> p1(new int);
	cout << "Added p1" << endl;
	MySharedPtr<int> p2(new int);
	cout << "Added p2" << endl;
	p2 = p1;
	cout << "p2 to p1" << endl;
	p1 = p1;
	cout << "p1 to p1" << endl;
	*p1 = 42;
	cout << "p1 to 42" << endl;
	cout << "P1: " << (*p1) << endl;
	cout << "P1 get(): " << (*(p1.get())) << endl;
	MySharedPtr<int> p3(p1);
	cout << "p3 to p1" << endl;
	cout << "P2: " << (*p2) << endl;
	cout << "P3: " << (*p3) << endl;
};
