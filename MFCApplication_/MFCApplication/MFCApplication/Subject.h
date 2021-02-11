#pragma once
#include <iostream>
#include <string>

using namespace std;
class Subject
{

public:

	Subject(int _roomNumber, CString _nameSubject, string _fNameTeacher, string _lNameTeacher);
	Subject();

	string GetFirstNameTeacher();
	void SetFirstNameTeacher(string _firstNameTeacher);

	string GetLastNameTeacher();
	void SetLastNameTeacher(string _lastNameTeacher);

	CString GetNameSubject();
	void SetNameSubject(CString _nameSubject);

	int GetRoomNumber();
	void SetRoomNumber(int _roomNumber);
	
	CString GetFullNameTeacher();
	void SetFullNameTeacher(CString _fullNameTeacher);
};

