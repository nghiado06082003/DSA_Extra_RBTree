#ifndef _STUDENT_
#define _STUDENT_

#include "Main.h"

class Student {
public:
	int ID;
	string firstName;
	string lastName;
	string classID;
	double ProfesAvgTen;
	double ProfesAvgFour;
	int ProfesCreditNum;
	int passedSubject;
	double generalAvgTen;
	double generalAvgFour;
	int generalCreditNum;

	Student();
	Student(const Student& others);

	void operator = (const Student& others);

	bool operator < (const Student& others);
	bool operator > (const Student& others);
	bool operator == (const Student& others);

	bool operator < (int key);
	bool operator > (int key);
	bool operator == (int key);
};

ostream& operator << (ostream& out, const Student& s)
{
	out << "ID: " << s.ID << endl
		<< "FirstName: " << s.firstName << endl
		<< "LastName: " << s.lastName << endl
		<< "ProfesAvgTen: " << s.ProfesAvgTen << endl
		<< "ProfesAvgFour: " << s.ProfesAvgFour << endl
		<< "ProfesCreditNum: " << s.ProfesCreditNum << endl
		<< "PassedSubject: " << s.passedSubject << endl
		<< "GeneralAvgTen: " << s.generalAvgTen << endl
		<< "GeneralAvgFour: " << s.generalAvgFour << endl
		<< "GeneralCreditNum: " << s.generalCreditNum << endl;
	return out;
}

Student::Student()
{
	this->ID = 0;
	this->firstName = "";
	this->lastName = "";
	this->classID = "";
	this->ProfesAvgTen = 0;
	this->ProfesAvgFour = 0;
	this->ProfesCreditNum = 0;
	this->passedSubject = 0;
	this->generalAvgTen = 0;
	this->generalAvgFour = 0;
	this->generalCreditNum = 0;
}

Student::Student(const Student& others)
{
	this->ID = others.ID;
	this->firstName = others.firstName;
	this->lastName = others.lastName;
	this->classID = others.classID;
	this->ProfesAvgTen = others.ProfesAvgTen;
	this->ProfesAvgFour = others.ProfesAvgFour;
	this->ProfesCreditNum = others.ProfesCreditNum;
	this->passedSubject = others.passedSubject;
	this->generalAvgTen = others.generalAvgTen;
	this->generalAvgFour = others.generalAvgFour;
	this->generalCreditNum = others.generalCreditNum;
}

void Student::operator = (const Student& others)
{
	this->ID = others.ID;
	this->firstName = others.firstName;
	this->lastName = others.lastName;
	this->classID = others.classID;
	this->ProfesAvgTen = others.ProfesAvgTen;
	this->ProfesAvgFour = others.ProfesAvgFour;
	this->ProfesCreditNum = others.ProfesCreditNum;
	this->passedSubject = others.passedSubject;
	this->generalAvgTen = others.generalAvgTen;
	this->generalAvgFour = others.generalAvgFour;
	this->generalCreditNum = others.generalCreditNum;
}

bool Student::operator < (const Student& others)
{
	return (this->ID < others.ID);
}

bool Student::operator > (const Student& others)
{
	return (this->ID > others.ID);
}

bool Student::operator == (const Student& others)
{
	return (this->ID == others.ID);
}

bool Student::operator < (int key)
{
	return (this->ID < key);
}

bool Student::operator > (int key)
{
	return (this->ID > key);
}

bool Student::operator == (int key)
{
	return (this->ID == key);
}
#endif // !_STUDENT_
