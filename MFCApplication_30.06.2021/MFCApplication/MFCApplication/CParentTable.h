#pragma once
#include "afxdb.h"
#include "CParent.h"


struct PARENT {
	int  iId;
	int  iStudentID;
	char szName[100 + 1]; // sz- char array ->name student
	char sz_First_Name[50 + 1];
	char sz_Last_Name[50 + 1];
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


class CParentTable : public CRecordset
{
public:
	CParentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CParentTable)

public:
	virtual ~CParentTable();

protected:
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();

public: //member
	int m_iId;
	int m_iIdStudent;
	CString m_str_first_name;
	CString m_str_last_name;
	CString m_str_phone_number;
	CString m_str_email;
	CString m_str_city;
	CString m_str_post_code;
	CString m_str_neighborhood;
	CString m_str_address;

public: //methods
	void LoadParent(CParentData& oParent);
	void Add_Edit_Parent(PARENT& oParent);
	bool IsExist(CParentData& oParent);
};