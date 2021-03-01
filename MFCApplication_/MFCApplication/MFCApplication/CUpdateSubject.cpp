// CUpdateSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"
#include "CTabSubject.h"
#include "Score.h"


// CUpdateSubject dialog
IMPLEMENT_DYNAMIC(CUpdateSubjectDlg, CDialogEx)
//old
/*
CUpdateSubjectDlg::CUpdateSubjectDlg(CWnd* pParent /*=nullptr/)
	: CDialogEx(IDD_DIALOG_UPDATE_SUBJECT, pParent)
{
	
}


CUpdateSubjectDlg::~CUpdateSubjectDlg()
{
}

/*virtual/
BOOL CUpdateSubjectDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	//BOOL bReadOnly = m_eModeAddSub == eDialogMode_View;
	//m_eRoomNum.SetReadOnly(bReadOnly);
	CSubjectData sub;
	//auto str = sub.GetRoomNumber();
	//m_eRoomNum.SetWindowTextW(L"Heiiii");
	//m_eRoomNum.SetReadOnly(true);
	//m_eRoomNum.SetWindowTextW(_T("hihihihih"));

	return TRUE;
}

void CUpdateSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_cstrRoomNum);
	DDX_Control (pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_eRoomNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_FN, m_strFN);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_LN, m_strLN);
	DDX_Text(pDX, IDC_STATIC7, m_strStaticText);
}


BEGIN_MESSAGE_MAP(CUpdateSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CUpdateSubjectDlg::OnBnClickedOk()
{
	CDialogEx::OnOK();

	UpdateData(TRUE);

	CSubjectData oSubjectData;
	//here set a flag isUpdate
	Library lib;
	string row = "";

	CSubjectData subject(_ttoi(m_strRoomNum), m_strSubject, m_strFN, m_strLN);
	CSubject oSubject;
	oSubject.EditSubject(subject);
}
*/

///////////////////////////////////////////
//new
CUpdateSubjectDlg::CUpdateSubjectDlg(CSubjectData& oSubject, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_UPDATE_SUBJECT, NULL)
	, m_oSubject(oSubject)
	, m_eMode(eMode)
{
}

CUpdateSubjectDlg::~CUpdateSubjectDlg()
{
}

/*virtual*/
BOOL CUpdateSubjectDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if(m_eMode == eDialogMode_Edit)
		SetDlgItemText(IDC_STATIC7, "Update subject");
	if (m_eMode == eDialogMode_View)
		SetDlgItemText(IDC_STATIC7, "Subject");

	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_SUBJECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_LN)->EnableWindow(bEnable);
	
	m_strRoomNum.Format("%d", m_oSubject.m_iRoomNumber);
	m_strSubject =  m_oSubject.m_strNameSubject;
	m_strFN = m_oSubject.m_strFNameTeacher;
	m_strLN = m_oSubject.m_strLNameTeacher;

	SetDlgItemText(IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_strRoomNum);
	SetDlgItemText(IDC_EDIT_UPDATE_SUBJECT_SUBJECT, m_strSubject);
	SetDlgItemText(IDC_EDIT_UPDATE_SUBJECT_FN, m_strFN);
	SetDlgItemText(IDC_EDIT_UPDATE_SUBJECT_LN, m_strLN);
	return TRUE;
}

void CUpdateSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_strRoomNum);
	//DDX_Control(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_eRoomNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_FN, m_strFN);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_LN, m_strLN);
	DDX_Text(pDX, IDC_STATIC7, m_strStaticText);
}

BEGIN_MESSAGE_MAP(CUpdateSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUpdateSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CUpdateSubjectDlg::ValidateData()
{
	if (m_strSubject.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}

	if (m_strFN.IsEmpty())
	{
		MessageBox("Missing first name's teacher!", "Error", MB_ICONHAND);

		return FALSE;
	}

	if (m_strLN.IsEmpty())
	{
		MessageBox("Missing last name's teacher!", "Error", MB_ICONHAND);

		return FALSE;
	}

	return TRUE;
}

void CUpdateSubjectDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	if (!ValidateData())
		return;

	m_oSubject.m_iRoomNumber = atoi(m_strRoomNum);
	m_oSubject.m_strNameSubject = m_strSubject;
	m_oSubject.m_strFNameTeacher = m_strFN;
	m_oSubject.m_strLNameTeacher = m_strLN;

	CDialogEx::OnOK();
}

/////////////////////////////////////////////
// CUpdateSubject dialog
/*

IMPLEMENT_DYNAMIC(CSubjectDlg, CDialogEx)

CSubjectDlg::CSubjectDlg(CSubjectData& oSubject, DialogMode eMode)
	: CDialogEx(IDD_DIALOG_UPDATE_SUBJECT, NULL)
	, m_oSubject(oSubject)
	, m_eMode(eMode)
{
}

CSubjectDlg::~CSubjectDlg()
{
}

/*virtual/
BOOL CSubjectDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_SUBJECT_LN)->EnableWindow(bEnable);
	
	m_strRoomNum.Format("%d", m_oSubject.m_iRoomNumber);
	m_strSubject = m_oSubject.m_strNameSubject;
	m_strFN = m_oSubject.m_strFNameTeacher;
	m_strLN = m_oSubject.m_strLNameTeacher;

	return TRUE;
}

#include "Score.h"

void CSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_cstrRoomNum);
	//DDV_(pDX, IDC_EDIT_UPDATE_SUBJECT_ROOM_NUM, m_cstrRoomNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_FN, m_strFN);
	DDX_Text(pDX, IDC_EDIT_UPDATE_SUBJECT_LN, m_strLN);
	DDX_Text(pDX, IDC_STATIC7, m_strStaticText);

	//Pogledni go
	//DDV_MaxChars(pDX, m_strSubject, 
}


BEGIN_MESSAGE_MAP(CSubjectDlg, CDialogEx)
END_MESSAGE_MAP()

BOOL CSubjectDlg::ValidateData()
{
	if (m_strSubject.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}

	if (m_strFN.IsEmpty())
	{
		MessageBox("Missing first name's teacher!", "Error", MB_ICONHAND);

		return FALSE;
	}

	if (m_strLN.IsEmpty())
	{
		MessageBox("Missing last name's teacher!", "Error", MB_ICONHAND);

		return FALSE;
	}

	return TRUE;
}

void CSubjectDlg::OnOK()
{
	UpdateData(TRUE);

	if (!ValidateData())
		return;

	m_oSubject.m_iRoomNumber = atoi(m_strRoomNum);
	m_oSubject.m_strNameSubject = m_strSubject;
	m_oSubject.m_strFNameTeacher = m_strFN;
	m_oSubject.m_strLNameTeacher = m_strLN;

	CDialogEx::OnOK();
}
*/