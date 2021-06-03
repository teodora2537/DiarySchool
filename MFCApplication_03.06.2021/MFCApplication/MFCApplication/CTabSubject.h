#pragma once
#include "Library.h"
#include "Subject.h"
#include "CUpdateSubject.h"
#include <list>
#include "CListMethods.h"
using namespace std;

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
	
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnAddSubject();
	void OnEditSubject();
	void OnViewSubject();
	void OnDeleteSubject();
	DECLARE_MESSAGE_MAP()

private:
	CListMethods m_listCtrl;

	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);

	void LoadData(bool isFromFile);

private:
	list<SUBJECT> m_listSubject;
};
