#pragma once


// CAddScore dialog

class CAddScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddScoreDlg)

public:
	CAddScoreDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddScoreDlg();

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
