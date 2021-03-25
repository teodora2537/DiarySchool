#include "pch.h"
#include "MFCApplication.h"
#include "CTabSubject.h"
#include "afxdialogex.h"
#include "Subject.h"
#include "CUpdateSubject.h"
#include "Library.h"
#include "Student.h"
#include <list>
#include "CListMethods.h"

// CTabSubject dialog

IMPLEMENT_DYNAMIC(CTabSubject, CDialogEx)

CTabSubject::CTabSubject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_SUBJECT, pParent)
{

}

CTabSubject::~CTabSubject()
{
}

void CTabSubject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTabSubject, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_SUBJECT, OnAddSubject)
	ON_BN_CLICKED(IDC_MENU_EDIT_SUBJECT, OnEditSubject)
	ON_BN_CLICKED(IDC_MENU_DEL_SUBJECT, OnDeleteSubject)
	ON_BN_CLICKED(IDC_MENU_VIEW_SUBJECT, OnViewSubject)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CTabSubject::OnNMDblclkList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CTabSubject::OnLvnColumnclickList)
END_MESSAGE_MAP()

BOOL CTabSubject::OnInitDialog() {

	//CDialogEx::OnInitDialog();
	if (!__super::OnInitDialog())
		return FALSE;
	
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Teacher", LVCFMT_LEFT, 100);
	LoadDataFromFile(m_listCtrl);

	return true;
}

void CTabSubject::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not sected
	bool bIsItemSelected = pos != NULL;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SUBJECT, "Add subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SUBJECT, "Edit subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SUBJECT, "Delete subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SUBJECT, "View subject");

	//disable edit/delete/view from submenu
	submenu.EnableMenuItem(IDC_MENU_EDIT_SUBJECT, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_DEL_SUBJECT, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_VIEW_SUBJECT, !bIsItemSelected);

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CTabSubject::OnAddSubject()
{
	CSubjectData oSubjectData;

	CSubject oSubject;

	oSubjectData.m_iRoomNumber = m_listCtrl.GetItemCount() + 1;

	CSubjectDlg dlg(oSubjectData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oSubject.AddSubject(oSubjectData))
		return;
	LoadDataFromFile(m_listCtrl);
}

void CTabSubject::OnEditSubject()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not selected
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//if don't get selected item
	if (nItem < 0)
		return;

	int nRoomId = (int)m_listCtrl.GetItemData(nItem);

	CSubjectData oSubjectData;

	CSubject oSubject;

	if (!oSubject.LoadSubject(nRoomId, oSubjectData))
		return;

	CSubjectDlg dlg(oSubjectData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oSubject.EditSubject(oSubjectData))
		return;

	LoadDataFromFile(m_listCtrl);
}

void CTabSubject::OnDeleteSubject()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	if (nItem < 0)
		return;

	int nRoomId = (int)m_listCtrl.GetItemData(nItem);

	CSubject oSubject;

	CString message;
	message.Format("Do you want to delete subject with room # %d?", nRoomId);
	int result = MessageBox(message, "Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oSubject.DeleteSubject(nRoomId))
		return;

	m_listCtrl.DeleteItem(nItem);
}

void CTabSubject::OnViewSubject()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not sected
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//if don't get selected item
	if (nItem < 0)
		return;

	int nRoomId = (int)m_listCtrl.GetItemData(nItem);

	CSubjectData oSubjectData;

	CSubject oSubject;

	if (!oSubject.LoadSubject(nRoomId, oSubjectData))
		return;

	CSubjectDlg dlg(oSubjectData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oSubject.LoadSubject(nRoomId, oSubjectData))
		return;

	LoadDataFromFile(m_listCtrl);
}

void CTabSubject::GetSubjectFromDlg()
{
	m_strId = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	m_strSubject = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	CString m_cstrTeacher = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);

	m_strFirstName = "";
	m_strLastName = "";
	m_nTokenPos = 0;
	m_iCount = 0;
	Library lib;
	CString strToken = m_cstrTeacher.Tokenize(_T(" "), m_nTokenPos);

	while (!strToken.IsEmpty())
	{
		if (m_iCount == 0)
		{
			m_strFirstName = strToken;
			m_iCount++;
		}
		else if (m_iCount == 1)
		{
			m_strLastName = strToken;
		}
		strToken = m_cstrTeacher.Tokenize(_T(" "), m_nTokenPos);
	}
	CSubjectData oSubjectData(_ttoi(m_strId), m_strSubject, m_strFirstName, m_strLastName);
	oSubjectData.m_strFullNameTeacher = m_cstrTeacher;
}

void CTabSubject::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewSubject();
}

///////////////////////////////////////////////////////////////////////////////////

list<SubStruct> m_listSubject;

SortOrder orderIdRoom = SORT_None;
SortOrder orderSubs = SORT_None;
SortOrder orderTeachers = SORT_None;
SortOrder sortOrderSubject = SORT_None;

void CTabSubject::LoadDataFromFile(CListCtrl& m_listCtrl)
{
	m_listCtrl.DeleteAllItems();
	Library oLib;
	CSubject oSubject;
	m_listSubject.clear();
	map<int, vector<CString>> m_mapSubjects;
	oSubject.PrintSubject(m_mapSubjects);
	
	int nCount = 0;
	int nItemIndex = 0;
	
	//IdRoom | subject, fn, ln
		for (map<int, vector<CString>>::iterator it = m_mapSubjects.begin(); it != m_mapSubjects.end(); it++) {
		
			nCount = m_listCtrl.GetItemCount();
		
		SubStruct subStruct = { oLib.IntToCString(it->first), it->second[0], it->second[1] + " " + it->second[2] };
		m_listSubject.push_back(subStruct);

		nItemIndex = m_listCtrl.InsertItem(nCount, subStruct.idRoom);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, subStruct.subject);
			m_listCtrl.SetItemText(nItemIndex, 2, subStruct.nameTeacher);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(subStruct.idRoom));
		}
	}
	
}

int sortClm = -1;   // not set

void CTabSubject::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	sortClm = pNMLV->iSubItem; // <<<<< save column# for the callback

	//for CListMethods
	if (sortClm == 0) {
		if (orderIdRoom == SORT_None) orderIdRoom = SORT_AZ;
	else orderIdRoom = (SortOrder)-orderIdRoom; // -1 to 1, 1 to -1
		sortOrderSubject = orderIdRoom;
	}
	else if (sortClm == 1) {
		if (orderSubs == SORT_None) orderSubs = SORT_AZ;
		else orderSubs = (SortOrder)-orderSubs; // -1 to 1, 1 to -1
		sortOrderSubject = orderSubs;
	}
	else if (sortClm == 2) {
		if (orderTeachers == SORT_None) orderTeachers = SORT_AZ;
		else orderTeachers = (SortOrder)-orderTeachers; // -1 to 1, 1 to -1
		sortOrderSubject = orderTeachers;
	}

	CListMethods oList;
	oList.SortListSub(sortClm, m_listSubject, sortOrderSubject);

	LoadDataFromListStruct();

	*pResult = 0;
}

void CTabSubject::LoadDataFromListStruct()
{
	m_listCtrl.DeleteAllItems();
	Library oLib;
	CSubject oSubject;

	int nCount = 0;
	int nItemIndex = 0;

	//IdRoom | subject, fn, ln
	for (list<SubStruct>::iterator it = m_listSubject.begin(); it != m_listSubject.end(); it++) {

		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, it->idRoom);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->subject);
			m_listCtrl.SetItemText(nItemIndex, 2, it->nameTeacher);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(it->idRoom));
		}
	}
}
