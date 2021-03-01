// CAddSubject.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CAddSubject.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Subject.h"
#include "Student.h"
#include "CTabSubject.h"


// CAddSubject dialog

IMPLEMENT_DYNAMIC(CAddSubjectDlg, CDialogEx)


CAddSubjectDlg::CAddSubjectDlg(CSubjectData& oSubject, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_ADD_SUBJECT, NULL)
	, m_oSubject(oSubject)
	,m_eModeAddSub(eMode)
{
	
}

CAddSubjectDlg::~CAddSubjectDlg()
{
}

/*virtual*/
BOOL CAddSubjectDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;
	
	BOOL bEnable = m_eModeAddSub == eDialogMode_Add;

	SetDlgItemText(IDC_STATIC7, "Add subject");
	GetDlgItem(IDC_EDIT_ADD_SUBJECT_ROOM_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_ADD_SUBJECT_SUBJECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ADD_SUBJECT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_ADD_SUBJECT_LN)->EnableWindow(bEnable);
	
	m_strRoomNum.Format("%d", m_oSubject.m_iRoomNumber);
	SetDlgItemText(IDC_EDIT_ADD_SUBJECT_ROOM_NUM, m_strRoomNum);
	
	return TRUE;
}

void CAddSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_EDIT_ADD_SUBJECT_ROOM_NUM, m_eRoomNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_ROOM_NUM, m_strRoomNum);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_SUBJECT, m_strSubject);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_FN, m_strFnTeacher);
	DDX_Text(pDX, IDC_EDIT_ADD_SUBJECT_LN, m_strLnTeacher);
}


BEGIN_MESSAGE_MAP(CAddSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAddSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CAddSubject message handlers

BOOL CAddSubjectDlg::ValidateData()
{
	if (m_strSubject.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}

	if (m_strFnTeacher.IsEmpty())
	{
		MessageBox("Missing first name's teacher!", "Error", MB_ICONHAND);

		return FALSE;
	}

	if (m_strLnTeacher.IsEmpty())
	{
		MessageBox("Missing last name's teacher!", "Error", MB_ICONHAND);

		return FALSE;
	}

	return TRUE;
}

void CAddSubjectDlg::OnBnClickedOk()
{
	UpdateData(TRUE);
	
	if (!ValidateData())
		return;

	m_oSubject.m_iRoomNumber = atoi(m_strRoomNum);
	m_oSubject.m_strNameSubject = m_strSubject;
	m_oSubject.m_strFNameTeacher = m_strFnTeacher;
	m_oSubject.m_strLNameTeacher = m_strLnTeacher;
	
	CDialogEx::OnOK();
}