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
	//Library oLib;
	CScoreData m_oScore;
	CString m_cstrSubject(m_oScore.GetSubject().c_str());
	CString m_cstrDate(m_oScore.GetDate().c_str());
	CString m_cstrScore;
	m_cstrScore.Format(L"%d" ,m_oScore.GetScore());

	m_cstrClassNum.Format(L"%d", m_oScore.GetClassNum());
	m_cstrSubject = m_cstrSubject;
	m_cstrDate = m_cstrDate;
	m_cstrScore = m_cstrScore;
}

CUpdateScoreDlg::~CUpdateScoreDlg()
{
}

void CUpdateScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_cstrClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SUBJECT, m_cstrSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_DATE, m_cstrDate);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SCORE, m_cstrScore);
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

	CScoreData score(_ttoi(m_cstrClassNum), lib.ConvertToStirng(m_cstrSubject, row), _ttoi(m_cstrScore), lib.ConvertToStirng(m_cstrDate, row));

	CScore oScore;
	oScore.EditScore(score);

}
