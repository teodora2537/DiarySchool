// CTabScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabScore.h"
#include "afxdialogex.h"
#include "Score.h"
#include "CUpdateScore.h"
#include "Library.h"
#include <string.h>
#include <map>
#include <vector>
#include <list>
#include "CListMethods.h"

using namespace std;

// CTabScore dialog

IMPLEMENT_DYNAMIC(CTabScore, CDialogEx)

CTabScore::CTabScore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_SCORE, pParent)
{

}

CTabScore::~CTabScore()
{
}

void CTabScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTabScore, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_SCORE, OnAddScore)
	ON_BN_CLICKED(IDC_MENU_EDIT_SCORE, OnEditScore)
	ON_BN_CLICKED(IDC_MENU_DEL_SCORE, OnDeleteScore)
	ON_BN_CLICKED(IDC_MENU_VIEW_SCORE, OnViewScore)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST, &CTabScore::OnNMDblclkList)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CTabScore::OnLvnColumnclickList)
END_MESSAGE_MAP()

BOOL CTabScore::OnInitDialog() {

	if (!__super::OnInitDialog())
		return FALSE;

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, "Score", LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(4, "Date", LVCFMT_LEFT, 100);

	LoadDataFromFile();
	return true;
}

void CTabScore::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	bool bIsItemSelected = pos != NULL;

	CMenu submenu;
	submenu.CreatePopupMenu();
	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SCORE, "Add score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SCORE, "Edit score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SCORE, "Delete score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SCORE, "View score");

	//disable edit/delete/view from submenu
	submenu.EnableMenuItem(IDC_MENU_EDIT_SCORE, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_DEL_SCORE, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_VIEW_SCORE, !bIsItemSelected);

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CTabScore::OnAddScore()
{	
	CScore oScore;
	CScoreData oScoreData;

	oScoreData.m_iIdScore = m_listCtrl.GetItemCount() + 1;

	CScoreDlg dlg(oScoreData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oScore.AddScore(oScoreData))
		return;

	LoadDataFromFile();
}

void CTabScore::OnEditScore()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	
	//if don't get selected item
	if (nItem < 0)
		return;

	int nRoomId = (int)m_listCtrl.GetItemData(nItem);

	CScoreData oScoreData;

	CScore oScore;

	if (!oScore.LoadScore(nRoomId, oScoreData))
		return;

	CScoreDlg dlg(oScoreData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oScore.EditScore(oScoreData))
		return;

	LoadDataFromFile();
}

void CTabScore::OnDeleteScore()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	
	//if don't get selected item
	if (nItem < 0)
		return;

	CScore oScore;
	CString message;
	int nRoomId = (int)m_listCtrl.GetItemData(nItem);
	message.Format("Do you want to delete score with id # %d?", nRoomId);
	int result = MessageBox(message, "Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oScore.DeleteScore(nRoomId))
		return;

	m_listCtrl.DeleteItem(nItem);
}

void CTabScore::OnViewScore()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	
	//if don't get selected item
	if (nItem < 0)
		return;

	int nRoomId = (int)m_listCtrl.GetItemData(nItem);

	CScoreData oScoreData;

	CScore oScore;

	if (!oScore.LoadScore(nRoomId, oScoreData))
		return;

	CScoreDlg dlg(oScoreData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oScore.LoadScore(nRoomId, oScoreData))
		return;

	LoadDataFromFile();
}

void CTabScore::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewScore();
}

SortOrder idStudOrder = SORT_None;
SortOrder nameStudentOrder = SORT_None;
SortOrder subOrder = SORT_None;
SortOrder scoreOrder = SORT_None;
SortOrder dateOrder = SORT_None;
SortOrder sortOrderScore = SORT_None;

list<ScoreStruct> m_listScore;

void CTabScore::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int sortClmScore = -1;
	sortClmScore = pNMLV->iSubItem; //save column for the callback
	
	if (sortClmScore == 0) {
		if (idStudOrder == SORT_None)  idStudOrder = SORT_AZ;
		else idStudOrder = (SortOrder)-idStudOrder;
		sortOrderScore = idStudOrder;
	}
	else if (sortClmScore == 1) {
		if ( nameStudentOrder == SORT_None) nameStudentOrder = SORT_AZ;
		else nameStudentOrder = (SortOrder)-nameStudentOrder;
		sortOrderScore = nameStudentOrder;
	}
	else if (sortClmScore == 2) {
		if ( subOrder == SORT_None) subOrder = SORT_AZ;
		else subOrder = (SortOrder)-subOrder; 
		sortOrderScore = subOrder;
	}
	else if (sortClmScore == 3) {
		if ( scoreOrder == SORT_None) scoreOrder = SORT_AZ;
		else scoreOrder = (SortOrder)-scoreOrder;
		sortOrderScore = scoreOrder;
	}
	else if (sortClmScore == 4) {
		if ( dateOrder == SORT_None) dateOrder = SORT_AZ;
		else dateOrder = (SortOrder)-dateOrder; 
		sortOrderScore = dateOrder;
	}

	CListMethods oList;
	oList.SortListScore(sortClmScore, m_listScore, sortOrderScore);

	LoadDataFromStruct();

	*pResult = 0;
}

void CTabScore::LoadDataFromStruct()
{
	m_listCtrl.DeleteAllItems();
	
	Library oLib;
	int nCount = 0;
	int nItemIndex = 0;
	
	for (list<ScoreStruct>::iterator it = m_listScore.begin(); it != m_listScore.end(); it++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->nIdStudent));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->strNameStudent);
			m_listCtrl.SetItemText(nItemIndex, 2, it->strSubject);
			m_listCtrl.SetItemText(nItemIndex, 3, it->strScore);
			m_listCtrl.SetItemText(nItemIndex, 4, it->strDate);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->nIdScore);
		}
	}
}

void CTabScore::LoadDataFromFile()
{
	m_listCtrl.DeleteAllItems();
	m_listScore.clear();
	
	Library oLib;
	int nCount = 0;
	int nItemIndex = 0;
	CScore oScore;
	oScore.Print_Score(m_listScore);

	for (auto it = m_listScore.begin(); it != m_listScore.end(); it++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();
		
		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->nIdStudent));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->strNameStudent);
			m_listCtrl.SetItemText(nItemIndex, 2, it->strSubject);
			m_listCtrl.SetItemText(nItemIndex, 3, it->strScore);
			m_listCtrl.SetItemText(nItemIndex, 4, it->strDate);
		
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->nIdScore);
		}
	}
}