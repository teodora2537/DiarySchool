#pragma once
#include "afxdb.h"
using namespace std;

class CParentTable : public CDialogEx, public CRecordset
{
public:
	CParentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CParentTable)

public:
	virtual ~CParentTable();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_STUDENT };
#endif

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
	DECLARE_MESSAGE_MAP()

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
	afx_msg void OnDtnDatetimechangeDatetimepicker1(NMHDR* pNMHDR, LRESULT* pResult);
};