#pragma once


// CAddSubject dialog

class CAddSubject : public CDialogEx
{
	DECLARE_DYNAMIC(CAddSubject)

public:
	CAddSubject(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddSubject();

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
	afx_msg void OnBnClickedOk();
};
