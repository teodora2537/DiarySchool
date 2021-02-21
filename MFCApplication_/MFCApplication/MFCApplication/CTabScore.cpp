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
	multimap<int, vector<string>> mapScore = oScore.PrintScore();
	
	m_iRow = 0;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Score", LVCFMT_LEFT, 50);
	m_listCtrl.InsertColumn(4, L"Date", LVCFMT_LEFT, 100);

	for (auto i = mapScore.begin(); i != mapScore.end(); i++)
	{
		string m_strNumber = to_string((*i).first);
		string m_strName = (*i).second[0];
		string m_strSubject = (*i).second[1];
		string m_strScore = (*i).second[2];
		string m_strDate = (*i).second[3];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrName(m_strName.c_str());
		CString m_cstrSubject(m_strSubject.c_str());
		CString m_cstrScore(m_strScore.c_str());
		CString m_cstrDate(m_strDate.c_str());

		m_listCtrl.InsertItem(m_iRow, m_cstrNumber);
		m_listCtrl.SetItemText(m_iRow, 1, m_cstrName);
		m_listCtrl.SetItemText(m_iRow, 2, m_cstrSubject);
		m_listCtrl.SetItemText(m_iRow, 3, m_cstrScore);
		m_listCtrl.SetItemText(m_iRow, 4, m_cstrDate);
		m_iRow++;
	}

	return true;
}

