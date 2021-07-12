#pragma once
#include "MFCApplication.h"
#include "CListMethods.h"
#include "CUpdateSubject.h"
#include "Library.h"
#include <list>

class CTabSubject : public CDialogEx
{
	DECLARE_DYNAMIC(CTabSubject)

public:
	CTabSubject();   // standard constructor
	virtual ~CTabSubject();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_SUBJECT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	
private: //Context Menu
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnAddSubject();
	void OnEditSubject();
	void OnViewSubject();
	void OnDeleteSubject();

private: //methods 
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadData(bool isFromFile);
	DECLARE_MESSAGE_MAP()

private: //member
	CListMethods m_listCtrl;
	list<CSubjectData> m_listSubject;
};
