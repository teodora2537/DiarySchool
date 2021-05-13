#pragma once
#include "Library.h"
#include "Student.h"
#include "CTabReference.h"
using namespace std;

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	//CStudentDlg();   // standard constructor
	CStudentDlg(CStudentData& oSubject, const DialogMode eMode);   // standard constructor
	virtual ~CStudentDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog() override;
	COleDateTime time;

	DECLARE_MESSAGE_MAP()
public:
	CString m_strClassNum;
	CString m_strFn;
	CString m_strLn;
	CString m_strBirthday;
	
	CDateTimeCtrl m_dtCtrlBirthday;
	COleDateTime m_oleDT;

	BOOL ValidateData();
	CStudentData& m_oStudent;
	DialogMode m_eMode;
	afx_msg void OnBnClickedOk();
};