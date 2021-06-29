#pragma once
#include "afxdb.h"
#include "CParent.h"
using namespace std;

class CParentTable : public CRecordset
{
public:
	CParentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CParentTable)

public:
	virtual ~CParentTable();

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

public:
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
	void LoadParent(CParentData& oParent);
	void AddParent(CParentData& oParent);
	void EditParent(CParentData& oParent);
	bool IsExist(CParentData& oParent);
};