#pragma once
#include <map>
#include <list>
#include <string>
#include "Score.h"
#include "Library.h"
#include "CStudentTable.h"
#include "CParentTable.h"
using namespace std;

#define DEF_SCORE_NAME_LEN 100
#define DEF_LEN 100

struct STUDENT {
	int iId;
	char szName[DEF_SCORE_NAME_LEN + 1]; // sz- char array ->name student
	char szDate[9 + 1];//DBTIMESTAMP ->date of score
	char szEmail[DEF_LEN + 1];
	char szPhoneNumber[20 + 1];
	char szEGN[20 + 1];
	char szCity[70 + 1];
	char szPostCode[10 + 1];
	char szNeighborhood[70 + 1];
	char szAddress[1000 + 1]; //max size

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
public:
	CStudentData();

	int m_iId;
	CString m_strStudent_FirstName;
	CString m_strStudent_LastName;
	COleDateTime m_oleDT_Birthday;
	CString m_strStudent_Email;
	CString m_strStudent_PhoneNumber;
	CString m_strStudent_Egn;
	CString m_strStudent_City;
	CString m_strStudent_PostCode;
	CString m_strStudent_Neighborhood;
	CString m_strStudent_Address;

	list<CStudentData> m_objList;
};

class CStudent
{
public:
	CStudent();
	virtual ~CStudent();

public:
	bool AddStudent(CStudentData& oStudent);
	bool EditStudent(CStudentData& oStudent);
	bool LoadStudent(const int nClassNumber, CStudentData& oStudent);
	bool DeleteStudent(const int nClassNumber);
	void PrintStudent_(list<STUDENT>& listStudent);

	void FillTables(CStudentTable& oStudentTable, CParentTable& oParentTable, list<CStudentData>& objList);

	void AvgScoreBySubject(list<REFERENCE>& listReference);
	void AvgScoreByAllSubject(list<REFERENCE>& listReference);
	void ExcellentStud(list<REFERENCE>& listReference);
	void PeopleHaveBirthday(list<REFERENCE>& listReference);
	void RemedialExaminationBySub(list<REFERENCE>& listReference);
	void RemedialExaminationByMoreSub(list<REFERENCE>& listReference);
	void GetLastId(CStudentData& oStudent);
};