#pragma once
#include <list>
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

	CStudentData(int _classNum, CString fName, CString lName, COleDateTime birthday);
	CStudentData();

	CString m_strFirstName;
	CString m_strLastName;
	COleDateTime m_strBirthday;
	CString m_strFullName;
	int m_iClassNumber;
};

class CStudent
{
public:
	CStudent();
	BOOL InitInstance();
	virtual ~CStudent();

public:
	bool AddStudent(CStudentData& oStudent);
	bool EditStudent(const CStudentData& oStudent);
	bool LoadStudent(const int nClassNumber, CStudentData& oStudent);
	bool DeleteStudent(const int nClassNumber);
	void PrintStudent_(list<STUDENT>& m_listStudent);


	void AvgScoreBySubject(list<REFERENCE>& m_listReference);
	void AvgScoreByAllSubject(list<REFERENCE>& m_listReference);
	void ExcellentStud(list<REFERENCE>& m_listReference);
	void PeopleHaveBirthday(list<REFERENCE>& m_listReference);
	void remedialExaminationBySub(list<REFERENCE>& m_listReference);
	void remedialExaminationByMoreSub(list<REFERENCE>& m_listReference);
	int CountStudent();
};
