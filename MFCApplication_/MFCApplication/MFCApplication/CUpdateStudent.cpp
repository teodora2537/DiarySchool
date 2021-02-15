// CUpdateStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateStudent.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"


// CUpdateStudent dialog

IMPLEMENT_DYNAMIC(CUpdateStudentDlg, CDialogEx)

CUpdateStudentDlg::CUpdateStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT, pParent)
{
		Library lib;
		CStudentData m_oStudent;
		CString m_cstrFirstName(m_oStudent.GetFirstName().c_str());
		CString m_cstrLastName(m_oStudent.GetLastName().c_str());
		CString m_cstrBirthday(m_oStudent.GetBirthday().c_str());
		
		classNum.Format(L"%d", m_oStudent.GetClassNumber());
		fn = m_cstrFirstName;
		ln = m_cstrLastName;
		birthday = m_cstrBirthday;

}

CUpdateStudentDlg::~CUpdateStudentDlg()
{
}

void CUpdateStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, classNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_FN, fn);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_LN, ln);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_BIRTHDAY, birthday);
}


BEGIN_MESSAGE_MAP(CUpdateStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateStudentDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();

	UpdateData(TRUE);
	Library lib;
	string row = "";

	CStudentData student(_ttoi(classNum), lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row), lib.ConvertToStirng(birthday, row));
	
	lib.UpdateStudent();
}
