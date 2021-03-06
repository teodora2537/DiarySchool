#pragma once


// CUpdateSubject dialog

class CUpdateSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateSubjectDlg)

public:
	CUpdateSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateSubjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SUBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString roomNum;
	CString subject;
	CString fn;
	CString ln;
	afx_msg void OnBnClickedOk();
};
