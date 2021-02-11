// AddStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "AddStudent.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"


// AddStudent dialog

IMPLEMENT_DYNAMIC(CAddStudent, CDialogEx)

CAddStudent::CAddStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_STUDENT, pParent)
{

}

CAddStudent::~CAddStudent()
{
}

void CAddStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_CLASS_NUM, classNum);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_FN, fn);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_LN, ln);
	DDX_Text(pDX, IDC_EDIT_ADD_STUDENT_BIRTHDAY, birthday);
}

BEGIN_MESSAGE_MAP(CAddStudent, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddStudent::OnBnClickedOk)
END_MESSAGE_MAP()

void CAddStudent::OnBnClickedAddStudent() {
	UpdateData(TRUE);
	Library lib;
	string row = "";

		Student student(_ttoi(classNum), lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row), lib.ConvertToStirng(birthday, row));
	
		/*int MessageBox(LPCTSTR lpszText,
			LPCTSTR lpszCaption = NULL,
			UINT nType = MB_OK);*/
}

// AddStudent message handlers
