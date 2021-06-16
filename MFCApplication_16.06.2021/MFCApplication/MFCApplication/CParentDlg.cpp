// CParentDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CParentDlg.h"
#include "afxdialogex.h"
#include "Library.h"



// CParentDlg dialog

IMPLEMENT_DYNAMIC(CParentDlg, CDialogEx)

CParentDlg::CParentDlg(list<CStudentData>& listData, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_PARENT, NULL)
	, m_listData(listData)
	,m_eMode(eMode)
{
}

CParentDlg::~CParentDlg()
{
}

void CParentDlg::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);	
	DDX_Text(pDX, IDC_EDIT_PARENT_FN, m_strFn);
	DDX_Text(pDX, IDC_EDIT_PARENT_LN, m_strLn);
	DDX_Text(pDX, IDC_EDIT_PARENT_EMAIL, m_strEmail);
	DDX_Text(pDX, IDC_EDIT_PARENT_PHONE_NUMBER, m_strPhoneNumber);
	DDX_Text(pDX, IDC_EDIT_PARENT_CITY, m_strCity);
	DDX_Text(pDX, IDC_EDIT_PARENT_POST_CODE, m_strPostCode);
	DDX_Text(pDX, IDC_EDIT_PARENT_NEIGHBORHOOD, m_strNeighborhood);
	DDX_Text(pDX, IDC_EDIT_PARENT_ADDRESS, m_strAddress);
}

BOOL CParentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	//BOXES
	if (m_eMode == eDialogMode_Add)
		this->SetWindowText("Add Student");
	else if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Edit Student");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Student");

	/*Fill edit boxes*/
	FillEditBoxes();

	if (m_eMode != eDialogMode_Add)
		//LoadParents(m_oStudent.m_iStudentId);
		;
	return TRUE;
}

/*Fill edit boxes*/
void CParentDlg::FillEditBoxes()
{
	//Library oLib;
	//m_strStudent_ClassNum = oLib.IntToCString(m_oStudent.m_iStudentId);
	//m_strStudent_Fn = m_oStudent.m_strFirstName;
	//m_strStudent_Ln = m_oStudent.m_strLastName;
	//m_strStudent_PhoneNumber = m_oStudent.m_strPhoneNumber;
	//m_strStudent_Email = m_oStudent.m_strEmail;
	//m_strStudent_EGN = m_oStudent.m_strEgn;
	//m_strStudent_City = m_oStudent.m_strCity;
	//m_strStudent_PostCode = m_oStudent.m_strPostCode;
	//m_strStudent_Neighborhood = m_oStudent.m_strNeighborhood;
	//m_strStudent_Address = m_oStudent.m_strAddress;
	//
	//if (m_eMode != eDialogMode_Add)
	//{
	//	m_dtStudent_CtrlBirthday.SetTime(m_oStudent.m_oleDTBirthday);
	//}
	//
	//SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strStudent_ClassNum);
	//SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_FN, m_strStudent_Fn);
	//SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_LN, m_strStudent_Ln);
	//SetDlgItemText(IDC_EDIT_STUDENT_EMAIL, m_strStudent_Email);
	//SetDlgItemText(IDC_EDIT_STUDENT_PHONE_NUMBER, m_strStudent_PhoneNumber);
	//SetDlgItemText(IDC_EDIT_STUDENT_EGN, m_strStudent_EGN);
	//SetDlgItemText(IDC_EDIT_STUDENT_CITY, m_strStudent_City);
	//SetDlgItemText(IDC_EDIT_STUDENT_POST_CODE, m_strStudent_PostCode);
	//SetDlgItemText(IDC_EDIT_STUDENT_NEIGHBORHOOD, m_strStudent_Neighborhood);
	//SetDlgItemText(IDC_EDIT_STUDENT_ADDRESS, m_strStudent_Address);
}

BEGIN_MESSAGE_MAP(CParentDlg, CDialogEx)
END_MESSAGE_MAP()


// CParentDlg message handlers
