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

IMPLEMENT_DYNAMIC(CUpdateStudentDlg, CDialogEx)

CUpdateStudentDlg::CUpdateStudentDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT, pParent)
{
		Library lib;
		CStudentData m_oStudentData;
		CString m_cstrFirstName(m_oStudentData.GetFirstName().c_str());
		CString m_cstrLastName(m_oStudentData.GetLastName().c_str());
		CString m_cstrBirthday(m_oStudentData.GetBirthday().c_str());
		
		m_cstrClassNum.Format(L"%d", m_oStudentData.GetClassNumber());
		m_cstrFn = m_cstrFirstName;
		m_cstrLn = m_cstrLastName;
		m_cstrBirthday = m_cstrBirthday;

}

CUpdateStudentDlg::~CUpdateStudentDlg()
{
}

void CUpdateStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_cstrClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_FN, m_cstrFn);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_LN, m_cstrLn);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_BIRTHDAY, m_cstrBirthday);
}


BEGIN_MESSAGE_MAP(CUpdateStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateStudentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	Library lib;
	string row = "";

	CStudentData student(_ttoi(m_cstrClassNum), lib.ConvertToStirng(m_cstrFn, row), lib.ConvertToStirng(m_cstrLn, row), lib.ConvertToStirng(m_cstrBirthday, row));
	
	CStudent oStudent;
	oStudent.EditStudent(student);
	CDialogEx::OnOK();
}
