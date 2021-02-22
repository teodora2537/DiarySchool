#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
class CSubjectData
{

public:

	CSubjectData(int _roomNumber, CString _nameSubject, string _fNameTeacher, string _lNameTeacher);
	CSubjectData();

	int m_iRoomNumber;
	CString m_cstrNameSubject, m_cstrFullNameTeacher;
	string m_strFNameTeacher, m_strLNameTeacher;
	bool m_bIsUpdate = false;

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
	
	bool GetFlagIsUpdate();
	void SetFlagIsUpdate(bool _bIsUpdate);
};

class CSubject {
public:
	CSubject();
	virtual ~CSubject();

public:
	bool AddSubject(CSubjectData& oSubject);
	//bool EditSubject(const CSubjectData& oSubject);
	bool EditSubject(CSubjectData& oSubject);
	bool LoadSubject(const int nClassNumber, CSubjectData& oSubject);
	bool DeleteSubject(const int nClassNumber);
	map<int, vector<string>> PrintSubject();

	int m_iRoomNum;
	string m_strFName;
	string m_strLName;
	string m_strSubject;
	int m_iCount = 0;
	string m_strText;
	string m_strToken;
	size_t m_sizeTPosition;
	bool m_bIsFind = false;
	map<int, vector<string>> m_mapSubjects;
};

