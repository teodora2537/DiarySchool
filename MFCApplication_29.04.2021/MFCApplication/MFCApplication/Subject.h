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
	CSubjectData(int _roomNumber, CString _nameSubject, CString _fNameTeacher, CString _lNameTeacher);
	CSubjectData();

	int	m_iRoomNumber;
	CString m_strNameSubject;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
	CString m_strFullNameTeacher;
};


class CSubject{
public:
	CSubject();
	virtual ~CSubject();
public:

	bool AddSubject(const CSubjectData& oSubjectData);
	bool EditSubject(const CSubjectData& oSubject);
	bool LoadSubject(const int nRoomId, CSubjectData& oSubject);
	bool DeleteSubject(const int nRoom);
	void PrintSub(list<SUBJECT>& listSub);
};
