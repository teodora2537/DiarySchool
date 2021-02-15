#pragma once
#include "Library.h"
#include "Student.h"


// AddStudent dialog

class CAddStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddStudentDlg)

public:
	CAddStudentDlg(CStudentData& oStudent, const DialogMode eMode);   // standard constructor
	virtual ~CAddStudentDlg();

public:

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_STUDENT };
#endif

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedAddStudent();

	DECLARE_MESSAGE_MAP()

public:
	CString m_strclassNum;
	CString fn;
	CString ln;
	CString birthday;

	CEdit m_edb;

	CStudentData& m_oStudent;
	
	DialogMode m_eMode;

	afx_msg void OnBnClickedOk();
};
