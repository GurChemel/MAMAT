#include<iostream>

using namespace std;

template<class T>
class MySharedPtr {
public:
	// Constructor:
	MySharedPtr(T* ptr) : pData(ptr), Counter_(1) {};
	// Copy Constructor:
	MySharedPtr(MySharedPtr<T>& from) : pData(from.pData), Counter_(++from.Counter_) {};
	~MySharedPtr() { 
		if ((--Counter_) == 0) {
			delete pData;
		};
	};
	//class get() {return Ptr};
	MySharedPtr& operator*() { return *pData;};
	MySharedPtr* operator->() { return pData ;};

	// Assignment operator:
	MySharedPtr<T>& operator=(MySharedPtr<T>& from) {
		// Check if self assignment:
		if (this != &from) {
			if ((--Counter_) == 0) {
				delete pData;
			};

			pData = from.pData;
			Counter_ = (++from.Counter_);
		};
		return *this;
	};

private:
	T* pData;
	int Counter_;

};

int main() {
	MySharedPtr<int> p1(new int);
	*p1 = 42;
	cout << (*p1) << endl;
	cout << (*(p1-get())) << endl;
	MySharedPtr<int> p1(p2);
};
