#pragma once
#include "afxdb.h"
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

public:
	int m_iClassNum;
	CString m_strFn;
	CString m_strLn;
	CDateTimeCtrl m_dtCtrlBirthday;
	COleDateTime time;

public:
	virtual void DoFieldExchange(CFieldExchange* pFX);
};
