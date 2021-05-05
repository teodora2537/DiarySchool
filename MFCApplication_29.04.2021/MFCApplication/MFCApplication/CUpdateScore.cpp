#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateScore.h"
#include "Score.h"
using namespace std;

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
	DDX_Text(pDX, IDC_COMBO_SCORE, m_strScore);
	DDX_Text(pDX, IDC_DATETIMEPICKER, m_strDate);
	DDX_Text(pDX, IDC_COMBO_SUBJECT, m_strSubject);
	
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dtCtrlDate);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtCtrlDate.SetFormat(formatStr);

	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_comboBoxSubject);
	DDX_Control(pDX, IDC_COMBO_SCORE, m_comboBoxScore);
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
	m_comboBoxSubject.EnableWindow(bEnable);
	m_comboBoxScore.EnableWindow(bEnable);
	m_dtCtrlDate.EnableWindow(bEnable);
	
	Library oLib;
	m_strClassNum = oLib.IntToCString(m_oScore.m_iClassNum);
	m_strScore = oLib.IntToCString(m_oScore.m_iScore);
	m_strSubject = m_oScore.m_strSubject;

	if (m_eMode != eDialogMode_Add)
	{
		COleDateTime date;
		CString strDate = m_oScore.m_strDate;
		date.ParseDateTime(strDate);
		m_dtCtrlDate.SetTime(date);
	}
	else {
	
		this->SetWindowText("Add Score");
		GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(TRUE);	
		
		m_strClassNum.Empty();
		m_strScore.Empty();

		COleDateTime oleDate = COleDateTime::GetCurrentTime();
		m_dtCtrlDate.SetTime(oleDate);
	}

	SetDlgItemText(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER, m_strClassNum);
	SetDlgItemText(IDC_COMBO_SUBJECT, m_strSubject);
	SetDlgItemText(IDC_COMBO_SCORE, m_strScore);

	//////////////////Range date//////////
	COleDateTime currentDate = COleDateTime::GetCurrentTime();
	COleDateTime dtMinRange;
	COleDateTime dtMaxRange;

	dtMaxRange.SetDate(currentDate.GetYear(), currentDate.GetMonth(), currentDate.GetDay());
	m_dtCtrlDate.SetRange(&dtMinRange, &dtMaxRange);
	/////////////////////////////////////
	
	///////////Fill combo box////////////
	list<SUBJECT> m_listSub;

	CSubject oSubject;
	oSubject.PrintSub(m_listSub);
	m_comboBoxSubject.SetItemHeight(5, 20);


	CArray<COMBO_DATA> arrData;
	int iId = 0;
	for (auto& i = m_listSub.begin(); i != m_listSub.end(); i++)
	{	
		COMBO_DATA combo_data;
		combo_data.nID = iId;
		sprintf(combo_data.szName, "%s", i->szSubject);
		arrData.Add(combo_data);
		iId++;

		//m_comboBoxSubject.AddString(i->szSubject);
	}
		CMyComboBox subjectCombo;
	subjectCombo.LoadData(arrData, m_comboBoxSubject);
		
	m_comboBoxScore.SetItemHeight(5, 20);

	iId = 0;
	arrData.RemoveAll();

	for (int i = 2; i <= 6; i++) {
	
		COMBO_DATA combo_data;
		combo_data.nID = iId;
		sprintf(combo_data.szName, "%d", i);
		arrData.Add(combo_data);

		//m_comboBoxScore.AddString(oLib.IntToCString(i));
}

	subjectCombo.LoadData(arrData, m_comboBoxScore);

	/////////////////////////////////
	return TRUE;
}


BEGIN_MESSAGE_MAP(CScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CScoreDlg::ValidateData()
{
	CMyComboBox myCombo;
	//int nIndexSub = m_comboBoxSubject.FindStringExact(0, m_strSubject);
	//int nIndexScore = m_comboBoxScore.FindStringExact(0, m_strScore);
	
	int nIndexSub = myCombo.GetSelectedValue(m_comboBoxSubject);
	int nIndexScore = myCombo.GetSelectedValue(m_comboBoxScore);
	
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