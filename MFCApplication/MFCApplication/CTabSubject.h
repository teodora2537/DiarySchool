#pragma once


// CTabSubject dialog

class CTabSubject : public CDialogEx
{
	DECLARE_DYNAMIC(CTabSubject)

public:
	CTabSubject(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabSubject();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_SUBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
