#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateStudent.h"

// CUpdateStudent dialog

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CStudentData& oStudent, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT, NULL)
	, m_oStudent(oStudent)
	, m_eMode(eMode)
{
}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_FN, m_strFn);
	DDV_MaxChars(pDX, m_strFn, 20);//Size of FN student
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_LN, m_strLn);
	DDX_Text(pDX, IDC_DATETIMEPICKER1, m_strBirthday);
	DDV_MaxChars(pDX, m_strLn, 15);//Size of LN student
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtCtrlBirthday);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtCtrlBirthday.SetFormat(formatStr);
}

BOOL CStudentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Add)
		this->SetWindowText("Add Student");
	else if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Edit Student");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Student");

	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_LN)->EnableWindow(bEnable);
	m_dtCtrlBirthday.EnableWindow(bEnable);
	
	Library oLib;
	m_strClassNum = oLib.IntToCString(m_oStudent.m_iClassNumber);
	m_strFn = m_oStudent.m_strFirstName;
	m_strLn = m_oStudent.m_strLastName;

	if (m_eMode != eDialogMode_Add)
	{
		/*
	COleDateTime date;
	CString strDate = m_oStudent.m_strBirthday;
	date.ParseDateTime(strDate);
		*/
	m_dtCtrlBirthday.SetTime(m_oStudent.m_strBirthday);
	}

	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strClassNum);
	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_FN, m_strFn);
	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_LN, m_strLn);

	//////////////////Range date///////////
	COleDateTime currentDate = COleDateTime::GetCurrentTime();
	COleDateTime dtMinRange;
	COleDateTime dtMaxRange;

	dtMinRange.SetDate(currentDate.GetYear()-100, currentDate.GetMonth(), currentDate.GetDay());
	dtMaxRange.SetDate(currentDate.GetYear(), currentDate.GetMonth(), currentDate.GetDay());
	m_dtCtrlBirthday.SetRange(&dtMinRange, &dtMaxRange);
	/////////////////

	return TRUE;
}

BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CStudentDlg::ValidateData()
{
	if (m_strFn.IsEmpty())
	{
		MessageBox("Missing first name!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strLn.IsEmpty())
	{
		MessageBox("Missing last name!", "Error", MB_ICONHAND);

		return FALSE;
	}
	return TRUE;
}

void CStudentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateData())
		return;

	m_oStudent.m_iClassNumber = atoi(m_strClassNum);
	m_oStudent.m_strFirstName = m_strFn;
	m_oStudent.m_strLastName = m_strLn;
	m_dtCtrlBirthday.GetTime(m_oStudent.m_strBirthday);

	CDialogEx::OnOK();
}
/*
void CStudentDlg::DoFieldExchange(CFieldExchange* pFx)
{
	Library oLib;
	pFx->SetFieldType(CFieldExchange::outputColumn);
	int m_classNum;
	RFX_Int(pFx, "[id]", m_classNum);
	m_strClassNum = oLib.IntToCString(m_classNum);
	RFX_Text(pFx, "[first_name]", m_strFn);
	RFX_Text(pFx, "[last_name]", m_strLn);

	m_dtCtrlBirthday.GetTime(time);
	RFX_Date(pFx, "[birth_date]", time);

	pFx->SetFieldType(CFieldExchange::inputParam);
}
*/

/*
void CStudentDlg::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	Library oLib;
	int m_classNum = atoi(m_strClassNum);
	RFX_Int(pFX, "[id]", m_classNum);
	RFX_Text(pFx, "[first_name]", m_strFn);
	RFX_Text(pFx, "[last_name]", m_strLn);
	RFX_Date(pFx, "[birth_date]", oLib.CStringToDate(m_strBirthday));

	pFX->SetFieldType(CFieldExchange::inputParam);
}
*/