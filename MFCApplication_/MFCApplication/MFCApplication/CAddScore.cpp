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
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_CLASS_NUMBER, classNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_SUBJECT, subject);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_DATE, date);
	DDX_Text(pDX, IDC_EDIT_ADD_SCORE_SCORE, score);
}


BEGIN_MESSAGE_MAP(CAddScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddScore message handlers


void CAddScoreDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	UpdateData(TRUE);
	Library lib;
	string row = "";

	int i_classNum = _ttoi(classNum);
	int i_score = _ttoi(score);
	string str_sub = lib.ConvertToStirng(subject, row);
	string str_date = lib.ConvertToStirng(date, row);


	Score score(_ttoi(classNum), lib.ConvertToStirng(subject, row), _ttoi(score), lib.ConvertToStirng(date, row));

	//Success Add
	lib.AddInScore();

}
