#pragma once
#include <afxdb.h>
#include "Library.h"
#include "Student.h"
#include "CUpdateStudent.h"
#include "CListMethods.h"
#include <list>
using namespace std;

class CTabStudent : public CDialogEx, public CDatabase, public CRecordset
{
	DECLARE_DYNAMIC(CTabStudent)

public:
	CTabStudent(CWnd* pParent = nullptr);   // standard constructor
	//afx_msg void OnInitialUpdate();
	virtual ~CTabStudent();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnAddStudent();
	void OnEditStudent();
	void OnViewStudent();
	void OnDeleteStudent();
	DECLARE_MESSAGE_MAP()

private:
	CListCtrl m_listCtrl;

	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadDataFromStruct();
	void LoadDataFromFile();
};
