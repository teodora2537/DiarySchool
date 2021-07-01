#pragma once
#include <list>
#include "Library.h"
using namespace std;

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
	//bool PrintParent(const int& nIdParent, list<PARENT>& lParent);
	bool PrintParentByStudent(const int& nIdStudent, list<CParentData>& lParent);
	list<CParentData> m_listStudents;
};