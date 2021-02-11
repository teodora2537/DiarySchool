#pragma once


// CAddScore dialog

class CAddScore : public CDialogEx
{
	DECLARE_DYNAMIC(CAddScore)

public:
	CAddScore(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddScore();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	afx_msg void OnBnClickedAddScore();

	DECLARE_MESSAGE_MAP()

public:
	CString classNum;
	CString subject;
	CString date;
	CString score;
	afx_msg void OnBnClickedOk();
};
