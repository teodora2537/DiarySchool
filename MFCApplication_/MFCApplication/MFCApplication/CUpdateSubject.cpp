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
	
}

CUpdateSubjectDlg::~CUpdateSubjectDlg()
{
}

void CUpdateSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_cstrRoomNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_SUBJECT, m_cstrSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_FN, m_cstrFN);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_LN, m_cstrLN);
	DDX_Text(pDX, IDC_STATIC7, m_cstrStaticText);
}


BEGIN_MESSAGE_MAP(CUpdateSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateSubjectDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();
	
	UpdateData(TRUE);

	CSubjectData oSubjectData;
	bool flag = oSubjectData.GetFlagIsUpdate();
	if (flag) {
	
	Library lib;
	string row = "";

	int m_iRoomNum = _ttoi(m_cstrRoomNum);
	string m_strFN = lib.ConvertToStirng(m_cstrFN, row);
	string m_strLN = lib.ConvertToStirng(m_cstrLN, row);

	CSubjectData subject(m_iRoomNum, m_cstrSubject, m_strFN, m_strLN);
	CSubject oSubject;
	oSubject.EditSubject(subject);
	}
}