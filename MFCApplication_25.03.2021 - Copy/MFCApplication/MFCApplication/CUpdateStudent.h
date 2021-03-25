#pragma once
#include "Student.h"
#include "Library.h"

// CUpdateStudent dialog

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CStudentData& oSubject, const DialogMode eMode);   // standard constructor
	virtual ~CStudentDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog() override;

	DECLARE_MESSAGE_MAP()

public:
	CString m_strClassNum;
	CString m_strFn;
	CString m_strLn;
	CString m_strBirthday;
	CDateTimeCtrl m_dtCtrlBirthday;

	CString m_strStaticClassNum;
	CString m_strStaticFn;
	CString m_strStaticLn;
	CString m_strStaticBirthday;
	BOOL ValidateData();
	CStudentData& m_oStudent;
	DialogMode m_eMode;
	/*
	COleDateTime oleDate = COleDateTime::GetCurrentTime();
	CString currentDate = oleDate.Format(_T("%m/%d/%Y"));
	*/
	afx_msg void OnBnClickedOk();
};
