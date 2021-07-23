#pragma once
#include "MFCApplication.h"
#include "CUpdateStudent.h"
#include "Library.h"
#include <list>

class CTabStudent : public CDialogEx
{
	DECLARE_DYNAMIC(CTabStudent)

public:
	CTabStudent(); 
	virtual ~CTabStudent();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_STUDENT };
#endif

protected: //metrhods
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();

private: //methods
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddStudent();
	afx_msg void OnEditStudent();
	afx_msg void OnViewStudent();
	afx_msg void OnDeleteStudent();
	DECLARE_MESSAGE_MAP()

private: //methods
	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadData();

private: //member 
	CListMethods m_listCtrl;
	list<CStudentData> m_listStudent;
};