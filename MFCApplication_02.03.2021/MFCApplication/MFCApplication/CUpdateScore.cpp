// CUpdateScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateScore.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Score.h"
#include "CTabStudent.h"
#include <string> 

// CUpdateScore dialog

IMPLEMENT_DYNAMIC(CScoreDlg, CDialogEx)

CScoreDlg::CScoreDlg(CScoreData& oScore, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_UPDATE_SCORE, NULL)
	, m_oScore(oScore)
	, m_eMode(eMode)
{
}

CScoreDlg::~CScoreDlg()
{
}

void CScoreDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	
	//CString
	
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	DDV_MaxChars(pDX, m_strClassNum, 2);//Size of class number
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SUBJECT, m_strSubject);	
	DDV_MaxChars(pDX, m_strSubject, 20);//Size of subject
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SCORE, m_strScore);
	DDV_MaxChars(pDX, m_strScore, 1);//Size of score
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_DATE, m_strDate);
	DDV_MaxChars(pDX, m_strDate, 10);//Size of score
	DDX_Text(pDX, IDC_STATIC7, m_strStaticText);
	
	//class number between 1 - count student
	CStudent oStudent;
	DDV_MinMaxInt(pDX, atoi(m_strClassNum), 1, oStudent.CountStudent());	

	/*
	CEdit *pEdit = // get your control here ...
	pEdit->ModifyStyle(0, ES_NUMBER);
	*/
}

/*virtual*/
BOOL CScoreDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;
	//m_strSubject.ReleaseBufferSetLength(5);
	BOOL bEnable = m_eMode != eDialogMode_View;
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_SUBJECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_SCORE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_DATE)->EnableWindow(bEnable);

	m_strClassNum.Format("%d", m_oScore.m_iClassNum);
	m_strScore.Format("%d",m_oScore.m_iScore);
	m_strSubject = m_oScore.m_strSubject;
	//here saet data format
	m_strDate = m_oScore.m_strDate;

	if (m_eMode == eDialogMode_Add)
	{
		SetDlgItemText(IDC_STATIC7, "Add score");
		GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(TRUE);

		m_strClassNum.Empty();
		m_strScore.Empty();
		m_strDate = currentDate;
	}
	else if (m_eMode == eDialogMode_Edit)
		SetDlgItemText(IDC_STATIC7, "Update score");
	else if (m_eMode == eDialogMode_View)
		SetDlgItemText(IDC_STATIC7, "Score");

	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_SUBJECT, m_strSubject);
	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_SCORE, m_strScore);
	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_DATE, m_strDate);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreDlg::OnBnClickedOk)
	ON_EN_MAXTEXT(IDC_EDIT_UPDATE_SCORE_SUBJECT, &CScoreDlg::OnEnMaxtextEditUpdateScoreSubject)
END_MESSAGE_MAP()

BOOL CScoreDlg::ValidateData()
{

	//empty subject
	if (m_strSubject.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}

	//empty or incorect score
	if (m_strScore.IsEmpty())
	{
		MessageBox("Missing score!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (atoi(m_strScore) < 2 || atoi(m_strScore) > 6)
	{
		MessageBox("The score must be between 2 and 6!", "Incorect score");
		return false;
	}
	
	//empty or incorect date
	COleDateTime date;
	date.ParseDateTime(m_strDate, 0, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	if (m_strDate.IsEmpty())
	{
		MessageBox("Missing date!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (date.GetStatus() || m_strDate[2] != '/' || m_strDate[5] != '/')
	{
		MessageBox("Please input correct date!", "Incorect date" );
		return false;
	}
	else if (date.GetYear() > oleDate.GetYear() || date.GetMonth() > oleDate.GetMonth() || date.GetDay() > oleDate.GetDay())
	{
		MessageBox("Please input today date or preview date!", "Incorect date");
		return false;
	}
	
	return TRUE;
}

void CScoreDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (!ValidateData())
		return;


	m_oScore.m_iClassNum = atoi(m_strClassNum);
	m_oScore.m_strSubject = m_strSubject;
	m_oScore.m_iScore = atoi(m_strScore);
	m_oScore.m_strDate = m_strDate;

	CDialogEx::OnOK();
}

void CScoreDlg::OnEnMaxtextEditUpdateScoreSubject()
{
	// TODO: Add your control notification handler code here
}
