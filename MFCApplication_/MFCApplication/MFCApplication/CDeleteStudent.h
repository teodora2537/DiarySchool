#pragma once
// CDeleteStudent dialog

class CDeleteStudent : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteStudent)

public:
	CDeleteStudent(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDeleteStudent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//afx_msg void OnBnClickedDeleteStudent();
	DECLARE_MESSAGE_MAP()

public:
	CString classNum;
	
	afx_msg void OnBnClickedOk();
};