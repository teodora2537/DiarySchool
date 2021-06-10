#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateStudent.h"
#include "CStudentTable.h"
// CUpdateStudent dialog

IMPLEMENT_DYNAMIC(CStudentDlg, CDialogEx)

CStudentDlg::CStudentDlg(CStudentData& oStudent, const DialogMode eMode)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT, NULL)
	, m_oStudent(oStudent)
	, m_eMode(eMode)
{
}

CStudentDlg::~CStudentDlg()
{
}

void CStudentDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strStudent_ClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_FN, m_strStudent_Fn);
	DDV_MaxChars(pDX, m_strStudent_Fn, 20);//Size of FN student
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_LN, m_strStudent_Ln);
	DDV_MaxChars(pDX, m_strStudent_Ln, 15);//Size of LN student
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtStudent_CtrlBirthday);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtStudent_CtrlBirthday.SetFormat(formatStr);
	//student
	DDX_Text(pDX, IDC_EDIT_STUDENT_EMAIL, m_strStudent_Email);
	DDX_Text(pDX, IDC_EDIT_STUDENT_PHONE_NUMBER, m_strStudent_PhoneNumber);
	DDX_Text(pDX, IDC_EDIT_STUDENT_EGN, m_strStudent_EGN);
	DDX_Text(pDX, IDC_EDIT_STUDENT_CITY, m_strStudent_City);
	DDX_Text(pDX, IDC_EDIT_STUDENT_POST_CODE, m_strStudent_PostCode);
	DDX_Text(pDX, IDC_EDIT_STUDENT_NEIGHBORHOOD, m_strStudent_Neighborhood);
	DDX_Text(pDX, IDC_EDIT_STUDENT_ADDRESS, m_strStudent_Address);
	//parent
	DDX_Text(pDX, IDC_EDIT_PARENT_FN, m_strParent_Fn);
	DDX_Text(pDX, IDC_EDIT_PARENT_LN, m_strParent_Ln);
	DDX_Text(pDX, IDC_EDIT_PARENT_EMAIL, m_strParent_Email);
	DDX_Text(pDX, IDC_EDIT_PARENT_PHONE_NUMBER, m_strParent_PhoneNumber);
	DDX_Text(pDX, IDC_EDIT_PARENT_CITY, m_strParent_City);
	DDX_Text(pDX, IDC_EDIT_PARENT_POST_CODE, m_strParent_PostCode);
	DDX_Text(pDX, IDC_EDIT_PARENT_NEIGHBORHOOD, m_strParent_Neighborhood);
	DDX_Text(pDX, IDC_EDIT_PARENT_ADDRESS, m_strParent_Address);
}

/*Set range date*/
void CStudentDlg::SetRangeOfDTPicker()
{
	COleDateTime currentDate = COleDateTime::GetCurrentTime();
	COleDateTime dtMinRange;
	COleDateTime dtMaxRange;

	dtMinRange.SetDate(currentDate.GetYear() - 100, currentDate.GetMonth(), currentDate.GetDay());
	dtMaxRange.SetDate(currentDate.GetYear(), currentDate.GetMonth(), currentDate.GetDay());
	m_dtStudent_CtrlBirthday.SetRange(&dtMinRange, &dtMaxRange);
}

/*Fill edit boxes*/ 
void CStudentDlg::FillEditBoxes()
{
	Library oLib;
	m_strStudent_ClassNum = oLib.IntToCString(m_oStudent.m_iId);
	m_strStudent_Fn = m_oStudent.m_strStudent_FirstName;
	m_strStudent_Ln = m_oStudent.m_strStudent_LastName;
	m_strStudent_PhoneNumber = m_oStudent.m_strStudent_PhoneNumber;
	m_strStudent_Email = m_oStudent.m_strStudent_Email;
	m_strStudent_City = m_oStudent.m_strStudent_City;
	m_strStudent_PostCode = m_oStudent.m_strStudent_PostCode;
	m_strStudent_Neighborhood = m_oStudent.m_strStudent_Neighborhood;
	m_strStudent_Address = m_oStudent.m_strStudent_Address;

	if (m_eMode != eDialogMode_Add)
	{
		m_dtStudent_CtrlBirthday.SetTime(m_oStudent.m_oleDT_Birthday);
	}

	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strStudent_ClassNum);
	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_FN, m_strStudent_Fn);
	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_LN, m_strStudent_Ln);
	SetDlgItemText(IDC_EDIT_PARENT_PHONE_NUMBER, m_strStudent_PhoneNumber);
	SetDlgItemText(IDC_EDIT_PARENT_EMAIL, m_strStudent_Email);
	SetDlgItemText(IDC_EDIT_PARENT_CITY, m_strStudent_City);
	SetDlgItemText(IDC_EDIT_PARENT_POST_CODE, m_strStudent_PostCode);
	SetDlgItemText(IDC_EDIT_PARENT_NEIGHBORHOOD, m_strStudent_Neighborhood);
	SetDlgItemText(IDC_EDIT_PARENT_ADDRESS, m_strStudent_Address);
}

/*Set enable/disable of edit boxes*/
void CStudentDlg::EnableDisableBoxes()
{
	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_LN)->EnableWindow(bEnable);
	m_dtStudent_CtrlBirthday.EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_PHONE_NUMBER)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_EMAIL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_CITY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_POST_CODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_NEIGHBORHOOD)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_PARENT_ADDRESS)->EnableWindow(bEnable);
}

BOOL CStudentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	if (m_eMode == eDialogMode_Add)
		this->SetWindowText("Add Student");
	else if (m_eMode == eDialogMode_Edit)
		this->SetWindowText("Edit Student");
	else if (m_eMode == eDialogMode_View)
		this->SetWindowText("Student");

	/*Set enable/disable of edit boxes*/
	EnableDisableBoxes();
	
	/*Fill edit boxes*/
	FillEditBoxes();

	/*Set range date*/
	SetRangeOfDTPicker();

	

	return TRUE;
}

BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CStudentDlg::ValidateData()
{
	//Student
	{
		if (m_strStudent_Fn.IsEmpty())
		{
			MessageBox("Missing first name!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Ln.IsEmpty())
		{
			MessageBox("Missing last name!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Email.IsEmpty())
		{
			MessageBox("Missing email!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_PhoneNumber.IsEmpty() || m_strStudent_PhoneNumber.GetLength() < 8)
		{
			MessageBox("Error phone number!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_EGN.IsEmpty())
		{
			MessageBox("Missing egn!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_City.IsEmpty())
		{
			MessageBox("Missing city!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_PostCode.IsEmpty())
		{
			MessageBox("Missing post code!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Neighborhood.IsEmpty())
		{
			MessageBox("Missing neighborhood!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Address.IsEmpty())
		{
			MessageBox("Missing address!", "Error", MB_ICONHAND);
			return FALSE;
		}
	}

	//Parent
	{
		if (m_strParent_Fn.IsEmpty())
		{
			MessageBox("Missing first name!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strParent_Ln.IsEmpty())
		{
			MessageBox("Missing last name!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strParent_PhoneNumber.IsEmpty() || m_strStudent_PhoneNumber.GetLength() < 8)
		{
			MessageBox("Error phone number!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strParent_City.IsEmpty())
		{
			MessageBox("Missing city!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strParent_PostCode.IsEmpty())
		{
			MessageBox("Missing post code!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strParent_Neighborhood.IsEmpty())
		{
			MessageBox("Missing neighborhood!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strParent_Address.IsEmpty())
		{
			MessageBox("Missing address!", "Error", MB_ICONHAND);
			return FALSE;
		}
	}

	return TRUE;
}

void CStudentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateData())
		return;
	
	list<CStudentData> objList;

	m_oStudent.m_iId = atoi(m_strStudent_ClassNum);
	m_oStudent.m_strStudent_FirstName = m_strStudent_Fn;
	m_oStudent.m_strStudent_LastName = m_strStudent_Ln;
	m_dtStudent_CtrlBirthday.GetTime(m_oStudent.m_oleDT_Birthday);
	m_oStudent.m_strStudent_Email = m_strStudent_Email;
	m_oStudent.m_strStudent_PhoneNumber = m_strParent_PhoneNumber;
	m_oStudent.m_strStudent_Egn = m_strStudent_EGN;
	m_oStudent.m_strStudent_City = m_strStudent_City;
	m_oStudent.m_strStudent_PostCode = m_strStudent_PostCode;
	m_oStudent.m_strStudent_Neighborhood = m_strStudent_Neighborhood;
	m_oStudent.m_strStudent_Address = m_strStudent_Address;
	objList.push_back(m_oStudent);

	m_oStudent.m_strStudent_FirstName = m_strParent_Fn;
	m_oStudent.m_strStudent_LastName = m_strParent_Ln;
	m_oStudent.m_strStudent_Email = m_strParent_Email;
	m_oStudent.m_strStudent_PhoneNumber = m_strParent_PhoneNumber;
	m_oStudent.m_strStudent_City = m_strParent_City;
	m_oStudent.m_strStudent_PostCode = m_strParent_PostCode;
	m_oStudent.m_strStudent_Neighborhood = m_strParent_Neighborhood;
	m_oStudent.m_strStudent_Address = m_strParent_Address;
	objList.push_back(m_oStudent);

	m_oStudent.m_objList = objList;
	CDialogEx::OnOK();
}