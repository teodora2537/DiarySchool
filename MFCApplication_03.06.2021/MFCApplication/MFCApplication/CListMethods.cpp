#include "pch.h"
#include "CListMethods.h"
#include "resource.h"
#include "CTabStudent.h"
using namespace std;

CListMethods::CListMethods()
{
	m_iSortColumn = -1;
	m_bSortAscending = TRUE;
}

BEGIN_MESSAGE_MAP(CListMethods, CListCtrl)
	ON_NOTIFY_REFLECT_EX(LVN_COLUMNCLICK, &CListMethods::OnLvnColumnclick)
END_MESSAGE_MAP()

int  CListMethods::GetSortedColumn() const
{
	return m_iSortColumn;
}

void CListMethods::SetSortAscending(const BOOL& bAscending)
{
	m_bSortAscending = bAscending;
}

void CListMethods::SetSortedColumn(const int& nCol)
{
	m_iSortColumn = nCol;
}

int CListMethods::InsertColumnAtEnd(
	_In_z_ LPCTSTR lpszColumnHeading
	, _In_ ListCtrlColumnTypeData eTypeData
	, _In_ int nFormat /*= LVCFMT_LEFT*/
	, _In_ int nWidth /*= -1*/
	, _In_ int nSubItem /*= -1*/)
{
	CHeaderCtrl* pHeader = (CHeaderCtrl*)GetDlgItem(0);
	int nColumnCount = pHeader->GetItemCount();

	int nNewColumnIndex = __super::InsertColumn(nColumnCount, lpszColumnHeading, nFormat, nWidth, nSubItem);

	m_mpColumnTypeData.SetAt(nNewColumnIndex, eTypeData);

	return nNewColumnIndex;
}

BOOL CListMethods::IsSortAscending() const
{
	return m_bSortAscending;
}

BOOL CListMethods::_IsNumber(const CString& strItem)
{
	if (strItem.SpanIncluding("0123456789") == strItem)
		return true;
	return false;
}

BOOL CListMethods::_IsDate(CString strItem)
{
	COleDateTime date;
	date.ParseDateTime(strItem);
	return date.GetStatus() == COleDateTime::valid;
}

int  CListMethods::_StringCompare(const CString& s1, const CString& s2)
{
	if (s1 < s2)
		return -1;

	if (s1 > s2)
		return 1;

	return 0;
}

int  CListMethods::_NumberCompare(CString strItem1, CString strItem2)
{
	Library oLib;
	int nNum1 = atoi(strItem1);
	int nNum2 = atoi(strItem2);
	if (nNum1 < nNum2)
		return -1;

	if (nNum1 > nNum2)
		return 1;

	return 0;
}

int  CListMethods::_DateCompare(const CString& strDate1, const CString& strDate2)
{
	COleDateTime date1, date2;
	date1.ParseDateTime(strDate1);
	date2.ParseDateTime(strDate2);

	if (date1.GetStatus() != COleDateTime::valid || date2.GetStatus() != COleDateTime::valid)
		return _StringCompare(strDate1, strDate2); // not date

	if (date1 < date2)
		return -1;

	if (date1 > date2)
		return 1;

	return 0;
}

BOOL CListMethods::OnLvnColumnclick(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;

	ListCtrlColumnTypeData eColDataType = eListCtrlColumnTypeData_None;

	m_mpColumnTypeData.Lookup(iColumn, eColDataType);

	eColDataType;

	Sort(iColumn, iColumn == GetSortedColumn() ? !IsSortAscending() : TRUE, eColDataType);
	*pResult = 0;

	return TRUE;
}

void CListMethods::Sort(int iColumn, BOOL bAscending, ListCtrlColumnTypeData eColDataType)
{
	SetSortedColumn(iColumn);
	SetSortAscending(bAscending);

	int item1 = 0;
	int item2 = 1;
	int iCountSwap = 0;
	CStudentData oStudent;
	Library oLib;
	bool flag = false;

	while (true) {

		if (bAscending && _CompareFunction(GetItem(item1, iColumn), GetItem(item2, iColumn), eColDataType) == -1)
		{
			if (SwapItems(oStudent, item1, item2))
				iCountSwap++;
		}
		else if (!bAscending && _CompareFunction(GetItem(item1, iColumn), GetItem(item2, iColumn), eColDataType) == 1)
		{
			if (SwapItems(oStudent, item1, item2))
				iCountSwap++;
		}

		if (item1 == GetItemCount() - 2 && item2 == GetItemCount() - 1)
		{
			if (iCountSwap != 0)
			{
				item1 = 0;
				item2 = 1;
				iCountSwap = 0;
				continue;
			}
			else break;
		}

		item1++;
		item2++;
	}
}

BOOL CListMethods::SwapItems(CStudentData& oStudent, int& nItem1, int& nItem2)
{
	const DWORD dwData1 = GetItemData(nItem1);
	const DWORD dwData2 = GetItemData(nItem2);

	SwapItemText(oStudent, nItem1, nItem2);

	// swap item data
	SetItemData(nItem1, dwData2);
	SetItemData(nItem2, dwData1);

	return TRUE;
}

void CListMethods::SwapItemText(CStudentData& oStudent, int& nItem1, int& nItem2)
{
	Library oLib;
	oStudent.m_iId = atoi(GetItem(nItem1, 0));
	SetItemText(nItem1, 0, GetItem(nItem2, 0));
	SetItemText(nItem2, 0, oLib.IntToCString(oStudent.m_iId));

	oStudent.m_strFirstName = GetItem(nItem1, 1);
	SetItemText(nItem1, 1, GetItem(nItem2, 1));
	SetItemText(nItem2, 1, oStudent.m_strFirstName);

	oStudent.m_oleDT_Birthday = oLib.CStringToDate(GetItem(nItem1, 2));
	SetItemText(nItem1, 2, GetItem(nItem2, 2));
	SetItemText(nItem2, 2, oLib.OleDTToCString(oStudent.m_oleDT_Birthday));
}

int CALLBACK CListMethods::_CompareFunction(CString& strItem1, CString& strItem2, ListCtrlColumnTypeData eColDataType)
{
	switch (eColDataType)
	{
	case 1:
		return _NumberCompare(strItem1, strItem2);
		break;
	case 2:
		return _DateCompare(strItem1, strItem2);
		break;
	case 3:
		return _StringCompare(strItem1, strItem2);
		break;
	}
}

CString CListMethods::GetItem(const int& nRow, const int& nColumn) {
	return GetItemText(nRow, nColumn);
}