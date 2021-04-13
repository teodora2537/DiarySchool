#pragma once
//#include <iostream>
//#include "Library.h"
//#include "Subject.h"
using namespace std;

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

	BOOL OnInitDialog();

	void LoadDataFromFile();
	
	void OnContextMenu(CWnd* pWnd, CPoint point);
	
	void OnAddSubject();
	
	void OnEditSubject();
	
	void OnViewSubject();
	
	void OnDeleteSubject();
	
	void GetSubjectFromDlg();

	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_listCtrl;

	CString m_strId;
	CString m_strSubject;
	CString m_strFirstName;
	CString m_strLastName;

	//DialogMode m_eModeAddSub;
	//CSubjectData m_oSubject;

	int m_nTokenPos{0};
	int m_iCount{0};
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadDataFromListStruct();
};
