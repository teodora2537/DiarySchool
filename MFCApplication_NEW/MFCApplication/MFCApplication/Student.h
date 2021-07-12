#pragma once
#include <map>
#include <list>
#include <string>
#include "Score.h"
#include "Library.h"
#include "CParent.h"

struct REFERENCE {
	//int iId;
	char szClm0[100 + 1];
	char szClm1[100 + 1];
	char szClm2[100 + 1];
	char szClm3[100 + 1];

	REFERENCE()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CStudentData
{
public:
	CStudentData();
	CStudentData(int iParentId, int iStudentId, CString strFirstName, CString strLastName, COleDateTime oleDTBirthday,
				 CString strEmail, CString strPhoneNumber, CString strEgn, CString strCity, 
				 CString strPostCode, CString strNeighborhood, CString strAddress);
	
public: //member
	int m_iStudentId;
	int m_iParentId;
	CString m_strFirstName;
	CString m_strLastName;
	CString m_strName;
	COleDateTime m_oleDTBirthday;
	CString m_strEmail;
	CString m_strPhoneNumber;
	CString m_strEgn;
	CString m_strCity;
	CString m_strPostCode;
	CString m_strNeighborhood;
	CString m_strAddress;
	list<CParentData> m_arrParents;

	//list<pair<int, int>> m_arrParentState;
};

class CStudent
{
public:
	CStudent();
	virtual ~CStudent();

public: //methods
	bool AddStudent(CStudentData& oStudent);
	bool EditStudent(CStudentData& oStudent);
	bool LoadStudent(const int nIdStudent, CStudentData& oStudent);
	bool DeleteStudent(const int nIdStudent);
	void PrintStudent(list<CStudentData>& listStudent);

public://reference methods
	void AvgScoreBySubject(list<REFERENCE>& listReference);
	void AvgScoreByAllSubject(list<REFERENCE>& listReference);
	void ExcellentStud(list<REFERENCE>& listReference);
	void PeopleHaveBirthday(list<REFERENCE>& listReference);
	void RemedialExaminationBySub(list<REFERENCE>& listReference);
	void RemedialExaminationByMoreSub(list<REFERENCE>& listReference);
	//get
	bool GetLastAddedID(CString& nIdStudent);
	void GetLastId(int& lastID);
};