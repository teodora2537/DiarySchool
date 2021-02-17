#pragma once


// CDeleteScore dialog

class CDeleteScore : public CDialogEx
{
	DECLARE_DYNAMIC(CDeleteScore)

public:
	CDeleteScore(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CDeleteScore();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_DELETE_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

//afx_msg	void OnBnClickedDeleteScore();

	DECLARE_MESSAGE_MAP()

public:
	CString idScore;
	afx_msg void OnBnClickedOk();
};
