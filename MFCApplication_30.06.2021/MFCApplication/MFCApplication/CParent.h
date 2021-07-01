#pragma once
#include <list>
#include "Library.h"
using namespace std;

struct PARENT {
	int iId;
	int iStudentID;
	char szName[100 + 1]; // sz- char array ->name student
	char sz_First_Name[50 + 1]; // sz- char array ->name student
	char sz_Last_Name[50 + 1]; // sz- char array ->name student
	char szEmail[100 + 1];
	char szPhoneNumber[20 + 1];
	char szCity[70 + 1];
	char szPostCode[10 + 1];
	char szNeighborhood[70 + 1];
	char szAddress[1000 + 1]; //max size
	char szRecordMode[20];

	PARENT()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CParentData 
{
public:
	CParentData();
	CParentData(int iParentId, int iStudentId, CString  strFirstName, CString strLastName,  CString strPhoneNumber,
				CString strEmail, CString strCity, CString strPostCode, CString strNeighborhood, 
				CString strAddress);

	int m_iParentId;
	int m_iStudentId;
	CString m_strFirstName;
	CString m_strLastName;
	CString m_strEmail;
	CString m_strPhoneNumber;
	CString m_strCity;
	CString m_strPostCode;
	CString m_strNeighborhood;
	CString m_strAddress;
	RecordMode m_eRecordMode;
};

class CParent
{
public:
	bool Func(int nIdStudent, list<CParentData>& arrParents);
	bool AddParent(CParentData& oParent);
	bool EditParent(CParentData& oParent);
	bool LoadParent(CParentData& oParent);
	bool DeleteParent(const int nId);
	bool DeleteOneParent(const int nIdParent);
	bool PrintParent(const int& nIdParent, list<PARENT>& lParent);
	bool PrintParentByStudent(const int& nIdStudent, list<CParentData>& lParent);
	list<PARENT> listStudents;
};