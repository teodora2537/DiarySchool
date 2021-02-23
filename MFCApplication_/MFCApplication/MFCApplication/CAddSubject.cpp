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
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_ROOM_NUM, m_cstrRoomNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_SUBJECT, m_cstrSubject);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_FN, m_cstrFnTeacher);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_LN, m_cstrLnTeacher);
}


BEGIN_MESSAGE_MAP(CAddSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddSubject message handlers

void CAddSubjectDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
	
	UpdateData(TRUE);
	Library oLib;
	CSubject oSubject;
	string m_strRow = "";

	int m_iRoomNum = _ttoi(m_cstrRoomNum);
	string m_strFN = oLib.ConvertToStirng(m_cstrFnTeacher, m_strRow);
	string m_strLN = oLib.ConvertToStirng(m_cstrLnTeacher, m_strRow);

	CSubjectData oSubjectData(m_iRoomNum, m_cstrSubject, m_strFN, m_strLN);
	oSubject.AddSubject(oSubjectData);
}