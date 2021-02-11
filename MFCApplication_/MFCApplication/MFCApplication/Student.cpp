#include "pch.h"
#include "Student.h"
#include <string>
using namespace std;

	string firstName;
	string lastName;
	string birthday;
	CString fullName;
	int classNumber;
	int status;

	Student::Student(int _classNum, string _fName, string _lName, string _birthday)
	{
		classNumber = _classNum;
		firstName = _fName;
		lastName = _lName;
		birthday = _birthday;
	}

	Student::Student()
	{
	}

	string Student::GetFirstName() {
		return firstName;
	}
	void Student::SetFirstName(string _firstName) {
		firstName = _firstName;
	}

	string Student::GetLastName() {
		return lastName;
	}
	void Student::SetLastName(string _lastName) {
		lastName = _lastName;
	}

	string Student::GetBirthday() {
		return birthday;
	}
	void Student::SetBirthday(string _birthday) {
		birthday = _birthday;
	}

	int Student::GetClassNumber() {
		return classNumber;
	}
	void Student::SetClassNumber(int _classNumber) {
		classNumber = _classNumber;
	}
	CString Student::GetFullName() {
		return fullName;
	}
	void Student::SetFullName(CString _fullName) {
		fullName = _fullName;
	}