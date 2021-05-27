#pragma once
#include <map>
#include <list>
#include <string>
#include "Score.h"
#include "Library.h"
using namespace std;

#define DEF_SCORE_NAME_LEN 100

struct STUDENT {
	int iId;
	char szName[DEF_SCORE_NAME_LEN + 1]; // sz- char array ->name student
	char szDate[9 + 1];//DBTIMESTAMP ->date of score

	STUDENT()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

struct REFERENCE {
	int iId;
	char szClm0[DEF_SCORE_NAME_LEN + 1];
	char szClm1[DEF_SCORE_NAME_LEN + 1];
	char szClm2[DEF_SCORE_NAME_LEN + 1];
	char szClm3[DEF_SCORE_NAME_LEN + 1];

	REFERENCE()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CStudentData
{
protected:

public:
	CStudentData(int _iId, CString _strFirstName, CString _strLastName, COleDateTime _oleDTBirthday);
	CStudentData();

	CString m_strFirstName;
	CString m_strLastName;
	COleDateTime m_oleDT_Birthday;
	int m_iId;
};

class CStudent
{
public:
	CStudent();
	virtual ~CStudent();

public:
	bool IsContainsStudent(CStudentData& oStudent);
	bool AddStudent(CStudentData& oStudent);
	bool EditStudent(CStudentData& oStudent);
	bool LoadStudent(const int nClassNumber, CStudentData& oStudent);
	bool DeleteStudent(const int nClassNumber);
	void PrintStudent_(list<STUDENT>& listStudent);

	void AvgScoreBySubject(list<REFERENCE>& listReference);
	void AvgScoreByAllSubject(list<REFERENCE>& listReference);
	void ExcellentStud(list<REFERENCE>& listReference);
	void PeopleHaveBirthday(list<REFERENCE>& listReference);
	void RemedialExaminationBySub(list<REFERENCE>& listReference);
	void RemedialExaminationByMoreSub(list<REFERENCE>& listReference);
	void GetLastId(CStudentData& oStudent);
};