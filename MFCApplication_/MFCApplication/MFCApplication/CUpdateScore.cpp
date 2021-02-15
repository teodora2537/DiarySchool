// CUpdateScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateScore.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Score.h"


// CUpdateScore dialog

IMPLEMENT_DYNAMIC(CUpdateScoreDlg, CDialogEx)

CUpdateScoreDlg::CUpdateScoreDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_SCORE, pParent)
{
	Library lib;
	Score m_oScore;
	CString m_cstrSubject(m_oScore.GetSubject().c_str());
	CString m_cstrDate(m_oScore.GetDate().c_str());
	CString m_cstrScore;
	m_cstrScore.Format(L"%d" ,m_oScore.GetScore());

	classNum.Format(L"%d", m_oScore.GetClassNum());
	subject = m_cstrSubject;
	date = m_cstrDate;
	score = m_cstrScore;
}

CUpdateScoreDlg::~CUpdateScoreDlg()
{
}

void CUpdateScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, classNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SUBJECT, subject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_DATE, date);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SCORE, score);
}


BEGIN_MESSAGE_MAP(CUpdateScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateScoreDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();

	UpdateData(TRUE);
	Library lib;
	string row = "";

	Score score(_ttoi(classNum), lib.ConvertToStirng(subject, row), _ttoi(score), lib.ConvertToStirng(date, row));

	lib.UpdateScore();
}
