#include "pch.h"
#include "CTabScore.h"

IMPLEMENT_DYNAMIC(CTabScore, CDialogEx)

CTabScore::CTabScore()
	: CDialogEx(IDD_DIALOG_TAB_SCORE)
{

}

CTabScore::~CTabScore()
{
}

/*virtual*/
void CTabScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_SCORE, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTabScore, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_SCORE, OnAddScore)
	ON_BN_CLICKED(IDC_MENU_EDIT_SCORE, OnEditScore)
	ON_BN_CLICKED(IDC_MENU_DEL_SCORE, OnDeleteScore)
	ON_BN_CLICKED(IDC_MENU_VIEW_SCORE, OnViewScore)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_SCORE, &CTabScore::OnNMDblclkList)
END_MESSAGE_MAP()

/*virtual*/
BOOL CTabScore::OnInitDialog() {

	if (!__super::OnInitDialog())
		return FALSE;

	m_listCtrl.SetBkColor(GetSysColor(COLOR_3DFACE));
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Subject", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Score", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Date", eListCtrlColumnTypeData_Date, LVCFMT_LEFT);

	LoadData();

	return TRUE;
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

	if (dlg.DoModal() != IDOK) {
		return;
	}

	if (!oScore.AddScore(oScoreData)) 
	{	
		if (IDRETRY) {
			OnAddScore();
		}
		return;
	}

	LoadData();
}

void CTabScore::OnEditScore()
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

	CScoreData oScoreData;
	oScoreData.m_iIdScore = nId;
	CScore oScore;

	if (!oScore.LoadScore(nId, oScoreData)) {
		return;
	}
	
	CScoreDlg dlg(oScoreData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK) {
		return;
	}

	if (!oScore.EditScore(oScoreData)) 
	{
		if (IDRETRY) { 
			OnEditScore();
		}

		return;
	}

	LoadData();
}

void CTabScore::OnDeleteScore()
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

	CString message;
	message.Format("Do you want to delete score with id # %d?", nId);
	int result = MessageBox(message, "Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES) {
		return;
	}

	CScore oScore;
	if (!oScore.DeleteScore(nId)) {
		return;
	}
	
	m_listCtrl.DeleteItem(nItem);
}

void CTabScore::OnViewScore()
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

	CScoreData oScoreData;

	CScore oScore;

	if (!oScore.LoadScore(nId, oScoreData)) {
		return;
	}

	CScoreDlg dlg(oScoreData, eDialogMode_View);

	if (dlg.DoModal() != IDOK) {
		return;
	}
}

void CTabScore::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult) {
	OnViewScore();
}


void CTabScore::LoadData() 
{
	

	m_listCtrl.DeleteAllItems();

		m_listScore.clear();
		CScore oScore;
		oScore.Print_Score(m_listScore);

	if (m_listScore.size() == 0) {
		MessageBox("The list score is empty!", "Error", MB_OK | MB_ICONERROR);
	}

	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	for (auto& it = m_listScore.begin(); it != m_listScore.end(); it++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->m_iIdStudent));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->m_strNameStudent);
			m_listCtrl.SetItemText(nItemIndex, 2, it->m_strSubject);
			m_listCtrl.SetItemText(nItemIndex, 3, oLib.IntToCString(it->m_iScore));
			m_listCtrl.SetItemText(nItemIndex, 4, oLib.OleDTToCString(it->m_oleDateTime));

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->m_iIdScore);
		}
	}

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}
