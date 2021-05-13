#pragma once
#include "afxdb.h"
//#include "afxdialogex.h"
using namespace std;
// CStudentTable dialog

class CStudentTable : public CDialogEx, public CRecordset
{
public:
	CStudentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentTable)

public:
	CStudentTable(CWnd* pParent = nullptr);   // standard constructor
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
	CString m_str_IdStudent;
	CString m_str_First_name;
	CString m_str_Last_name;
	COleDateTime m_oleDT_Birthday;
	int m_iCountStudent;
//public:
//
//#ifdef _DEBUG
//	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
//	virtual void AssertValid() const;
//	virtual void Dump(CDumpContext& dc) const;
//#endif
};