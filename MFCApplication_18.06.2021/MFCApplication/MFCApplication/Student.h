#pragma once
#include <map>
#include <list>
#include <string>
#include "Score.h"
#include "Library.h"
#include "CStudentTable.h"
#include "CParentTable.h"
#include "CParent.h"
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
	CStudentData(int iStudentId, int iParentId, CString strFirstName, CString strLastName, COleDateTime oleDTBirthday,
				 CString strEmail, CString strPhoneNumber, CString strEgn, CString strCity, 
				 CString strPostCode, CString strNeighborhood, CString strAddress);
	int m_iStudentId;
	int m_iParentId;
	CString m_strFirstName;
	CString m_strLastName;
	COleDateTime m_oleDTBirthday;
	CString m_strEmail;
	CString m_strPhoneNumber;
	CString m_strEgn;
	CString m_strCity;
	CString m_strPostCode;
	CString m_strNeighborhood;
	CString m_strAddress;

	list<CParentData> m_arrParents;
};

class CStudent
{
public:
	CStudent();
	virtual ~CStudent();

	bool isStudentExist(CString strEgn);

public:
	bool AddStudent(CStudentData& oStudent);// , list<CParentData>& arrParents);
	bool EditStudent(CStudentData& oStudent);// , list<CParentData>& arrParents);
	bool LoadStudent(const int nClassNumber, CStudentData& oStudent);
	bool DeleteStudent(const int nClassNumber);
	void PrintStudent_(list<STUDENT>& listStudent);

	void AvgScoreBySubject(list<REFERENCE>& listReference);
	void AvgScoreByAllSubject(list<REFERENCE>& listReference);
	void ExcellentStud(list<REFERENCE>& listReference);
	void PeopleHaveBirthday(list<REFERENCE>& listReference);
	void RemedialExaminationBySub(list<REFERENCE>& listReference);
	void RemedialExaminationByMoreSub(list<REFERENCE>& listReference);
	void GetLastId(int& lastID);
};