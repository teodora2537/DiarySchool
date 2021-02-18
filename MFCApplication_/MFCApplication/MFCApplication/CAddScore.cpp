// CAddScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CAddScore.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Score.h"


// CAddScore dialog

IMPLEMENT_DYNAMIC(CAddScoreDlg, CDialogEx)

CAddScoreDlg::CAddScoreDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_SCORE, pParent)
{

}

CAddScoreDlg::~CAddScoreDlg()
{
}

void CAddScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_CLASS_NUMBER, m_cstrClassNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_SUBJECT, m_cstrSubject);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_DATE, m_cstrDate);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_SCORE, m_cstrScore);
}


BEGIN_MESSAGE_MAP(CAddScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddScore message handlers


void CAddScoreDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
	UpdateData(TRUE);
	Library lib;
	string row = "";
	CScore oScore;

	CScoreData score(_ttoi(m_cstrClassNum), lib.ConvertToStirng(m_cstrSubject, row), _ttoi(m_cstrScore), lib.ConvertToStirng(m_cstrDate, row));

	oScore.AddScore(score);
}
