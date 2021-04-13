#pragma once
#include <list>
#include "CListMethods.h"
#include "Library.h"
using namespace std;

class CSubjectData
{

public:
	CSubjectData(int _roomNumber, CString _nameSubject, CString _fNameTeacher, CString _lNameTeacher);
	CSubjectData();

	int m_iRoomNumber;
	CString m_strNameSubject;
	CString m_strFullNameTeacher;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
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
	void PrintSub(list<SubStruct>& listSub);
};

