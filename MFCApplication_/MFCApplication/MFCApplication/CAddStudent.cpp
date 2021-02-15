// AddStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "AddStudent.h"
#include "afxdialogex.h"
#include "Student.h"


// AddStudent dialog

IMPLEMENT_DYNAMIC(CAddStudentDlg, CDialogEx)

CAddStudentDlg::CAddStudentDlg(CStudentData& oStudent, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_ADD_STUDENT)
	, m_oStudent(oStudent)
{
	m_eMode = eMode;
}

CAddStudentDlg::~CAddStudentDlg()
{
}

/*virtual*/
BOOL CAddStudentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	BOOL bReadOnly = m_eMode == eDialogMode_View;

	m_edb.SetReadOnly(bReadOnly);

	return TRUE;
}

void CAddStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ADD_STUDENT_CLASS_NUM, m_edb);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_FN, fn);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_LN, ln);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_BIRTHDAY, birthday);
}

BEGIN_MESSAGE_MAP(CAddStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CAddStudentDlg::OnBnClickedAddStudent() {
	UpdateData(TRUE);
	Library lib;
	string row = "";


	//	CStudentData student(_ttoi(classNum), lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row), lib.ConvertToStirng(birthday, row));
}


void CAddStudentDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();

	UpdateData(TRUE);
	Library lib;
	string row = "";

	//CStudentData student(_ttoi(classNum), lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row), lib.ConvertToStirng(birthday, row));
	//lib.AddInStudent();
}
