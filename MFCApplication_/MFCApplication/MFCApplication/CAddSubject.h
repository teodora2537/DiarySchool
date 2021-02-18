#pragma once


// CAddSubject dialog

class CAddSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSubjectDlg)

public:
	CAddSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddSubjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SUBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_cstrRoomNum;
	CString m_cstrSubject;
	CString m_cstrFnTeacher;
	CString m_cstrLnTeacher;

	CEdit m_edb;


	afx_msg void OnBnClickedOk();
};
