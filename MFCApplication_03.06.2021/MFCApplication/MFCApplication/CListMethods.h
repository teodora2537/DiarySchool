#pragma once
#include <list>
#include "Library.h"
#include "Student.h"
#include "Score.h"
#include "Subject.h"
using namespace std;

enum ListCtrlColumnTypeData
{
   eListCtrlColumnTypeData_None = 0,
   eListCtrlColumnTypeData_Int = 1,
   eListCtrlColumnTypeData_Date = 2,
   eListCtrlColumnTypeData_String = 3,
};

class CListMethods : public CListCtrl
{
private:
    int  m_iSortColumn;
    bool m_bSortAscending;

    CString GetItem(const int& nRow, const int& nColumn);

public:

    CListMethods();

    afx_msg BOOL OnLvnColumnclick(NMHDR* pNMHDR, LRESULT* pResult);
	BOOL IsSortAscending() const;
	BOOL _IsNumber(const CString& strItem);
	BOOL _IsDate(CString strItem);
	BOOL SwapItems(CStudentData& oStudent, int& nItem1, int& nItem2);

    void SwapItemText(CStudentData& oStudent, int& nItem1, int& nItem2);
	
    int GetSortedColumn() const;
	int  _StringCompare(const CString& s1, const CString& s2);
	int  _NumberCompare(CString strItem1, CString strItem2);
	int  _DateCompare(const CString& strDate1, const CString& strDate2);
	int _CompareFunction(CString& strItem1, CString& strItem2, ListCtrlColumnTypeData eColDataType);
	
    void Sort(int iColumn, BOOL bAscending, ListCtrlColumnTypeData);

    void SetSortAscending(const BOOL& bAscending);
    void SetSortedColumn(const int& nCol);

    int InsertColumnAtEnd(_In_z_ LPCTSTR lpszColumnHeading,
        const ListCtrlColumnTypeData eTypeData,
        _In_ int nFormat = LVCFMT_LEFT, _In_ int nWidth = -1, _In_ int nSubItem = -1);

    CMap<int, int, ListCtrlColumnTypeData, ListCtrlColumnTypeData> m_mpColumnTypeData;

    DECLARE_MESSAGE_MAP()
};