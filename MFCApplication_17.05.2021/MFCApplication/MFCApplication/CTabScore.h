#pragma once
#include <list>
#include "Score.h"
#include "CUpdateScore.h"
#include "Library.h"
#include "CListMethods.h"
using namespace std;

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

private: //contex menu
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddScore();
	afx_msg void OnEditScore();
	afx_msg void OnDeleteScore();
	afx_msg void OnViewScore();

private:
	CListCtrl m_listCtrl;
	
	void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadData(CString isFromFile);

private: //sort
	SortOrder idStudOrder = SORT_None;
	SortOrder nameStudentOrder = SORT_None;
	SortOrder subOrder = SORT_None;
	SortOrder scoreOrder = SORT_None;
	SortOrder dateOrder = SORT_None;
	SortOrder sortOrderScore = SORT_None;
	
	list<SCORE> m_listScore;
};

