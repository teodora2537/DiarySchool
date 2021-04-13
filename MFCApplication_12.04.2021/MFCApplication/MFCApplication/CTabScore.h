
#pragma once
// CTabScore dialog
#include <iostream>
#include <map>
#include <vector>
#include <string.h>
using namespace std;

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
	int m_iRow{0};
	int nItem = {0};
	
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddScore();
	afx_msg void OnEditScore();
	afx_msg void OnDeleteScore();
	afx_msg void OnViewScore();

	//void GetScoreFromDlg();
	
	CString m_cstrClassNum;
	CString m_cstrSubject;
	CString m_cstrDate;
	CString m_cstrScore;
	
	afx_msg void LoadDataFromFile();
	
	void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadDataFromStruct();
private:
};

