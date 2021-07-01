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
	DDX_Text(pDX, IDC_COMBO_SUBJECT, m_strSubject);
	//date
	DDX_Control(pDX, IDC_DATETIMEPICKER, m_dtCtrlDate);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtCtrlDate.SetFormat(formatStr);
	//combobox
	DDX_Control(pDX, IDC_COMBO_SUBJECT, m_comboBoxSubject);
	DDX_Control(pDX, IDC_COMBO_SCORE, m_comboBoxScore);
}

/*Set range of date time picker*/
void CScoreDlg::SetRangeOfDTPicker()
{
	COleDateTime currentDate = COleDateTime::GetCurrentTime();
	COleDateTime dtMinRange;
	COleDateTime dtMaxRange;

	dtMaxRange.SetDate(currentDate.GetYear(), currentDate.GetMonth(), currentDate.GetDay());
	m_dtCtrlDate.SetRange(&dtMinRange, &dtMaxRange);
}

/*Fill combo boxes*/
void CScoreDlg::FillComboBox()
{
	list<CSubjectData> listSub;

	CSubject oSubject;
	oSubject.PrintSubject(listSub);
	m_comboBoxSubject.SetItemHeight(5, 20);


	CArray<COMBO_DATA> arrData;
	int iId = 0;
	for (auto& i = listSub.begin(); i != listSub.end(); i++)
	{
		COMBO_DATA combo_data;
		combo_data.nID = iId;
		sprintf(combo_data.szName, "%s", i->m_strSubject);
		arrData.Add(combo_data);
		iId++;
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
	}

	subjectCombo.LoadData(arrData, m_comboBoxScore);
}

/*Fill edit boxes*/
void CScoreDlg::FillEditBoxes()
{
	Library oLib;
	m_strClassNum = oLib.IntToCString(m_oScore.m_iIdStudent);
	m_strScore = oLib.IntToCString(m_oScore.m_iScore);
	m_strSubject = m_oScore.m_strSubject;

	if (m_eMode != eDialogMode_Add)
	{
		m_dtCtrlDate.SetTime(m_oScore.m_oleDateTime);
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
}

/*Set enable/disable of edit boxes*/
void CScoreDlg::EnableDisableBoxes()
{
	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_UPDATE_SCORE_CLASS_NUMBER)->EnableWindow(FALSE);
	m_comboBoxSubject.EnableWindow(bEnable);
	m_comboBoxScore.EnableWindow(bEnable);
	m_dtCtrlDate.EnableWindow(bEnable);
}

/*virtual*/
BOOL CScoreDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;
	
	/*Range date*/
	SetRangeOfDTPicker();
	
	/*Fill combo box*/
	FillComboBox();

	if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Update Score");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Score");

	/*Set enable/disable of edit boxes*/
	EnableDisableBoxes();
	
	/*Fill edit boxes*/
	FillEditBoxes();

	return TRUE;
}

BEGIN_MESSAGE_MAP(CScoreDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CScoreDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CScoreDlg::ValidateData()
{
	CMyComboBox myCombo;
	
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

	m_oScore.m_iIdStudent = atoi(m_strClassNum);
	m_oScore.m_strSubject = m_strSubject;
	m_oScore.m_iScore = atoi(m_strScore);
	m_dtCtrlDate.GetTime(m_oScore.m_oleDateTime);

	CDialogEx::OnOK();
}