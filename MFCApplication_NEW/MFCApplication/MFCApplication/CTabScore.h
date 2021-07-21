#pragma once
#include "MFCApplication.h"
#include "CListMethods.h"
#include "CUpdateScore.h"
#include "Library.h"
#include <list>

class CTabScore : public CDialogEx
{
	DECLARE_DYNAMIC(CTabScore)

public:
	CTabScore();   // standard constructor
	virtual ~CTabScore();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	

	DECLARE_MESSAGE_MAP()

private: //contex menu methods
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddScore();
	afx_msg void OnEditScore();
	afx_msg void OnDeleteScore();
	afx_msg void OnViewScore();

private: //methods
	void afx_msg OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	
public: //methods 
	void LoadData();

private: //member
	CListMethods m_listCtrl;
	list<CScoreData> m_listScore;
};