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
	afx_msg void OnLvnColumnclickList_(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult);
	void LoadData(bool isFromFile);

private: //sort
	SortOrder m_idStudentOrder = SORT_None;
	SortOrder m_nameStudOrder = SORT_None;
	SortOrder m_birthdayOrder = SORT_None;
	SortOrder m_sortOrderStudent = SORT_None;

	list<STUDENT> m_listStudent;

	////////////////////////////////////////////
private:
	int  m_iSortColumn;
	bool m_bSortAscending;
	map<int, bool> mapSortColumn;
	int m_nClm0 = 0;
	int m_nClm1 = 0;
	int m_nClm2 = 0;

	int GetSortedColumn() const;
	BOOL IsSortAscending() const;
	void SetSortAscending(BOOL bAscending);
	void SetSortedColumn(int nCol);
	BOOL _IsValidIndex(int nIndex) const;
	BOOL _IsNumber(const CString& strItem);
	BOOL _IsDate(CString strItem);
	int  _StringCompare(const CString& s1, const CString& s2);
	int  _NumberCompare(CString strItem1, CString strItem2);//LPCTSTR pszNumber1, LPCTSTR pszNumber2);
	int  _DateCompare(const CString& strDate1, const CString& strDate2);
	void Sort(int iColumn, BOOL bAscending);
	int _CompareFunction(CString& strItem1, CString& strItem2, int iColumn);
	BOOL SwapItems(CStudentData& oStudent,int& nItem1,int& nItem2, bool& flag);
};

