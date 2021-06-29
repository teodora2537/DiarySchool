#include "pch.h"
#include "MFCApplication.h"
#include "CTabSubject.h"
#include "Subject.h"
using namespace std;

IMPLEMENT_DYNAMIC(CTabSubject, CDialogEx)

CTabSubject::CTabSubject()
	: CDialogEx(IDD_TAB_SUBJECT)
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
END_MESSAGE_MAP()

BOOL CTabSubject::OnInitDialog() {

	if (!__super::OnInitDialog())
		return FALSE;

	m_listCtrl.SetBkColor(GetSysColor(COLOR_3DFACE));
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Subject", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Teacher", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	
	LoadData(true);

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i)
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

	return true;
}

void CTabSubject::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
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

	oSubject.GetLastId(oSubjectData);

	CSubjectDlg dlg(oSubjectData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oSubject.AddSubject(oSubjectData))
	{
		if (IDRETRY)
			OnAddSubject();
		return;
	}

	LoadData(true);
}

void CTabSubject::OnEditSubject()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	/*Нямам нужда от тази проверка, защото ,мога да Edit-вам само селектиран елемен, иначе са ми disable*/
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

	CSubjectData oSubjectData;
	CSubject oSubject;

	if (!oSubject.LoadSubject(nId, oSubjectData))
		return;

	CSubjectDlg dlg(oSubjectData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oSubject.EditSubject(oSubjectData))
	{
		MessageBox("The subject not updated!", "Error", MB_RETRYCANCEL | MB_ICONERROR);
		if (IDRETRY)
			OnEditSubject();
		return;
	}

	LoadData(true);
}

void CTabSubject::OnDeleteSubject()
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

	CSubject oSubject;

	CString message;
	message.Format("Do you want to delete subject with room # %d?", nId);
	int result = MessageBox(message, "Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oSubject.DeleteSubject(nId))
		return;

	m_listCtrl.DeleteItem(nItem);
}

void CTabSubject::OnViewSubject()
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

	CSubjectData oSubjectData;
	CSubject oSubject;

	if (!oSubject.LoadSubject(nId, oSubjectData))
		return;

	CSubjectDlg dlg(oSubjectData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;
}

void CTabSubject::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewSubject();
}

void CTabSubject::LoadData(bool isFromFile)
{
	m_listCtrl.DeleteAllItems();
	
	if (isFromFile)
	{
		m_listSubject.clear();
		CSubject oSubject;
		oSubject.PrintSubject(m_listSubject);
	}
	
	Library oLib; 
	
	int nCount = 0;
	int nItemIndex = 0;
	
		for (auto& it = m_listSubject.begin(); it != m_listSubject.end(); it++) 
		{
			//get Count list items
			nCount = m_listCtrl.GetItemCount();
		
			nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->iId));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->szSubject);
			m_listCtrl.SetItemText(nItemIndex, 2, it->szTeacher);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->iId);
		}
	}
}