// CTabScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabScore.h"
#include "afxdialogex.h"
#include "Score.h"


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
END_MESSAGE_MAP()

BOOL CTabScore::OnInitDialog() {

	CDialogEx::OnInitDialog();

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	CScore oScore;
	//Library lib;
	multimap<int, vector<string>> mapScore = oScore.PrintScore();
	string str;
	int row = 0;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Date", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(4, L"Score", LVCFMT_LEFT, 50);

	for (auto i = mapScore.begin(); i != mapScore.end(); i++)
	{
		string number = to_string((*i).first);
		string name = (*i).second[0];
		string subject = (*i).second[1];
		string score = (*i).second[2];
		string date = (*i).second[3];

		CString cstrNumber(number.c_str());
		CString cstrName(name.c_str());
		CString cstrSubject(subject.c_str());
		CString cstrScore(score.c_str());
		CString cstrDate(date.c_str());

		m_listCtrl.InsertItem(row, cstrNumber);
		m_listCtrl.SetItemText(row, 1, cstrName);
		m_listCtrl.SetItemText(row, 2, cstrSubject);
		m_listCtrl.SetItemText(row, 3, cstrDate);
		m_listCtrl.SetItemText(row, 4, cstrScore);
		row++;
	}

	return true;
}



void CTabScore::OnContextMenu(CWnd* pWnd, CPoint point)
{
	int m_nItem = m_listCtrl.GetSelectionMark() + 1;

	if (m_nItem == 0)
		return;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SCORE, L"Add score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SCORE, L"Edit score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SCORE, L"Delete score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SCORE, L"View score");

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}
