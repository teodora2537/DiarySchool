// CTabStudent.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabStudent.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"


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

BOOL CTabStudent::OnInitDialog() {
	
	CDialogEx::OnInitDialog();


	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);
	
	CStudent oStudent;

	map<int, vector<CString>> m_mapAllStudent;
	oStudent.PrintStudent(m_mapAllStudent);

	int m_iCount = 0;

	m_listCtrl.InsertColumn(0, "¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Date of birthday", LVCFMT_LEFT, 100);

	for (auto i = m_mapAllStudent.begin(); i != m_mapAllStudent.end(); i++)
	{
		string m_strNumber = to_string((*i).first);
		string m_strName = (*i).second[0] + " " + (*i).second[1];
		string m_strDayOfBirth = (*i).second[2];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrName(m_strName.c_str());
		CString m_cstrDayOfBirth(m_strDayOfBirth.c_str());

		m_listCtrl.InsertItem(m_iCount, m_cstrNumber);
		m_listCtrl.SetItemText(m_iCount, 1, m_cstrName);
		m_listCtrl.SetItemText(m_iCount, 2, m_cstrDayOfBirth);

		m_iCount++;
	}
	
	return true;
}