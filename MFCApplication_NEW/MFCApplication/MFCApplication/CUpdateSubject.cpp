#include "pch.h"
#include "CUpdateSubject.h"

// CUpdateSubject dialog
IMPLEMENT_DYNAMIC(CSubjectDlg, CDialogEx)

CSubjectDlg::CSubjectDlg(CSubjectData& oSubject, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_SUBJECT, NULL)
	, m_oSubject(oSubject)
	, m_eMode(eMode)
{
}

CSubjectDlg::~CSubjectDlg()
{
}

/*Fill edit boxes*/
void CSubjectDlg::FillEditBoxes()
{
	Library oLib;
	m_strRoomNum = oLib.IntToCString(m_oSubject.m_iId);
	m_strSubject = m_oSubject.m_strSubject;
	m_strFirst_Name = m_oSubject.m_strFirstNameTeacher;
	m_strLast_Name = m_oSubject.m_strLastNameTeacher;

	SetDlgItemText(IDC_EDIT_SUBJECT_ROOM_NUM, m_strRoomNum);
	SetDlgItemText(IDC_EDIT_SUBJECT_SUBJECT, m_strSubject);
	SetDlgItemText(IDC_EDIT_SUBJECT_FIRST_NAME, m_strFirst_Name);
	SetDlgItemText(IDC_EDIT_SUBJECT_LAST_NAME, m_strLast_Name);
}

/*Set enable/disable of edit boxes*/
void CSubjectDlg::EnableDisableBoxes()
{
	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_SUBJECT_ROOM_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SUBJECT_SUBJECT)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SUBJECT_FIRST_NAME)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_SUBJECT_LAST_NAME)->EnableWindow(bEnable);
}

/*virtual*/
BOOL CSubjectDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Add)
		this->SetWindowText("Add Subject");
	else if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Edit Subject");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Subject");

	/*Set enable/disable of edit boxes*/
	EnableDisableBoxes();

	/*Fill edit boxes*/
	FillEditBoxes();

	return TRUE;
}

void CSubjectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SUBJECT_ROOM_NUM, m_strRoomNum);
	DDX_Text(pDX, IDC_EDIT_SUBJECT_SUBJECT, m_strSubject);
	DDV_MaxChars(pDX, m_strSubject, 25);//Size of subject
	DDX_Text(pDX, IDC_EDIT_SUBJECT_FIRST_NAME, m_strFirst_Name);
	DDV_MaxChars(pDX, m_strFirst_Name, 20);//Size of FN teacher
	DDX_Text(pDX, IDC_EDIT_SUBJECT_LAST_NAME, m_strLast_Name);
	DDV_MaxChars(pDX, m_strLast_Name, 15);//Size of FN teacher
}

BEGIN_MESSAGE_MAP(CSubjectDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CSubjectDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CSubjectDlg::ValidateData()
{
	if (m_strSubject.IsEmpty())
	{
		MessageBox("Missing subject!", "Error", MB_ICONHAND);
		return FALSE;
	}

	if (m_strFirst_Name.IsEmpty())
	{
		MessageBox("Missing first name's teacher!", "Error", MB_ICONHAND);
		return FALSE;
	}

	if (m_strLast_Name.IsEmpty())
	{
		MessageBox("Missing last name's teacher!", "Error", MB_ICONHAND);
		return FALSE;
	}

	return TRUE;
}

void CSubjectDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateData())
		return;

	m_oSubject.m_iId = atoi(m_strRoomNum);
	m_oSubject.m_strSubject = m_strSubject;
	m_oSubject.m_strFirstNameTeacher = m_strFirst_Name;
	m_oSubject.m_strLastNameTeacher = m_strLast_Name;

	CDialogEx::OnOK();
}