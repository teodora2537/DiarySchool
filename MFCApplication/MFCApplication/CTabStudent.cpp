// CTabStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabStudent.h"
#include "afxdialogex.h"
#include "Library.h"


// CTabStudent dialog

IMPLEMENT_DYNAMIC(CTabStudent, CDialogEx)

CTabStudent::CTabStudent(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_STUDENT, pParent)
{
	
}

CTabStudent::~CTabStudent()
{
}

void CTabStudent::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
}

BEGIN_MESSAGE_MAP(CTabStudent, CDialogEx)
END_MESSAGE_MAP()
