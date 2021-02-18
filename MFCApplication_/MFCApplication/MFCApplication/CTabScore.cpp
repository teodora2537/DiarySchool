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
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Date", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Score", LVCFMT_LEFT, 50);

	for (auto i = mapScore.begin(); i != mapScore.end(); i++)
	{
		string number = to_string((*i).first);
		string subject = (*i).second[0];
		string date = (*i).second[2];
		string score = (*i).second[1];

		CString cstrNumber(number.c_str());
		CString cstrSubject(subject.c_str());
		CString cstrDate(date.c_str());
		CString cstrScore(score.c_str());

		m_listCtrl.InsertItem(row, cstrNumber);
		m_listCtrl.SetItemText(row, 1, cstrSubject);
		m_listCtrl.SetItemText(row, 2, cstrDate);
		m_listCtrl.SetItemText(row, 3, cstrScore);
		row++;
	}

	return true;
}

