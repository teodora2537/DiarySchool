#pragma once
#include "Library.h"
#include "Subject.h"
#include "CUpdateSubject.h"
#include "CListMethods.h"
#include <list>
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
	
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnAddSubject();
	void OnEditSubject();
	void OnViewSubject();
	void OnDeleteSubject();

	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_listCtrl;

	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);

	void LoadDataFromFile();
	void LoadDataFromListStruct();
};
