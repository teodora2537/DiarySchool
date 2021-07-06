#pragma once
#include "Library.h"
#include <list>
#include "Student.h"

class CSubjectData
{
public:
	CSubjectData(int _idSubject, CString _subject, CString _fNameTeacher, CString _lNameTeacher);
	CSubjectData();

public://member
	int	m_iId;
	CString m_strSubject;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
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
	bool IsContainsSubject(CSubjectData& oSubject);
};