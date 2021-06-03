#include "pch.h"
#include "MFCApplication.h"
#include "CTabStudent.h"
using namespace std;

IMPLEMENT_DYNAMIC(CTabStudent, CDialogEx)

CTabStudent::CTabStudent()
	: CDialogEx(IDD_TAB_STUDENT)
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
END_MESSAGE_MAP()

BOOL CTabStudent::OnInitDialog() {

	if (!__super::OnInitDialog())
		return FALSE;

	//CStudent oStude;
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumnAtEnd("Date of birthday", eListCtrlColumnTypeData_Date, LVCFMT_LEFT, 100);

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

//CListCtrl& CTabStudent::GetListCtrl()
//{
//	CListCtrl& listCtrl = m_listCtrl;
//	return listCtrl;
//}