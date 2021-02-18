// CUpdateSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"


// CUpdateSubject dialog

IMPLEMENT_DYNAMIC(CUpdateSubjectDlg, CDialogEx)

CUpdateSubjectDlg::CUpdateSubjectDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_UPDATE_SUBJECT, pParent)
{
	
	Library lib;
	CSubjectData m_oSubject;
	CString m_cstrFirstNameTeacher(m_oSubject.GetFirstNameTeacher().c_str());
	CString m_cstrLastNameTeacher(m_oSubject.GetLastNameTeacher().c_str());
	CString m_cstrSubject(m_oSubject.GetNameSubject());

	m_cstrRoomNum.Format(L"%d", m_oSubject.GetRoomNumber());
	m_cstrSubject = m_cstrSubject;
	m_cstrFN = m_cstrFirstNameTeacher;
	m_cstrLN = m_cstrLastNameTeacher;
}

CUpdateSubjectDlg::~CUpdateSubjectDlg()
{
}

void CUpdateSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_cstrRoomNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_SUBJECY, m_cstrSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_FN, m_cstrFN);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_LN, m_cstrLN);
}


BEGIN_MESSAGE_MAP(CUpdateSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateSubjectDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
	
	UpdateData(TRUE);
	Library lib;
	string row = "";

	CSubjectData subject(_ttoi(m_cstrRoomNum), m_cstrSubject, lib.ConvertToStirng(m_cstrFN, row), lib.ConvertToStirng(m_cstrLN, row));

	//lib.UpdateSubject();
	CSubject oSubject;
	oSubject.EditSubject(subject);
}
