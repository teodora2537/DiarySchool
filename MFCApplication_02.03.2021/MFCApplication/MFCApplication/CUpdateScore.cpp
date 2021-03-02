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
	CString m_strSubject(m_oScore.m_strSubject);
	CString m_strDate(m_oScore.m_strDate);
	CString m_strScore;
	m_strScore.Format("%d" ,m_oScore.m_iScore);

	m_strClassNum.Format("%d", m_oScore.m_iClassNum);
	m_strSubject = m_strSubject;
	m_strDate = m_strDate;
	m_strScore = m_strScore;
}

CUpdateScoreDlg::~CUpdateScoreDlg()
{
}

void CUpdateScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_DATE, m_strDate);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SCORE, m_strScore);
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

	CScoreData score(_ttoi(m_strClassNum), m_strSubject, _ttoi(m_strScore), m_strDate);

	CScore oScore;
	oScore.EditScore(score);

}
