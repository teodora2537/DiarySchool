#pragma once
#include <list>
using namespace std;

struct PARENT {
	int iId;
	int iStudentID;
	char szName[100 + 1]; // sz- char array ->name student
	char szEmail[100 + 1];
	char szPhoneNumber[20 + 1];
	char szCity[70 + 1];
	char szPostCode[10 + 1];
	char szNeighborhood[70 + 1];
	char szAddress[1000 + 1]; //max size

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
};

class CParent
{
public:
	bool AddParent(list<CParentData>& m_arrParents);
	bool EditParent(list<CParentData>& m_arrParents);
	bool LoadParent(const int nId, CParentData& oParent);
	bool DeleteParent(const int nId);
	bool PrintParent(const int& nIdParent, list<PARENT>& lParent);
	bool PrintParent_(const int& nIdStudent, list<CParentData>& lParent);
	list<PARENT> listStudents;
};