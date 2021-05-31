#include "pch.h"
#include "MFCApplication.h"
#include "CTabStudent.h"
using namespace std;

IMPLEMENT_DYNAMIC(CTabStudent, CDialogEx)

CTabStudent::CTabStudent()
	: CDialogEx(IDD_TAB_STUDENT)
{
	m_iSortColumn = -1;
	m_bSortAscending = TRUE;
}

CTabStudent::~CTabStudent()
{
}

void CTabStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTabStudent, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_STUDENT, OnAddStudent)
	ON_BN_CLICKED(IDC_MENU_EDIT_STUDENT, OnEditStudent)
	ON_BN_CLICKED(IDC_MENU_DEL_STUDENT, OnDeleteStudent)
	ON_BN_CLICKED(IDC_MENU_VIEW_STUDENT, OnViewStudent)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CTabStudent::OnNMDblclkList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CTabStudent::OnLvnColumnclickList)
END_MESSAGE_MAP()

BOOL CTabStudent::OnInitDialog() {

	if (!__super::OnInitDialog())
		return FALSE;
	
	CStudent oStude;
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Date of birthday", LVCFMT_LEFT, 100);

	LoadData(true);

	return true;
}

void CTabStudent::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	bool bIsItemSelected = pos != NULL;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_STUDENT, "Add student");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_STUDENT, "Edit student");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_STUDENT, "Delete student");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_STUDENT, "View student");

	//disable edit/delete/view from submenu
	submenu.EnableMenuItem(IDC_MENU_EDIT_STUDENT, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_DEL_STUDENT, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_VIEW_STUDENT, !bIsItemSelected);

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CTabStudent::OnAddStudent()
{
	CStudentData oStudentData;
	CStudent oStudent;
	oStudent.GetLastId(oStudentData);

	CStudentDlg dlg(oStudentData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oStudent.AddStudent(oStudentData))
	{
		if (IDRETRY)
			OnAddStudent();
		return;
	}

	LoadData(true);
}

void CTabStudent::OnEditStudent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	
	//if don't get selected item
	if (nItem < 0) 
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CStudentData oStudentData;
	CStudent oStudent;

	if (!oStudent.LoadStudent(nId, oStudentData))
		return;

	CStudentDlg dlg(oStudentData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oStudent.EditStudent(oStudentData)) {
		//MessageBox("The student not updated!", "Error", MB_RETRYCANCEL | MB_ICONERROR);

		if (IDRETRY)
			OnEditStudent();
		return;
	}

	LoadData(true);
}

void CTabStudent::OnDeleteStudent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	if (nItem < 0)
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CStudent oStudent;

	CString message;
	message.Format("Do you want to delete subject with room # %d?", nId);
	int result = MessageBox(message, "Delete student", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oStudent.DeleteStudent(nId))
	return;

	m_listCtrl.DeleteItem(nItem);
}

void CTabStudent::OnViewStudent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	//if don't get selected item
	if (nItem < 0)
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CStudentData oStudentData;

	CStudent oScore;

	if (!oScore.LoadStudent(nId, oStudentData))
		return;

	CStudentDlg dlg(oStudentData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;

	//if (!oScore.LoadStudent(nId, oStudentData))
	//	return;
	//
	//LoadData(true);
}

void CTabStudent::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewStudent();
}

void CTabStudent::OnLvnColumnclickList_(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int sortClm = -1;
	sortClm = pNMLV->iSubItem; //save column for the callback

	if (sortClm == 0) 
	{
		if (m_idStudentOrder == SORT_None)m_idStudentOrder = SORT_AZ;
		else m_idStudentOrder = (SortOrder)-m_idStudentOrder;
		m_sortOrderStudent = m_idStudentOrder;
	}
	else if (sortClm == 1) 
	{
		if (m_nameStudOrder == SORT_None)m_nameStudOrder = SORT_AZ;
		else m_nameStudOrder = (SortOrder)-m_nameStudOrder;
		m_sortOrderStudent = m_nameStudOrder;
	}
	else if (sortClm == 2) {
		if (m_birthdayOrder == SORT_None)	m_birthdayOrder = SORT_AZ;
		else m_birthdayOrder = (SortOrder) -m_birthdayOrder;
		m_sortOrderStudent = m_birthdayOrder;
	}

	CListMethods oList;
	oList.SortListStudent(sortClm, m_listStudent, m_sortOrderStudent);

	LoadData(false);
	
	*pResult = 0;
}

void CTabStudent::LoadData(bool isFromFile)
{
	m_listCtrl.DeleteAllItems();

	if (isFromFile)
	{
		m_listStudent.clear();
		CStudent oStudent;
		oStudent.PrintStudent_(m_listStudent);
	}

	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	for (auto& i = m_listStudent.begin(); i != m_listStudent.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).iId));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).szName);
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).szDate);
			
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->iId);
		}
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int  CTabStudent::GetSortedColumn() const { return m_iSortColumn; }
BOOL CTabStudent::IsSortAscending() const { return m_bSortAscending; }
void CTabStudent::SetSortAscending(BOOL bAscending) { m_bSortAscending = bAscending; }
void CTabStudent::SetSortedColumn(int nCol) { m_iSortColumn = nCol; }
BOOL CTabStudent::_IsValidIndex(int nIndex) const { return nIndex >= 0 && nIndex < m_listCtrl.GetItemCount(); }

int  CTabStudent::_StringCompare(const CString& s1, const CString& s2)
{
	if (s1 < s2)
		return -1;

	if (s1 > s2)
		return 1;

	return 0;
}
int  CTabStudent::_NumberCompare(int num1, int num2)//LPCTSTR pszNumber1, LPCTSTR pszNumber2)
{
	if (num1 < num2)
		return -1;

	if (num1 > num2)
		return 1;

	return 0;
}
int  CTabStudent::_DateCompare(const CString& strDate1, const CString& strDate2)
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

void CTabStudent::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	const int iColumn = pNMListView->iSubItem;

	Sort(iColumn, iColumn == GetSortedColumn() ? !IsSortAscending() : TRUE);

	*pResult = 0;
}
void CTabStudent::Sort(int iColumn, BOOL bAscending)
{
	//if (iColumn < 0 || iColumn >= GetColumnCount())
	//	return;

	SetSortedColumn(iColumn);
	SetSortAscending(bAscending);

	int item1 = 0;
	int item2 = 1;
	bool bIdDiffZero = false; //id different from zero
	CStudentData oStudent;
	Library oLib;
	bool flag = false;

	if (iColumn == 0) 
	{
		while (true) {
	
			if (bAscending) 
				flag = _NumberCompare(atoi(m_listCtrl.GetItemText(item1, iColumn)), atoi(m_listCtrl.GetItemText(item2, iColumn))) < 0;
			else
				flag = _NumberCompare(atoi(m_listCtrl.GetItemText(item1, iColumn)), atoi(m_listCtrl.GetItemText(item2, iColumn))) == 1;
			
			if(flag)
				SwapItems(oStudent, item1, item2, bIdDiffZero);

			if (!bIdDiffZero)
			{ 
				item1++; 
				item2++; 
			}
			else 
				bIdDiffZero = false;

			if (item1 == m_listCtrl.GetItemCount())
				break;
		}
		
		if (m_nClm0 == 0) 
		{
			m_bSortAscending = m_nClm0;
			m_nClm0 = 1;
		}
		else
		{
			m_bSortAscending = m_nClm0;
			m_nClm0 = 0;
		}
	}
	else if (iColumn == 1)
	{
		while (true) {

			if (bAscending)
				flag = _StringCompare(m_listCtrl.GetItemText(item1, iColumn), m_listCtrl.GetItemText(item2, iColumn)) < 0;
			else
				flag = _StringCompare(m_listCtrl.GetItemText(item1, iColumn), m_listCtrl.GetItemText(item2, iColumn)) == 1;

			if (flag)
				SwapItems(oStudent, item1, item2, bIdDiffZero);

			if (!bIdDiffZero)
			{ 
				item1++;
				item2++; 
			}
			else 
				bIdDiffZero = false;

			if (item1 == m_listCtrl.GetItemCount())
				break;
		}
		if (m_nClm1 == 0)
		{
			m_bSortAscending = m_nClm1;
			m_nClm1 = 1;
		}
		else
		{
			m_bSortAscending = m_nClm1;
			m_nClm1 = 0;
		}
	}
	else if (iColumn == 2)
	{
		while (true) {

			if (bAscending)
				flag = _DateCompare(m_listCtrl.GetItemText(item1, iColumn), m_listCtrl.GetItemText(item2, iColumn)) < 0;
			else
				flag = _DateCompare(m_listCtrl.GetItemText(item1, iColumn), m_listCtrl.GetItemText(item2, iColumn)) == 1;

			if (flag)
				SwapItems(oStudent, item1, item2, bIdDiffZero);

			if (!bIdDiffZero)
			{
				item1++; 
				item2++; 
			}
			else 
				bIdDiffZero = false;

			if (item1 == m_listCtrl.GetItemCount())
				break;
		}
	}
	if (m_nClm2 == 0)
	{
		m_bSortAscending = m_nClm2;
		m_nClm2 = 1;
	}
	else
	{
		m_bSortAscending = m_nClm2;
		m_nClm2 = 0;
	}
}

BOOL CTabStudent::SwapItems(CStudentData &oStudent, int& nItem1, int& nItem2, bool& flag)//(int nItem1, int nItem2)
{
	Library oLib;
	
	if (!_IsValidIndex(nItem1) || !_IsValidIndex(nItem2))
		return FALSE;

	const DWORD dwData1 = m_listCtrl.GetItemData(nItem1);
	const DWORD dwData2 = m_listCtrl.GetItemData(nItem2);


	oStudent.m_iId = atoi(m_listCtrl.GetItemText(nItem1, 0));
	m_listCtrl.SetItemText(nItem1, 0, m_listCtrl.GetItemText(nItem2, 0));
	m_listCtrl.SetItemText(nItem2, 0, oLib.IntToCString(oStudent.m_iId));

	oStudent.m_strFirstName = m_listCtrl.GetItemText(nItem1, 1);
	m_listCtrl.SetItemText(nItem1, 1, m_listCtrl.GetItemText(nItem2, 1));
	m_listCtrl.SetItemText(nItem2, 1, oStudent.m_strFirstName);

	oStudent.m_oleDT_Birthday = oLib.CStringToDate(m_listCtrl.GetItemText(nItem1, 2));
	m_listCtrl.SetItemText(nItem1, 2, m_listCtrl.GetItemText(nItem2, 2));
	m_listCtrl.SetItemText(nItem2, 2, oLib.OleDTToCString(oStudent.m_oleDT_Birthday));

	// swap item data
	m_listCtrl.SetItemData(nItem1, dwData2);
	m_listCtrl.SetItemData(nItem2, dwData1);

	if (nItem1 != 0) { nItem1 -= 1; nItem2 -= 1; flag = true; }

	return TRUE;
}