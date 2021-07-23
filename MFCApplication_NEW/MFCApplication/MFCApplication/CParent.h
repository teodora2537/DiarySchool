#pragma once
#include <list>
#include "Library.h"

class CParentData 
{
public: //Constructories
	CParentData();

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
	
	//Functions ADD/EDIT/DELETE
private:
	bool AddParent(CParentData& oParent);
	bool EditParent(CParentData& oParent);
	bool DeleteOneParent(const int nIdParent);
	bool DeleteParents(const int nId);
};