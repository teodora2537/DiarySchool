#pragma once


// CUpdateStudent dialog

class CUpdateStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateStudentDlg)

public:
	CUpdateStudentDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateStudentDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_cstrClassNum;
	CString m_cstrFn;
	CString m_cstrLn;
	CString m_cstrBirthday;

	afx_msg void OnBnClickedOk();
};
