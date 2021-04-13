#pragma once
////////db////////
#include "odbcinst.h"
#include <afxdb.h>
/////////////////

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
	void LoadDataFromFile();
	void OnContextMenu(CWnd* pWnd, CPoint point);
	void OnAddStudent();
	void OnEditStudent();
	void OnViewStudent();
	void OnDeleteStudent();
	//void GetStudentFromDlg();


	DECLARE_MESSAGE_MAP()

public:
	CListCtrl m_listCtrl;

	CString m_cstrId;
	CString m_cstrName;
	CString m_cstrBirthday;
	CString m_cstrFirstName;
	CString m_cstrLastName;

	afx_msg void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadDataFromStruct();
};
