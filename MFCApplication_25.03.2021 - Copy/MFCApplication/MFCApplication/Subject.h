#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>

using namespace std;
class CSubjectData
{

public:

	CSubjectData(int _roomNumber, CString _nameSubject, CString _fNameTeacher, CString _lNameTeacher);
	CSubjectData();

	int m_iRoomNumber = 0;
	CString m_strNameSubject;
	CString m_strFullNameTeacher;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
	bool m_bIsUpdate = false;
};

class CSubject {
public:
	CSubject();
	virtual ~CSubject();

public:
	bool AddSubject(const CSubjectData& oSubjectData);
	bool EditSubject(const CSubjectData& oSubject);
	bool LoadSubject(const int nRoomId, CSubjectData& oSubject);
	bool DeleteSubject(const int nClassNumber);
	void PrintSubject(map<int, vector<CString>>& m_mapSubjects);
};

