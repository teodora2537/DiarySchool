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
END_MESSAGE_MAP()

BOOL CTabSubject::OnInitDialog() {

	CDialogEx::OnInitDialog();

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CSubject oSubject;
	map<int, vector<string>> m_mapSubjects = oSubject.PrintSubject();
	string str;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Teacher", LVCFMT_LEFT, 100);

	for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
	{
		string m_strNumber = to_string((*i).first);
		string m_strSubject = (*i).second[0];
		string m_strTeacher = (*i).second[1] + " " + (*i).second[2];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrSubject(m_strSubject.c_str());
		CString m_cstrTeacher(m_strTeacher.c_str());

		m_listCtrl.InsertItem((*i).first - 1, m_cstrNumber);
		m_listCtrl.SetItemText((*i).first - 1, 1, m_cstrSubject);
		m_listCtrl.SetItemText((*i).first - 1, 2, m_cstrTeacher);
	}
	return true;
}

void CTabSubject::OnContextMenu(CWnd* pWnd, CPoint point)
{
	
	if ((m_listCtrl.GetSelectionMark() + 1) == 0)
		return;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SUBJECT, L"Add subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SUBJECT, L"Edit subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SUBJECT, L"Delete subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SUBJECT, L"View subject");

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
	
}

void CTabSubject::OnAddSubject()
{
	//Set Enable room
	CSubject oSubject;
	CString m_cstrRow;
	m_cstrRow.Format(L"%d", oSubject.PrintSubject().size() + 1);

	GetSubjectFromDlg();
	CAddSubjectDlg dlg;
	dlg.m_cstrRoomNum = m_cstrRow;
	dlg.DoModal();
	
	//Add item with dlg datas
	int n = m_listCtrl.GetItemCount();
	n = m_listCtrl.InsertItem(n, dlg.m_cstrRoomNum);
	m_listCtrl.SetItemText(n, 1, dlg.m_cstrSubject);
	m_listCtrl.SetItemText(n, 2, dlg.m_cstrFnTeacher+" "+ dlg.m_cstrLnTeacher);
}

void CTabSubject::OnEditSubject()
{
	CSubjectData oSubjectData;
	oSubjectData.SetFlagIsUpdate(true);
	GetSubjectFromDlg();
	CUpdateSubjectDlg dlg;
	dlg.m_cstrRoomNum = m_cstrId;
	dlg.m_cstrSubject = m_cstrSubject;
	dlg.m_cstrFN = m_cstrFirstName;
	dlg.m_cstrLN = m_cstrLastName;
	dlg.m_cstrStaticText = "Update subject";
	dlg.DoModal();

	//Add item with dlg datas
	int n = _ttoi(m_cstrId);
	n = m_listCtrl.InsertItem(n, dlg.m_cstrRoomNum);
	m_listCtrl.SetItemText(n, 1, dlg.m_cstrSubject);
	m_listCtrl.SetItemText(n, 2, dlg.m_cstrFN + " " + dlg.m_cstrLN);

	//Delete select item
	for (int nItem = 0; nItem < m_listCtrl.GetItemCount(); )
	{
		if (m_listCtrl.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
			m_listCtrl.DeleteItem(nItem);
		else
			++nItem;
	}
}

void CTabSubject::OnDeleteSubject() {
	GetSubjectFromDlg();
	CSubjectData oSubjectData;
	CString message;
	message.Format(L"Do you want to delete %s with room ¹ %s?", m_cstrSubject, m_cstrId);
	int result = MessageBox(message, L"Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	UpdateData(TRUE);
	CSubject oSubject;
	oSubject.DeleteSubject(oSubjectData.GetRoomNumber());
	
	//Delete select item
	for (int nItem = 0; nItem < m_listCtrl.GetItemCount(); )
	{
		if (m_listCtrl.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
			m_listCtrl.DeleteItem(nItem);
		else
			++nItem;
	}
}

void CTabSubject::OnViewSubject()
{
	CSubjectData oSubjectData;
	oSubjectData.SetFlagIsUpdate(false);
	GetSubjectFromDlg();
	CUpdateSubjectDlg dlg;
	dlg.m_cstrRoomNum = m_cstrId;
	dlg.m_cstrSubject = m_cstrSubject;
	dlg.m_cstrFN = m_cstrFirstName;
	dlg.m_cstrLN = m_cstrLastName;
	dlg.m_cstrStaticText = "Subject";
	dlg.DoModal();
}

void CTabSubject::GetSubjectFromDlg()
{
	m_cstrId = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	m_cstrSubject = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	CString m_cstrTeacher = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);

	m_cstrFirstName = L"";
	m_cstrLastName = L"";
	m_nTokenPos = 0;
	m_iCount = 0;
	Library lib;
	CString strToken = m_cstrTeacher.Tokenize(_T(" "), m_nTokenPos);

	while (!strToken.IsEmpty())
	{
		if (m_iCount == 0)
		{
			m_cstrFirstName = strToken;
			m_iCount++;
		}
		else if (m_iCount == 1)
		{
			m_cstrLastName = strToken;
		}
		strToken = m_cstrTeacher.Tokenize(_T(" "), m_nTokenPos);
	}
	CSubjectData sub(_ttoi(m_cstrId), m_cstrSubject, lib.ConvertToStirng(m_cstrFirstName, ""), lib.ConvertToStirng(m_cstrLastName, ""));
	sub.SetFullNameTeacher(m_cstrTeacher);
}
