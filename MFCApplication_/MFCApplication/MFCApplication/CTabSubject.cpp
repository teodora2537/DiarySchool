// CTabSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabSubject.h"
#include "afxdialogex.h"
#include "Subject.h"


// CTabSubject dialog

IMPLEMENT_DYNAMIC(CTabSubject, CDialogEx)

CTabSubject::CTabSubject(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_SUBJECT, pParent)
{

}

CTabSubject::~CTabSubject()
{
}

void CTabSubject::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
}


BEGIN_MESSAGE_MAP(CTabSubject, CDialogEx)
END_MESSAGE_MAP()


BOOL CTabSubject::OnInitDialog() {

	CDialogEx::OnInitDialog();

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	CSubject oSubject;
	map<int, vector<string>> mapSubject = oSubject.PrintSubject();
	string str;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Teacher", LVCFMT_LEFT, 100);

	for (auto i = mapSubject.begin(); i != mapSubject.end(); i++)
	{
		string number = to_string((*i).first);
		string subject = (*i).second[0];
		string teacher = (*i).second[1] + " " + (*i).second[2];

		CString cstrNumber(number.c_str());
		CString cstrSubject(subject.c_str());
		CString cstrTeacher(teacher.c_str());

		m_listCtrl.InsertItem((*i).first - 1, cstrNumber);
		m_listCtrl.SetItemText((*i).first - 1, 1, cstrSubject);
		m_listCtrl.SetItemText((*i).first - 1, 2, cstrTeacher);
	}
	return true;
}
