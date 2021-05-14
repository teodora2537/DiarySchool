#pragma once
#include <list>
#include "Library.h"
#include "CListMethods.h"
#include "Score.h"
#include "Student.h"
#include "Subject.h"
#include "CUpdateScore.h"
#include "CUpdateStudent.h"
#include "CUpdateSubject.h"
using namespace std;
// CTabReference dialog
class CTabReference : public CDialogEx
{
	DECLARE_DYNAMIC(CTabReference)

public:
	CTabReference();   // standard constructor
	virtual ~CTabReference();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_REFERENCES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
//buttons for list references
	afx_msg void OnBnClickedButtonAvgscorebysubject();
	afx_msg void OnBnClickedButtonAvgscorebyallsubjects();
	afx_msg void OnBnClickedButtonExcellentstudent();
	afx_msg void OnBnClickedButtonBirtdays();
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButtonByMoreSubjects();
	
	//load functions and clicked column
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);

	void LoadData(CString name);

	CListCtrl m_listCtrl;

protected:
	bool isOnlyNames = false;
	CString name;

	//sort
	SortOrder orderClm0 = SORT_None;
	SortOrder orderClm1 = SORT_None;
	SortOrder orderClm2 = SORT_None;
	SortOrder orderClm3 = SORT_None;
	SortOrder sortOrderReference = SORT_None;
	list<REFERENCE> m_listReference;
	int sortClmReference = -1;

};