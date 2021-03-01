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
		//Library lib;
		CStudentData m_oStudent;
		CString m_strFirstName(m_oStudent.m_strFirstName);
		CString m_strLastName(m_oStudent.m_strLastName);
		CString m_strBirthday(m_oStudent.m_strBirthday);
		
		m_strClassNum.Format("%d", m_oStudent.m_iClassNumber);
		m_strFn = m_strFirstName;
		m_strLn = m_strLastName;
		m_strBirthday = m_strBirthday;
}

CUpdateStudentDlg::~CUpdateStudentDlg()
{
}

void CUpdateStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_FN, m_strFn);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_LN, m_strLn);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_BIRTHDAY, m_strBirthday);
}


BEGIN_MESSAGE_MAP(CUpdateStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateStudentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	Library lib;
	string row = "";

	CStudentData student(_ttoi(m_strClassNum), m_strFn, m_strLn, m_strBirthday);
	
	CStudent oStudent;
	oStudent.EditStudent(student);
	CDialogEx::OnOK();
}
