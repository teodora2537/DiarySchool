// CTabSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabSubject.h"
#include "afxdialogex.h"
#include "Subject.h"
#include "CUpdateSubject.h"
#include "Library.h"

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
END_MESSAGE_MAP()

BOOL CTabSubject::OnInitDialog() {

	CDialogEx::OnInitDialog();

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
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not selected
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//if don't get selected item
	if (nItem < 0)
		return;

	CSubjectData oSubjectData;

	CSubject oSubject;

	oSubjectData.m_iRoomNumber = m_listCtrl.GetItemCount()+1;

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


	if (!oSubject.LoadSubject(nRoomId,oSubjectData))
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

void CTabSubject::LoadDataFromFile(CListCtrl& m_listCtrl)
{
	m_listCtrl.DeleteAllItems();
	CSubject oSubject;
	map<int, vector<CString>> m_mapSubjects;
	oSubject.PrintSubject(m_mapSubjects);

	int nCount = 0;
	int nItemIndex = 0;

	for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
	{
		string m_strNumber = to_string((*i).first);
		string m_strSubject = (*i).second[0];
		string m_strTeacher = (*i).second[1] + " " + (*i).second[2];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrSubject(m_strSubject.c_str());
		CString m_cstrTeacher(m_strTeacher.c_str());
		
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

			nItemIndex = m_listCtrl.InsertItem(nCount, m_cstrNumber);
		
		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, m_cstrSubject);
			m_listCtrl.SetItemText(nItemIndex, 2, m_cstrTeacher);
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->first);
		}
	}
}