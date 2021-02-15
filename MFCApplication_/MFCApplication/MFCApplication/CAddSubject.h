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

	afx_msg void OnBnClickedCAddSubject();

	DECLARE_MESSAGE_MAP()

public:
	CString roomNum;
	CString subject;
	CString fn;
	CString ln;

	CEdit m_edb;


	afx_msg void OnBnClickedOk();
};
