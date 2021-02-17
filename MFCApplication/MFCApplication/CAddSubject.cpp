// CAddSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CAddSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"
#include "Student.h"


// CAddSubject dialog

IMPLEMENT_DYNAMIC(CAddSubjectDlg, CDialogEx)

CAddSubjectDlg::CAddSubjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_SUBJECT, pParent)
{

}

CAddSubjectDlg::~CAddSubjectDlg()
{
}

void CAddSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_ROOM_NUM, roomNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_SUBJECT, subject);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_FN, fn);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_LN, ln);
}


BEGIN_MESSAGE_MAP(CAddSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddSubject message handlers


void CAddSubjectDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	
	UpdateData(TRUE);
	Library lib;
	CSubject oSubject;
	string row = "";

	CSubjectData subject(_ttoi(roomNum), subject, lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row));
	//lib.AddInSubject();
	oSubject.AddSubject(subject);
}
