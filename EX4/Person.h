
#ifndef _Person_
#define _Person_

class Person {
	public:
	//constructor & default constructor
	Person(int personID,const char *personName);
	//class constant methods
	int 	getID() const;
	char*	getName() const;

	//class setting methods

	//virtual methods

	//destructor
	virtual ~Person();

	protected:
	const int 		personID_;
	char*		personName_;

};

#endif //End Of _Person_
