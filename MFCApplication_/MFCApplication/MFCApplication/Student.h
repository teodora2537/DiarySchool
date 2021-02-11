#pragma once
#include<string>
using namespace std;
class Student
{
protected:

public:

	Student(int _classNum, string fName, string lName, string birthday);
	Student();
	string GetFirstName();
	void SetFirstName(string firstName);
	
	string GetLastName();
	void SetLastName(string lastName);

	string GetBirthday();
	void SetBirthday(string birthday);

	int GetClassNumber();
	void SetClassNumber(int classNumber);
	CString GetFullName();
	void SetFullName(CString _fullName);
};

