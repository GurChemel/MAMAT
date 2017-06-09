
#ifndef _Person_
#define _Person_

class Person {
	public:
	//constructor & default constructor
	Person(int personID = 0 ,const char *personName = "Jane Doh");
	//class constant methods
	int 	getID() const;
	char*	getName() const;

	//class setting methods

	//virtual methods

	//destructor
	virtual ~Person();

	protected:
	const int 		personID_;
	const char*		personName_;

};

#endif //End Of _Person_
