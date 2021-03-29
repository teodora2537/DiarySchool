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
	DDX_Text(pDX, IDC_COMBO_SCORE, m_strScore);
	DDX_Text(pDX, IDC_DATETIMEPICKER, m_strDate);
	DDX_Text(pDX, IDC_COMBO_SUBJECT, m_strSubject);
	CDateTimeCtrl* m_dtCtrlDate = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtCtrlDate->SetFormat(formatStr);
}

/*virtual*/
BOOL CScoreDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

		if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Update Score");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Score");

	BOOL bEnable = m_eMode != eDialogMode_View;
		
	GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(FALSE);
	GetDlgItem(IDC_COMBO_SUBJECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_COMBO_SCORE)->EnableWindow(bEnable);
	GetDlgItem(IDC_DATETIMEPICKER)->EnableWindow(bEnable);
	
	Library oLib;
	m_strClassNum = oLib.IntToCString(m_oScore.m_iClassNum);
	m_strScore = oLib.IntToCString(m_oScore.m_iScore);
	m_strSubject = m_oScore.m_strSubject;
	CDateTimeCtrl* m_dtCtrlDate = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER);

	if (m_eMode != eDialogMode_Add)
	{
		COleDateTime date;
		CString strDate = m_oScore.m_strDate;
		date.ParseDateTime(strDate);
		m_dtCtrlDate->SetTime(date);
	}
	else {
	
		this->SetWindowText("Add Score");
		GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(TRUE);	
		
		m_strClassNum.Empty();
		m_strScore.Empty();

	
	
		COleDateTime oleDate = COleDateTime::GetCurrentTime();
		m_dtCtrlDate->SetTime(oleDate);
	}

	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	SetDlgItemText(IDC_COMBO_SUBJECT, m_strSubject);
	SetDlgItemText(IDC_COMBO_SCORE, m_strScore);
	//////////////////Range date//////////
		COleDateTime currentDate = COleDateTime::GetCurrentTime();
		COleDateTime dtMinRange;
		COleDateTime dtMaxRange;

		dtMaxRange.SetDate(currentDate.GetYear(), currentDate.GetMonth(), currentDate.GetDay());
		((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER))->SetRange(&dtMinRange, &dtMaxRange);
		/////////////////////////////////////
	
		///////////Fill combo box////////////
	CSubject oSubject;
	map<int, vector<CString>> m_mapAllSubjects;
	oSubject.PrintSubject(m_mapAllSubjects);

	CComboBox* comboSubject = (CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT);
	comboSubject->SetItemHeight(5, 20);

	for (int i = 0; i < m_mapAllSubjects.size(); i++)
		comboSubject->AddString(m_mapAllSubjects[i + 1][0]);

	CComboBox* comboScore = (CComboBox*)GetDlgItem(IDC_COMBO_SCORE);
	comboScore->SetItemHeight(5, 20);

	for (int i = 2; i <= 6; i++)
		comboScore->AddString(oLib.IntToCString(i));
	/////////////////////////////////
	return TRUE;
}

BEGIN_MESSAGE_MAP(CScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CScoreDlg::ValidateData()
{
	CComboBox* comboSubject = (CComboBox*)GetDlgItem(IDC_COMBO_SUBJECT);
	int nIndexSub = comboSubject->FindStringExact(0, m_strSubject);

	CComboBox* comboScore = (CComboBox*)GetDlgItem(IDC_COMBO_SCORE);
	int nIndexScore = comboScore->FindStringExact(0, m_strScore);
	
	//empty subject
	if (m_strSubject.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (nIndexSub < 0)
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
	else if (nIndexScore < 0)
	{
		MessageBox("Please input correct score!", "Incorect score");
		return false;
	}
	return TRUE;
}

void CScoreDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateData())
		return;

	m_oScore.m_iClassNum = atoi(m_strClassNum);
	m_oScore.m_strSubject = m_strSubject;
	m_oScore.m_iScore = atoi(m_strScore);
	m_oScore.m_strDate = m_strDate;

	CDialogEx::OnOK();
}