#pragma once
#include <list>
#include "Library.h"

class CParentData 
{
public: //Constructories
	CParentData();
	CParentData(int iParentId, int iStudentId, CString  strFirstName, CString strLastName,  CString strPhoneNumber,
				CString strEmail, CString strCity, CString strPostCode, CString strNeighborhood, 
				CString strAddress);

	
public: //member
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

//Functions
public:
	bool Func(int nIdStudent, list<CParentData>& arrParents);
	bool PrintParentByStudent(const int& nIdStudent, list<CParentData>& lParent);
	bool LoadParent(CParentData& oParent);
	bool DeleteParents(const int nId);
	
//Functions
private:
	bool AddParent(CParentData& oParent);
	bool EditParent(CParentData& oParent);
	bool DeleteOneParent(const int nIdParent);
};