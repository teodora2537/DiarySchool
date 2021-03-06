#pragma once
#include "afxdb.h"

using namespace std;

class CStudentTable : public CDialogEx, public CRecordset
{
public:
	CStudentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentTable)

public:
	virtual ~CStudentTable();

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
	CString m_str_First_name;
	CString m_str_Last_name;
	COleDateTime m_oleDT_Birthday;
	CString m_str_email; 
	CString m_str_phone_number;
	CString m_str_egn;
	CString m_str_city;
	CString m_str_post_code;
	CString m_str_neighborhood;
	CString m_str_address;
	//int m_iCountStudent;
};	