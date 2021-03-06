#pragma once
#include <afxdb.h>
#include "Library.h"
#include "Student.h"
#include "CUpdateStudent.h"
#include "CListMethods.h"
#include <list>
using namespace std;

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

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddStudent();
	afx_msg void OnEditStudent();
	afx_msg void OnViewStudent();
	afx_msg void OnDeleteStudent();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_listCtrl;

	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadData(bool isFromFile);

private: //sort
	SortOrder idStudentOrder = SORT_None;
	SortOrder nameStudOrder = SORT_None;
	SortOrder birthdayOrder = SORT_None;
	SortOrder sortOrderStudent = SORT_None;

	list<STUDENT> m_listStudent;
};
