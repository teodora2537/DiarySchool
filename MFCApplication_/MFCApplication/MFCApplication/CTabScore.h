#pragma once


// CTabScore dialog

class CTabScore : public CDialogEx
{
	DECLARE_DYNAMIC(CTabScore)

public:
	CTabScore(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabScore();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtrl;
	int m_iRow = 0;
	int nItem = 0;

};
