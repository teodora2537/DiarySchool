#pragma once
#include <list>
#include "Library.h"
using namespace std;


#define DEF_SUBJECT_NAME_LEN 100
#define DEF_SUBJECT_TEACHER_NAME_LEN 100

struct SUBJECT {
	int iId;
	char szSubject[DEF_SUBJECT_NAME_LEN + 1];
	char szTeacher[DEF_SUBJECT_TEACHER_NAME_LEN + 1];

	SUBJECT()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CSubjectData
{
public:
	CSubjectData(int _idSubject, CString _subject, CString _fNameTeacher, CString _lNameTeacher);
	CSubjectData();

	int	m_iId;
	CString m_strSubject;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;

};

class CSubject{
public:
	CSubject();
	virtual ~CSubject();

public:
	bool IsContainsSubject(CSubjectData& oSubject);
	bool AddSubject(CSubjectData& oSubjectData);
	bool EditSubject(CSubjectData& oSubject);
	bool LoadSubject(const int nRoomId, CSubjectData& oSubject);
	bool DeleteSubject(const int nRoom);
	void PrintSub(list<SUBJECT>& listSub);
	void GetLastId(CSubjectData& oSubject);
};