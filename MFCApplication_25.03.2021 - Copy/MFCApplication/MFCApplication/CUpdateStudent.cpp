// CUpdateStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateStudent.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"
#include "CTabReference.h"

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
	DDV_MaxChars(pDX, m_strLn, 15);//Size of LN student
	DDX_Text(pDX, IDC_DATETIMEPICKER1, m_strBirthday);
	CDateTimeCtrl* m_dtCtrlDate = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtCtrlDate->SetFormat(formatStr);
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
	GetDlgItem(IDC_DATETIMEPICKER1)->EnableWindow(bEnable);
	
	Library oLib;
	m_strClassNum = oLib.IntToCString(m_oStudent.m_iClassNumber);
	m_strFn = m_oStudent.m_strFirstName;
	m_strLn = m_oStudent.m_strLastName;
	CDateTimeCtrl* m_dtCtrlDate = (CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1);

	if (m_eMode != eDialogMode_Add)
	{
	COleDateTime date;
	CString strDate = m_oStudent.m_strBirthday;
	date.ParseDateTime(strDate);
	m_dtCtrlDate->SetTime(date);
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
	((CDateTimeCtrl*)GetDlgItem(IDC_DATETIMEPICKER1))->SetRange(&dtMinRange, &dtMaxRange);
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

	/*
	//empty or incorect date
	COleDateTime date;
	Library oLib;
	if (m_strBirthday.IsEmpty())
	{
		MessageBox("Missing birthday!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (!oLib.IsCorrectDate(m_strBirthday))
	{
		MessageBox("Please input correct date or preview date!", "Incorect date");
		return false;
	}
	*/

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
/*
	COleDateTime m_dt;
	m_dtCtrlBirthday.GetTime(m_dt);
	CString strDateTime = m_dt.Format(VAR_DATEVALUEONLY);
*/
	m_oStudent.m_strBirthday = m_strBirthday;

	CDialogEx::OnOK();
}
