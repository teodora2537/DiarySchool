// CTabScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabScore.h"
#include "afxdialogex.h"
#include "Score.h"
#include "CUpdateScore.h"
#include "Library.h"


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
END_MESSAGE_MAP()

BOOL CTabScore::OnInitDialog() {

	CDialogEx::OnInitDialog();

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
	//if not sected
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
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	//if not sected
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//if don't get selected item
	if (nItem < 0)
		return;

	CScoreData oScoreData;

	CScore oScore;

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
	//if not sected
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
	//if not selected
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
	//if not selected
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

void CTabScore::GetScoreFromDlg()
{
	Library oLib;

	CString m_strClassNum = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	CString m_strSubject  = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	CString m_strDate	   = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);
	CString m_strScore	   = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 3);

	CScoreData score(_ttoi(m_strClassNum), m_strSubject, _ttoi(m_strScore), m_strDate);
	score.m_iIdScore =  m_listCtrl.GetSelectionMark() + 1;
}

void CTabScore::LoadDataFromFile()
{
	m_listCtrl.DeleteAllItems();
	CScore oScore;
	map<int, vector<CString>> mapScore;
	oScore.PrintScore(mapScore);

	int nCount = 0;
	int nItemIndex = 0;

	for (auto i = mapScore.begin(); i != mapScore.end(); i++)
	{
		string m_strNumber = (*i).second[0];
		string m_strName = (*i).second[1];
		string m_strSubject = (*i).second[2];
		string m_strScore = (*i).second[3];
		string m_strDate = (*i).second[4];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrName(m_strName.c_str());
		CString m_cstrSubject(m_strSubject.c_str());
		CString m_cstrScore(m_strScore.c_str());
		CString m_cstrDate(m_strDate.c_str());

		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, m_cstrNumber);


		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, m_cstrName); 
			m_listCtrl.SetItemText(nItemIndex, 2, m_cstrSubject);
			m_listCtrl.SetItemText(nItemIndex, 3, m_cstrScore);
			m_listCtrl.SetItemText(nItemIndex, 4, m_cstrDate);
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->first);
		}
	}
}

void CTabScore::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewScore();
}
