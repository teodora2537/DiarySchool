// CAddSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CAddSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"


// CAddSubject dialog

IMPLEMENT_DYNAMIC(CAddSubject, CDialogEx)

CAddSubject::CAddSubject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_SUBJECT, pParent)
{

}

CAddSubject::~CAddSubject()
{
}

void CAddSubject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_ROOM_NUM, roomNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_SUBJECT, subject);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_FN, fn);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_LN, ln);
}


BEGIN_MESSAGE_MAP(CAddSubject, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddSubject::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddSubject message handlers


void CAddSubject::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	
	UpdateData(TRUE);
	Library lib;
	string row = "";

	Subject subject(_ttoi(roomNum), subject, lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row));
	lib.AddInSubject();
}
