#pragma once
#include <iostream>
#include <string>

using namespace std;
class CSubjectData
{

public:

	CSubjectData(int _roomNumber, CString _nameSubject, string _fNameTeacher, string _lNameTeacher);
	CSubjectData();

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

class CSubject {
public:
	CSubject();
	virtual ~CSubject();

public:
	bool AddSubject(CSubjectData& oSubject);
	bool EditSubject(const CSubjectData& oSubject);
	bool LoadSubject(const int nClassNumber, CSubjectData& oSubject);
	bool DeleteSubject(const int nClassNumber);

};

