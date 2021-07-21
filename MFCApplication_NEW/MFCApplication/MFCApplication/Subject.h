#pragma once
#include "Library.h"
#include <list>
#include "Student.h"

class CSubjectData
{
public:
	CSubjectData(int _idSubject, CString _subject, CString _firstNameTeacher, CString _lastNameTeacher);
	CSubjectData();

public://member
	int	m_iId;
	CString m_strSubject;
	CString m_strFirstNameTeacher;
	CString m_strLastNameTeacher;
};

class CSubject{
public:
	CSubject();
	virtual ~CSubject();

public: //methods
	bool AddSubject(CSubjectData& oSubjectData);
	bool EditSubject(CSubjectData& oSubject);
	bool DeleteSubject(const int nRoom);
	bool LoadSubject(const int nRoomId, CSubjectData& oSubject);
	void PrintSubject(list<CSubjectData>& listSub);

	void GetLastId(CSubjectData& oSubject);
	//bool IsContainsSubject(CSubjectData& oSubject);
};