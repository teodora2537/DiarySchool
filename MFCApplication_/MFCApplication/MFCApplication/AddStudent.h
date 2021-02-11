#pragma once


// AddStudent dialog

class CAddStudent : public CDialogEx
{
	DECLARE_DYNAMIC(CAddStudent)

public:
	CAddStudent(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddStudent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedAddStudent();

	DECLARE_MESSAGE_MAP()

public:
	CString classNum;
	CString fn;
	CString ln;
	CString birthday;

	afx_msg void OnBnClickedOk();
};
