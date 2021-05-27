#include "pch.h"
#include "MFCApplication.h"
#include "CTabScore.h"
#include "Score.h"
using namespace std;

IMPLEMENT_DYNAMIC(CTabScore, CDialogEx)

CTabScore::CTabScore()
	: CDialogEx(IDD_TAB_SCORE)
{

}

CTabScore::~CTabScore()
{
}

/*virtual*/
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

/*virtual*/
BOOL CTabScore::OnInitDialog() {

	if (!__super::OnInitDialog())
		return FALSE;

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, "Score", LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(4, "Date", LVCFMT_LEFT, 100);

	LoadData(true);
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
	CScoreData oScoreData;
	CScore oScore;

	oScore.GetLastId(oScoreData);

	CScoreDlg dlg(oScoreData, eDialogMode_Add);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oScore.AddScore(oScoreData)) 
	{	
		//MessageBox("The score not added!", "Error", MB_RETRYCANCEL | MB_ICONERROR);

		if (IDRETRY)
			OnAddScore();
		return;
	}

	LoadData(true);
}

void CTabScore::OnEditScore()
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

	CScoreData oScoreData;
	oScoreData.m_iIdScore = nId;
	CScore oScore;

	if (!oScore.LoadScore(nId, oScoreData))
		return;
	
	CScoreDlg dlg(oScoreData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;

	if (!oScore.EditScore(oScoreData)) 
	{
		//MessageBox("The score not updated!", "Error", MB_RETRYCANCEL | MB_ICONERROR);

		if (IDRETRY)
			OnEditScore();
		return;
	}

	LoadData(true);
}

void CTabScore::OnDeleteScore()
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

	CScore oScore;
	CString message;
	message.Format("Do you want to delete score with id # %d?", nId);
	int result = MessageBox(message, "Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oScore.DeleteScore(nId))
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
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CScoreData oScoreData;

	CScore oScore;

	if (!oScore.LoadScore(nId, oScoreData))
		return;

	CScoreDlg dlg(oScoreData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;


	//if (!oScore.LoadScore(nId, oScoreData))
	//	return;
	//
	//LoadData(true);
}

void CTabScore::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewScore();
}

void CTabScore::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int sortClm = -1;
	sortClm = pNMLV->iSubItem; //save column for the callback
	
	if (sortClm == 0) {
		if (m_idStudOrder == SORT_None)  m_idStudOrder = SORT_AZ;
		else m_idStudOrder = (SortOrder) - m_idStudOrder;
		m_sortOrderScore = m_idStudOrder;
	}
	else if (sortClm == 1) {
		if (m_nameStudentOrder == SORT_None) m_nameStudentOrder = SORT_AZ;
		else m_nameStudentOrder = (SortOrder) - m_nameStudentOrder;
		m_sortOrderScore = m_nameStudentOrder;
	}
	else if (sortClm == 2) {
		if (m_subOrder == SORT_None) m_subOrder = SORT_AZ;
		else m_subOrder = (SortOrder) - m_subOrder; 
		m_sortOrderScore = m_subOrder;
	}
	else if (sortClm == 3) {
		if (m_scoreOrder == SORT_None) m_scoreOrder = SORT_AZ;
		else m_scoreOrder = (SortOrder) - m_scoreOrder;
		m_sortOrderScore = m_scoreOrder;
	}
	else if (sortClm == 4) {
		if (m_dateOrder == SORT_None) m_dateOrder = SORT_AZ;
		else m_dateOrder = (SortOrder) - m_dateOrder; 
		m_sortOrderScore = m_dateOrder;
	}

	CListMethods oList;
	oList.SortListScore(sortClm, m_listScore, m_sortOrderScore);

	LoadData(false);

	*pResult = 0;
}

void CTabScore::LoadData(bool isFromFile) {
	
	m_listCtrl.DeleteAllItems();

	if (isFromFile) {
		m_listScore.clear();
		CScore oScore;
		oScore.Print_Score(m_listScore);
	}

	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	for (auto& it = m_listScore.begin(); it != m_listScore.end(); it++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->iClassNum));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->szName);
			m_listCtrl.SetItemText(nItemIndex, 2, it->szSubject);
			m_listCtrl.SetItemText(nItemIndex, 3, oLib.IntToCString(it->iScore));
			m_listCtrl.SetItemText(nItemIndex, 4, it->szDate);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->iId);
		}
	}
}