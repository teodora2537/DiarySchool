#pragma once
#include "Subject.h"
#include "Library.h"


// CAddSubject dialog

class CAddSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSubjectDlg)

public:
	//CAddSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	CAddSubjectDlg(CSubjectData& oSubject, const DialogMode m_eModeAddSub);   // standard constructor
	virtual ~CAddSubjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SUBJECT };
#endif

protected:
	virtual BOOL OnInitDialog();

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_strRoomNum;
	CString m_strSubject;
	CString m_strFnTeacher;
	CString m_strLnTeacher;

	CEdit m_eRoomNum;
	DialogMode m_eModeAddSub;
	CSubjectData m_oSubject;

	afx_msg
		afx_msg	BOOL ValidateData();
	void OnBnClickedOk();
};
