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
	CString m_strClassNum;
	CString m_strSubject;
	CString m_strDate;
	CString m_strScore;

	afx_msg void OnBnClickedOk();
};
