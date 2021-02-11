// CUpdateSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"


// CUpdateSubject dialog

IMPLEMENT_DYNAMIC(CUpdateSubject, CDialogEx)

CUpdateSubject::CUpdateSubject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_SUBJECT, pParent)
{
	
	Library lib;
	Subject m_oSubject;
	CString m_cstrFirstNameTeacher(m_oSubject.GetFirstNameTeacher().c_str());
	CString m_cstrLastNameTeacher(m_oSubject.GetLastNameTeacher().c_str());
	CString m_cstrSubject(m_oSubject.GetNameSubject());

	roomNum.Format(L"%d", m_oSubject.GetRoomNumber());
	subject = m_cstrSubject;
	fn = m_cstrFirstNameTeacher;
	ln = m_cstrLastNameTeacher;
	
}

CUpdateSubject::~CUpdateSubject()
{
}

void CUpdateSubject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, roomNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_SUBJECY, subject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_FN, fn);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_LN, ln);
}


BEGIN_MESSAGE_MAP(CUpdateSubject, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateSubject::OnBnClickedOk)
END_MESSAGE_MAP()

// CUpdateSubject message handlers


void CUpdateSubject::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnOK();
	
	UpdateData(TRUE);
	Library lib;
	string row = "";

	//Success Update
	Subject subject(_ttoi(roomNum), subject, lib.ConvertToStirng(fn, row), lib.ConvertToStirng(ln, row));

	lib.UpdateSubject();
}
