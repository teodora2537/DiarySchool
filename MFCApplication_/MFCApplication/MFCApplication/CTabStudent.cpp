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
	int nItem = 0;

	//Library lib_;
	CStudent oStudent;

	map<int, vector<string>> mapStudent = oStudent.PrintStudent();
	string str;

	int count = 0;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Date of birthday", LVCFMT_LEFT, 100);

	for (auto i = mapStudent.begin(); i != mapStudent.end(); i++)
	{
		string number = to_string((*i).first);
		string name = (*i).second[0] + " " + (*i).second[1];
		string dayOfBirth = (*i).second[2];

		CString cstrNumber(number.c_str());
		CString cstrName(name.c_str());
		CString cstrDayOfBirth(dayOfBirth.c_str());

		m_listCtrl.InsertItem(count, cstrNumber);
		m_listCtrl.SetItemText(count, 1, cstrName);
		m_listCtrl.SetItemText(count, 2, cstrDayOfBirth);

		count++;
	}
	
	return true;
}