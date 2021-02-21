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
	map<int, vector<string>> m_mapSubjects = oSubject.PrintSubject();
	string str;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Teacher", LVCFMT_LEFT, 100);

	for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
	{
		string m_strNumber = to_string((*i).first);
		string m_strSubject = (*i).second[0];
		string m_strTeacher = (*i).second[1] + " " + (*i).second[2];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrSubject(m_strSubject.c_str());
		CString m_cstrTeacher(m_strTeacher.c_str());

		m_listCtrl.InsertItem((*i).first - 1, m_cstrNumber);
		m_listCtrl.SetItemText((*i).first - 1, 1, m_cstrSubject);
		m_listCtrl.SetItemText((*i).first - 1, 2, m_cstrTeacher);
	}
	return true;
}
