#include "pch.h"
#include "CTabStudent.h"

IMPLEMENT_DYNAMIC(CTabStudent, CDialogEx)

CTabStudent::CTabStudent()
	: CDialogEx(IDD_DIALOG_TAB_STUDENT)
{
}

CTabStudent::~CTabStudent()
{
}

void CTabStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STUDENT, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTabStudent, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_STUDENT, OnAddStudent)
	ON_BN_CLICKED(IDC_MENU_EDIT_STUDENT, OnEditStudent)
	ON_BN_CLICKED(IDC_MENU_DEL_STUDENT, OnDeleteStudent)
	ON_BN_CLICKED(IDC_MENU_VIEW_STUDENT, OnViewStudent)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_STUDENT, &CTabStudent::OnNMDblclkList)
END_MESSAGE_MAP()

BOOL CTabStudent::OnInitDialog() 
{

	if (!__super::OnInitDialog()) {
		return FALSE;
	}

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Date of birthday", eListCtrlColumnTypeData_Date, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Email", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Phone number", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("EGN", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("City", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Post code", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Neighborhood", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Address", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	
	LoadData(true);

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}

	return TRUE;
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
	
	oStudent.GetLastId(oStudentData.m_iStudentId);

	CStudentDlg dlg(oStudentData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK) {
		return;
	}

	if (!oStudent.AddStudent(oStudentData))
	{
		if (IDRETRY) {
			OnAddStudent();
		}
		return;
	}

	LoadData(true);
}

void CTabStudent::OnEditStudent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL) {
		return;
	}

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

	if (!oStudent.LoadStudent(nId, oStudentData)) {
		return;
	}

	CStudentDlg dlg(oStudentData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK) {
		return;
	}

	if (!oStudent.EditStudent(oStudentData)) {

		if (IDRETRY) {
			OnEditStudent();
		}
		return;
	}

	LoadData(true);
}

void CTabStudent::OnDeleteStudent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	if (pos == NULL) {
		return;
	}

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

	if (!oScore.LoadStudent(nId, oStudentData)) {
		return;
	}

	CStudentDlg dlg(oStudentData, eDialogMode_View);

	if (dlg.DoModal() != IDOK) {
		return;
	}
}

void CTabStudent::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult) {
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
		oStudent.PrintStudent(m_listStudent);
	}

	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	for (auto& i = m_listStudent.begin(); i != m_listStudent.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).m_iStudentId));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).m_strName);
			m_listCtrl.SetItemText(nItemIndex, 2, oLib.OleDTToCString((*i).m_oleDTBirthday));
			m_listCtrl.SetItemText(nItemIndex, 3, (*i).m_strEmail);
			m_listCtrl.SetItemText(nItemIndex, 4, (*i).m_strPhoneNumber);
			m_listCtrl.SetItemText(nItemIndex, 5, (*i).m_strEgn);
			m_listCtrl.SetItemText(nItemIndex, 6, (*i).m_strCity);
			m_listCtrl.SetItemText(nItemIndex, 7, (*i).m_strPostCode);
			m_listCtrl.SetItemText(nItemIndex, 8, (*i).m_strNeighborhood);
			m_listCtrl.SetItemText(nItemIndex, 9, (*i).m_strAddress);
			
			//set index of back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)(*i).m_iStudentId);
		}
	}
}