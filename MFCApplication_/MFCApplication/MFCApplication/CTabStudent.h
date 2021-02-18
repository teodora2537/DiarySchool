#pragma once


// CTabStudent dialog

class CTabStudent : public CDialogEx
{
	DECLARE_DYNAMIC(CTabStudent)

public:
	CTabStudent(CWnd* pParent = nullptr);   // standard constructor
	afx_msg void OnInitialUpdate();
	virtual ~CTabStudent();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();


	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_listCtrl;
};
