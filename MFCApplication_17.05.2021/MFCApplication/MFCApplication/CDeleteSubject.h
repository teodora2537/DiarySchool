#pragma once


// CDeleteSubject dialog

class CDeleteSubject : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteSubject)

public:
	CDeleteSubject(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDeleteSubject();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_SUBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedDeleteSubject();

	DECLARE_MESSAGE_MAP()

public:
	CString roomNum;



	afx_msg void OnBnClickedOk();
};
