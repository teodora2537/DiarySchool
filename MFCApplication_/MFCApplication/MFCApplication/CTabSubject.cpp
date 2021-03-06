// CTabSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabSubject.h"
#include "afxdialogex.h"
#include "Subject.h"
#include "CAddSubject.h"
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

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	LoadDataFromFile(m_listCtrl);

	/*
	// na edna fuknciq LoadDataFromFile ili ne6to takova
	m_listCtrl.DeleteAllItems();

	CSubject oSubject;
	map<int, vector<CString>> m_mapSubjects;
	oSubject.PrintSubject(m_mapSubjects);

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Teacher", LVCFMT_LEFT, 100);

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
		
		nItemIndex = m_listCtrl.InsertItem(nCount - 1, m_cstrNumber);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, m_cstrSubject);
			m_listCtrl.SetItemText(nItemIndex, 2, m_cstrTeacher);
			
			m_listCtrl.SetItemData(nItemIndex, (DWORD_PTR)i->first);
		}
	}
	// na edna fuknciq LoadDataFromFile ili ne6to takova
	*/
	return true;
}

void CTabSubject::OnContextMenu(CWnd* pWnd, CPoint point)
{
	
	if ((m_listCtrl.GetSelectionMark() + 1) == 0)
		return;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SUBJECT, "Add subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SUBJECT, "Edit subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SUBJECT, "Delete subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SUBJECT, "View subject");

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	
}

void CTabSubject::OnAddSubject()
{
	
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not sected
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//if don't get selected item
	if (nItem < 0)
		return;

	//int nRoomId = (int)m_listCtrl.GetItemData(nItem); //0 - always

	CSubjectData oSubjectData;

	CSubject oSubject;

	oSubjectData.m_iRoomNumber = m_listCtrl.GetItemCount()+1;

	CAddSubjectDlg dlg(oSubjectData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oSubject.AddSubject(oSubjectData))
		return;
	LoadDataFromFile(m_listCtrl);

	/*
	//Set Enable room
	map<int, vector<CString>> mapAllSubjects;
	CSubject oSubject;
	oSubject.PrintSubject(mapAllSubjects);
	CSubjectData oSubjectData;
	CString m_cstrRow;
	m_cstrRow.Format("%d", mapAllSubjects.size() + 1);

	GetSubjectFromDlg();
	CAddSubjectDlg dlg(oSubjectData, eDialogMode_View);
	//CAddSubjectDlg dlg;
	dlg.m_cstrRoomNum = m_cstrRow;
	
	dlg.DoModal();

	if (dlg.m_cstrRoomNum != "" && dlg.m_cstrSubject != "" && dlg.m_cstrFnTeacher != "" && dlg.m_cstrLnTeacher != "")
	{
		//Add item with dlg datas
		int n = m_listCtrl.GetItemCount();
		n = m_listCtrl.InsertItem(n, dlg.m_cstrRoomNum);
		m_listCtrl.SetItemText(n, 1, dlg.m_cstrSubject);
		m_listCtrl.SetItemText(n, 2, dlg.m_cstrFnTeacher + " " + dlg.m_cstrLnTeacher);
	}
	*/

}

//!!!WORK!!!
void CTabSubject::OnEditSubject()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not sected
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//if don't get selected item
	if (nItem < 0)
		return;

	//int nRoomId = (int)m_listCtrl.GetItemData(nItem); //0 - always

	CSubjectData oSubjectData;

	CSubject oSubject;

	if (!oSubject.LoadSubject(nItem+1, oSubjectData))
		return;

	CUpdateSubjectDlg dlg(oSubjectData, eDialogMode_Edit);
	
	if (dlg.DoModal() != IDOK)
		return;
	

	if (!oSubject.EditSubject(oSubjectData))
		return;

	LoadDataFromFile(m_listCtrl);
}
//!!!WORK!!!
void CTabSubject::OnDeleteSubject() 
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	if (nItem < 0)
		return;

	//int nRoomId = (int)m_listCtrl.GetItemData(nItem); always == 0

	CSubject oSubject;

	CString message;
	message.Format("Do you want to delete subject with room # %d?", nItem+1); // nRoomId
	int result = MessageBox(message, "Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oSubject.DeleteSubject(nItem+1)) // nRoomId
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

	//int nRoomId = (int)m_listCtrl.GetItemData(nItem); //0 - always

	CSubjectData oSubjectData;

	CSubject oSubject;

	if (!oSubject.LoadSubject(nItem + 1, oSubjectData))
		return;

	CUpdateSubjectDlg dlg(oSubjectData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oSubject.LoadSubject(nItem+1,oSubjectData))
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

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Teacher", LVCFMT_LEFT, 100);

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

			//nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->first); don't show datas
		}
	}
}