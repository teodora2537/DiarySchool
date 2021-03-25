#pragma once
#include "Subject.h"
#include "Library.h"
#include <list>
#include "CListMethods.h"

// CTabSubject dialog
/*
typedef enum {
	SORT_None = 0,
	SORT_AZ = -1,
	SORT_ZA = 1,
} SortOrderSub;

typedef struct SubStruct {
	CString idRoom;
	CString subject;
	CString nameTeacher;
} ListData;
*/

	
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

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_listCtrl;
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddSubject();
	afx_msg void OnEditSubject();
	afx_msg void OnDeleteSubject();
	afx_msg void OnViewSubject();

	void GetSubjectFromDlg();

	CString m_strId;
	CString m_strSubject;
	CString m_strFirstName;
	CString m_strLastName;

	

	DialogMode m_eModeAddSub;
	CSubjectData m_oSubject;

	int m_nTokenPos = 0;
	int m_iCount = 0;
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadDataFromFile(CListCtrl& m_listCtrl);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadDataFromListStruct();
};
