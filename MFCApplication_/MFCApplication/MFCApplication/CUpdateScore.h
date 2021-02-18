#pragma once


// CUpdateScore dialog

class CUpdateScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateScoreDlg)

public:
	CUpdateScoreDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateScoreDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_cstrClassNum;
	CString m_cstrSubject;
	CString m_cstrDate;
	CString m_cstrScore;

	afx_msg void OnBnClickedOk();
};
