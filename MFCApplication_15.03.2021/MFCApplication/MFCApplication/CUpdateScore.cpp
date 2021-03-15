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
#include "Subject.h"

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
	
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	DDV_MaxChars(pDX, m_strClassNum, 2);//Size of class number
	//class number between 1 - count student
	CStudent oStudent;
	DDV_MinMaxInt(pDX, atoi(m_strClassNum), 1, oStudent.CountStudent());	
	
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_SCORE, m_strScore);
	DDV_MaxChars(pDX, m_strScore, 1);//Size of score
	DDV_MinMaxInt(pDX, atoi(m_strScore), 2, 6);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SCORE_DATE, m_strDate);
	DDV_MaxChars(pDX, m_strDate, 10);//Size of date
	DDX_Text(pDX, IDC_STATIC7, m_strStaticText);
	DDX_Text(pDX, IDC_COMBO_SUBJECT, m_strComboBoxSubjects);
	
	/*
	CEdit *pEdit = // get your control here ...
	pEdit->ModifyStyle(0, ES_NUMBER);
	*/
}

/*virtual*/
BOOL CScoreDlg::OnInitDialog()
{
	Library oLib;
	CSubject oSubject;
	map<int, vector<CString>> m_mapAllSubjects;
	oSubject.PrintSubject(m_mapAllSubjects);

	CComboBox* combo = (CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT);
	combo->SetItemHeight(5, 20);

	for (int i = 0; i < m_mapAllSubjects.size(); i++)
	combo->AddString(m_mapAllSubjects[i+1][0]);

	if (!__super::OnInitDialog())
		return FALSE;

	BOOL bEnable = m_eMode != eDialogMode_View;
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SUBJECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_SCORE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_DATE)->EnableWindow(bEnable);

	m_strClassNum = oLib.IntToCString(m_oScore.m_iClassNum);
	m_strScore= oLib.IntToCString(m_oScore.m_iScore);
	m_strSubject = m_oScore.m_strSubject;
	m_strDate = m_oScore.m_strDate;

	if (m_eMode == eDialogMode_Add)
	{
		SetDlgItemText(IDC_STATIC7, "Add score");
		GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(TRUE);

		m_strClassNum.Empty();
		m_strScore.Empty();
		COleDateTime oleDate = COleDateTime::GetCurrentTime();
		CString currentDate = oleDate.Format(_T("%m/%d/%Y"));
		m_strDate = currentDate;
	}
	else if (m_eMode == eDialogMode_Edit)
		SetDlgItemText(IDC_STATIC7, "Update score");
	else if (m_eMode == eDialogMode_View)
		SetDlgItemText(IDC_STATIC7, "Score");

	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	SetDlgItemText(IDC_COMBO_SUBJECT, m_strSubject);
	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_SCORE, m_strScore);
	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_DATE, m_strDate);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CScoreDlg::ValidateData()
{
	CComboBox* combo = (CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT);
	int nIndex = combo->GetCurSel();

	//empty subject
	if (m_strComboBoxSubjects.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (nIndex == -1)
	{
		MessageBox("Please input correct subject or choose subject!", "Incorect subject");
		return false;
	}
	//empty or incorect score
	else if (m_strScore.IsEmpty())
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
	Library oLib;
	if (m_strDate.IsEmpty())
	{
		MessageBox("Missing date!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (!oLib.IsCorrectDate(m_strDate))
	{
		MessageBox("Please input correct date or preview date!", "Incorect date");
		return FALSE;
	}
	return TRUE;
}

void CScoreDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	if (m_eMode != eDialogMode_View && !ValidateData())
		return;

	m_oScore.m_iClassNum = atoi(m_strClassNum);
	m_oScore.m_strSubject = m_strComboBoxSubjects;//m_strSubject;
	m_oScore.m_iScore = atoi(m_strScore);
	m_oScore.m_strDate = m_strDate;

	CDialogEx::OnOK();
}