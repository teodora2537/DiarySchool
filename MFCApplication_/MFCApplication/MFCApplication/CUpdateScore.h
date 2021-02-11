#pragma once


// CUpdateScore dialog

class CUpdateScore : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateScore)

public:
	CUpdateScore(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateScore();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString classNum;
	CString subject;
	CString date;
	CString score;
	afx_msg void OnBnClickedOk();
};
