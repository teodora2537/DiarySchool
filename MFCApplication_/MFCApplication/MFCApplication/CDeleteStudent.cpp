// CDeleteStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CDeleteStudent.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"


// CDeleteStudent dialog

IMPLEMENT_DYNAMIC(CDeleteStudent, CDialogEx)

CDeleteStudent::CDeleteStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE_STUDENT, pParent)
{
	//Library lib;
	// CString m_cstrFirstName(m_oStudent.GetFirstName().c_str());
	// CString m_cstrLastName(m_oStudent.GetLastName().c_str());
	// CString m_cstrBirthday(m_oStudent.GetBirthday().c_str());

	Student m_oStudent;
	classNum.Format(L"%d", m_oStudent.GetClassNumber());
}

CDeleteStudent::~CDeleteStudent()
{
}

void CDeleteStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELETE_STUDENT_CLASS_NUM, classNum);
}


BEGIN_MESSAGE_MAP(CDeleteStudent, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDeleteStudent::OnBnClickedOk)
END_MESSAGE_MAP()

// CDeleteStudent message handlers

void CDeleteStudent::OnBnClickedOk()
{
	Library lib;
	Student m_oStudent;
	CString message;
	message.Format(L"Do you want to delete %s with � in class %d?", m_oStudent.GetFullName(), m_oStudent.GetClassNumber());

	int result = MessageBox(message, L"Delete student", MB_YESNO);
	CDialogEx::OnOK();
	
	//button yes clicked
	if (result == 6)
	{
		UpdateData(TRUE);
		Library lib;
		string row = "";
		
		Student student;
		student.SetClassNumber(_ttoi(classNum));

	lib.DeleteStudent();
	}
}
