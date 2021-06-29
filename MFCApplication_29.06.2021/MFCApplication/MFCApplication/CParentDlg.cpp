// CParentDlg.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CParentDlg.h"
#include "afxdialogex.h"
#include "Library.h"
#include "CUpdateStudent.h"

// CParentDlg dialog

IMPLEMENT_DYNAMIC(CParentDlg, CDialogEx)

CParentDlg::CParentDlg(CParentData& oParent, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_PARENT, NULL)
	, m_oParent(oParent)
	,m_eMode(eMode)
{
}

CParentDlg::~CParentDlg()
{
}

void CParentDlg::DoDataExchange(CDataExchange* pDX)
{

	CDialogEx::DoDataExchange(pDX);	
	DDX_Text(pDX, IDC_EDIT_PARENT_FN,			m_strFn);
	DDX_Text(pDX, IDC_EDIT_PARENT_LN,			m_strLn);
	DDX_Text(pDX, IDC_EDIT_PARENT_EMAIL,		m_strEmail);
	DDX_Text(pDX, IDC_EDIT_PARENT_PHONE_NUMBER, m_strPhoneNumber);
	DDX_Text(pDX, IDC_EDIT_PARENT_CITY,			m_strCity);
	DDX_Text(pDX, IDC_EDIT_PARENT_POST_CODE,	m_strPostCode);
	DDX_Text(pDX, IDC_EDIT_PARENT_NEIGHBORHOOD, m_strNeighborhood);
	DDX_Text(pDX, IDC_EDIT_PARENT_ADDRESS,		m_strAddress);
}

BOOL CParentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	//BOXES
	if (m_eMode == eDialogMode_Add)
		this->SetWindowText("Add Parent");
	else if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Edit Parent");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Parent");


	/*Set enable/disable of edit boxes*/
	EnableDisableBoxes();

	/*Fill edit boxes*/
	FillEditBoxes();
		
	return TRUE;
}

/*Set enable/disable of edit boxes*/
void CParentDlg::EnableDisableBoxes()
{
	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_PARENT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_LN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_EMAIL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_PHONE_NUMBER)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_CITY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_POST_CODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_NEIGHBORHOOD)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_ADDRESS)->EnableWindow(bEnable);
}

/*Fill edit boxes*/
void CParentDlg::FillEditBoxes()
{
	m_strFn				= m_oParent.m_strFirstName;
	m_strLn				= m_oParent.m_strLastName;
	m_strPhoneNumber	= m_oParent.m_strPhoneNumber;
	m_strEmail			= m_oParent.m_strEmail;
	m_strCity			= m_oParent.m_strCity;
	m_strPostCode		= m_oParent.m_strPostCode;
	m_strNeighborhood	= m_oParent.m_strNeighborhood;
	m_strAddress		= m_oParent.m_strAddress;
	
	SetDlgItemText(IDC_EDIT_PARENT_FN, m_strFn);
	SetDlgItemText(IDC_EDIT_PARENT_LN, m_strLn);
	SetDlgItemText(IDC_EDIT_PARENT_EMAIL, m_strEmail);
	SetDlgItemText(IDC_EDIT_PARENT_PHONE_NUMBER, m_strPhoneNumber);
	SetDlgItemText(IDC_EDIT_PARENT_CITY, m_strCity);
	SetDlgItemText(IDC_EDIT_PARENT_POST_CODE, m_strPostCode);
	SetDlgItemText(IDC_EDIT_PARENT_NEIGHBORHOOD, m_strNeighborhood);
	SetDlgItemText(IDC_EDIT_PARENT_ADDRESS, m_strAddress);
}

BOOL CParentDlg::ValidateData()
{
	if (m_strFn.IsEmpty())
	{
		MessageBox("Missing first name of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strLn.IsEmpty())
	{
		MessageBox("Missing last name of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strPhoneNumber.IsEmpty() || m_strPhoneNumber.GetLength() < 8)
	{
		MessageBox("Error phone number of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strCity.IsEmpty())
	{
		MessageBox("Missing city of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strPostCode.IsEmpty())
	{
		MessageBox("Missing post code of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strNeighborhood.IsEmpty())
	{
		MessageBox("Missing neighborhood of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	else if (m_strAddress.IsEmpty())
	{
		MessageBox("Missing address of parent!", "Error", MB_ICONHAND);
		return FALSE;
	}
	
	return TRUE;
}

BEGIN_MESSAGE_MAP(CParentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CParentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// CParentDlg message handlers
void CParentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateData())	{
		return;
	}

	m_oParent.m_strFirstName = m_strFn;
	m_oParent.m_strLastName = m_strLn;
	m_oParent.m_strEmail = m_strEmail;
	m_oParent.m_strPhoneNumber = m_strPhoneNumber;
	m_oParent.m_strCity = m_strCity;
	m_oParent.m_strPostCode = m_strPostCode;
	m_oParent.m_strNeighborhood = m_strNeighborhood;
	m_oParent.m_strAddress = m_strAddress;

	CDialogEx::OnOK();
}