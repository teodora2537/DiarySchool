#include "pch.h"
#include "MFCApplication.h"
#include "CTabStudent.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"
#include "CUpdateStudent.h"
#include "CListMethods.h"
#include <list>
using namespace std;;

IMPLEMENT_DYNAMIC(CTabStudent, CDialogEx)

CTabStudent::CTabStudent(CWnd* pParent)
	: CDialogEx(IDD_TAB_STUDENT, pParent)
{

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
	map<vector<CString>, vector<int>> mapAllScoreBySub;
	oStude.AverageScore(mapAllScoreBySub);

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Date of birthday", LVCFMT_LEFT, 100);

	LoadDataFromFile();

	return true;
}

void CTabStudent::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not sected
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

	oStudentData.m_iClassNumber = m_listCtrl.GetItemCount() + 1;

	CStudentDlg dlg(oStudentData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oStudent.AddStudent(oStudentData))
		return;

	LoadDataFromFile();
}

void CTabStudent::OnEditStudent()
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

	CStudentData oStudentData;

	CStudent oStudent;

	if (!oStudent.LoadStudent(nRoomId, oStudentData))
		return;

	CStudentDlg dlg(oStudentData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oStudent.EditStudent(oStudentData))
		return;

	LoadDataFromFile();
}

void CTabStudent::OnDeleteStudent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	if (nItem < 0)
		return;

	int nRoomId = (int)m_listCtrl.GetItemData(nItem);

	CStudent oStudent;
	GetStudentFromDlg();
	Library oLib;
	CStudentData oStudentData;

	CString message;
	message.Format("Do you want to delete subject with room # %d?", nRoomId);
	int result = MessageBox(message, "Delete student", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oStudent.DeleteStudent(nRoomId))
		return;

	m_listCtrl.DeleteItem(nItem);
}

void CTabStudent::OnViewStudent()
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

	CStudentData oStudentData;

	CStudent oScore;

	if (!oScore.LoadStudent(nRoomId, oStudentData))
		return;

	CStudentDlg dlg(oStudentData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oScore.LoadStudent(nRoomId, oStudentData))
		return;

	LoadDataFromFile();
}

void CTabStudent::GetStudentFromDlg()
{
	m_cstrId = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	m_cstrName = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	m_cstrBirthday = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);
	m_cstrFirstName = m_cstrLastName = "";

	int nTokenPos = 0;
	int count = 0;

	Library lib;
	CString strToken = m_cstrName.Tokenize(_T(" "), nTokenPos);

	while (!strToken.IsEmpty())
	{
		if (count == 0)
		{
			m_cstrFirstName = strToken;
			count++;
		}
		else if (count == 1)
		{
			m_cstrLastName = strToken;
		}
		strToken = m_cstrName.Tokenize(_T(" "), nTokenPos);
	}

	CStudentData m_oStudent(_ttoi(m_cstrId), m_cstrFirstName, m_cstrLastName, m_cstrBirthday);
	m_oStudent.m_strFullName = m_cstrName;
}

void CTabStudent::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewStudent();
}
///////////////////////////////////////////////////////////////////

SortOrder idStudentOrder = SORT_None;
SortOrder nameStudOrder = SORT_None;
SortOrder birthdayOrder = SORT_None;
SortOrder sortOrderStudent = SORT_None;

list<StudentStruct> m_listStudent;
/////////////////////////////////////////////

void CTabStudent::LoadDataFromFile()
{
	m_listCtrl.DeleteAllItems();

	CStudent oStudent;
	Library oLib;
	map<int, vector<CString>> m_mapAllStudent;
	oStudent.PrintStudent(m_mapAllStudent);

	m_listStudent.clear();

	int nCount = 0;
	int nItemIndex = 0;
	
	//idStudent | name, birthday
	for (auto i = m_mapAllStudent.begin(); i != m_mapAllStudent.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		StudentStruct studentStruct = { i->first, i->second[0] +" "+ i->second[1], i->second[2]};
		m_listStudent.push_back(studentStruct);

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).first));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).second[0] + " " + (*i).second[1]);
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).second[2]);
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->first);
		}
	}
}

void CTabStudent::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int sortClm = -1;
	sortClm = pNMLV->iSubItem; // <<<<< save column# for the callback
	
	if (sortClm == 0) {
		if ( idStudentOrder == SORT_None)idStudentOrder = SORT_AZ;
		else idStudentOrder = (SortOrder)-idStudentOrder;
		sortOrderStudent = idStudentOrder;
	}
	else if (sortClm == 1) {
		if (nameStudOrder == SORT_None)nameStudOrder = SORT_AZ;
		else nameStudOrder = (SortOrder)-nameStudOrder;
		sortOrderStudent = nameStudOrder;
	}
	else if (sortClm == 2) {
		if (birthdayOrder == SORT_None)birthdayOrder = SORT_AZ;
		else birthdayOrder = (SortOrder)-birthdayOrder;
		sortOrderStudent = birthdayOrder;
	}

	CListMethods oList;
	oList.SortListStudent(sortClm, m_listStudent, sortOrderStudent);

	LoadDataFromStruct();
	
	*pResult = 0;
}

void CTabStudent::LoadDataFromStruct()
{
	m_listCtrl.DeleteAllItems();
	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	//idStudent | name, birthday
	for (list<StudentStruct>::iterator i = m_listStudent.begin(); i != m_listStudent.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(i->nIdStudent));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, i->strNameStudent);
			m_listCtrl.SetItemText(nItemIndex, 2, i->strBirthday);
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->nIdStudent);
		}
	}
}


