#pragma once


// CUpdateStudent dialog

class CUpdateStudent : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateStudent)

public:
	CUpdateStudent(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateStudent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString classNum;
	CString fn;
	CString ln;
	CString birthday;
	afx_msg void OnBnClickedOk();
};
