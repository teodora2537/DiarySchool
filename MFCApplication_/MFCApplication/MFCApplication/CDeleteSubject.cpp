// CDeleteSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CDeleteSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"
#include "Student.h"


// CDeleteSubject dialog

IMPLEMENT_DYNAMIC(CDeleteSubject, CDialogEx)

CDeleteSubject::CDeleteSubject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE_SUBJECT, pParent)
{
	Subject m_oSubject;
	roomNum.Format(L"%d", m_oSubject.GetRoomNumber());
}

CDeleteSubject::~CDeleteSubject()
{
}

void CDeleteSubject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELETE_SUBJECT_ROOM_NUM, roomNum);
}


BEGIN_MESSAGE_MAP(CDeleteSubject, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDeleteSubject::OnBnClickedOk)
END_MESSAGE_MAP()


// CDeleteSubject message handlers


void CDeleteSubject::OnBnClickedOk()
{
	CDialogEx::OnOK();
	Subject m_oSubject;
	CString message;
	message.Format(L"Do you want to delete %s with room ¹ %d?", m_oSubject.GetNameSubject(), m_oSubject.GetRoomNumber());

	int result = MessageBox(message, L"Delete subject", MB_YESNO);

	//button yes clicked
	if (result == 6)
	{
	UpdateData(TRUE);
	Library lib;
	string row = "";

	Subject subject;
	subject.SetRoomNumber(_ttoi(roomNum));

	lib.DeleteSubject();
	}
}