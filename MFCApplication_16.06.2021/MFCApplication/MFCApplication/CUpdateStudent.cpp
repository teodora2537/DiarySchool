#include "pch.h"
#include "MFCApplication.h"
#include "CUpdateStudent.h"
#include "CStudentTable.h"
#include <list>
#include "CParent.h"
#include "CParentDlg.h"
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
	DDX_Control(pDX, IDC_LIST_PARENT, m_listCtrl);
	//student
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strStudent_ClassNum);
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_FN, m_strStudent_Fn);
	DDV_MaxChars(pDX, m_strStudent_Fn, 20);//Size of FN student
	DDX_Text(pDX, IDC_EDIT_UPDATE_STUDENT_LN, m_strStudent_Ln);
	DDV_MaxChars(pDX, m_strStudent_Ln, 15);//Size of LN student
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_dtStudent_CtrlBirthday);
	CString formatStr = _T("MM'/'dd'/'yyyy");
	m_dtStudent_CtrlBirthday.SetFormat(formatStr);
	DDX_Text(pDX, IDC_EDIT_STUDENT_EMAIL, m_strStudent_Email);
	DDX_Text(pDX, IDC_EDIT_STUDENT_PHONE_NUMBER, m_strStudent_PhoneNumber);
	DDX_Text(pDX, IDC_EDIT_STUDENT_EGN, m_strStudent_EGN);
	DDX_Text(pDX, IDC_EDIT_STUDENT_CITY, m_strStudent_City);
	DDX_Text(pDX, IDC_EDIT_STUDENT_POST_CODE, m_strStudent_PostCode);
	DDX_Text(pDX, IDC_EDIT_STUDENT_NEIGHBORHOOD, m_strStudent_Neighborhood);
	DDX_Text(pDX, IDC_EDIT_STUDENT_ADDRESS, m_strStudent_Address);

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
	m_strStudent_ClassNum =		oLib.IntToCString(m_oStudent.m_iStudentId);
	m_strStudent_Fn =			m_oStudent.m_strFirstName;
	m_strStudent_Ln =			m_oStudent.m_strLastName;
	m_strStudent_PhoneNumber =	m_oStudent.m_strPhoneNumber;
	m_strStudent_Email =		m_oStudent.m_strEmail;
	m_strStudent_EGN =			m_oStudent.m_strEgn;
	m_strStudent_City =			m_oStudent.m_strCity;
	m_strStudent_PostCode =		m_oStudent.m_strPostCode;
	m_strStudent_Neighborhood = m_oStudent.m_strNeighborhood;
	m_strStudent_Address =		m_oStudent.m_strAddress;

	if (m_eMode != eDialogMode_Add)
	{
		m_dtStudent_CtrlBirthday.SetTime(m_oStudent.m_oleDTBirthday);
	}

	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM, m_strStudent_ClassNum);
	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_FN, m_strStudent_Fn);
	SetDlgItemText(IDC_EDIT_UPDATE_STUDENT_LN, m_strStudent_Ln);
	SetDlgItemText(IDC_EDIT_STUDENT_EMAIL, m_strStudent_Email);
	SetDlgItemText(IDC_EDIT_STUDENT_PHONE_NUMBER, m_strStudent_PhoneNumber);
	SetDlgItemText(IDC_EDIT_STUDENT_EGN, m_strStudent_EGN);
	SetDlgItemText(IDC_EDIT_STUDENT_CITY, m_strStudent_City);
	SetDlgItemText(IDC_EDIT_STUDENT_POST_CODE, m_strStudent_PostCode);
	SetDlgItemText(IDC_EDIT_STUDENT_NEIGHBORHOOD, m_strStudent_Neighborhood);
	SetDlgItemText(IDC_EDIT_STUDENT_ADDRESS, m_strStudent_Address);
}

/*Set enable/disable of edit boxes*/
void CStudentDlg::EnableDisableBoxes()
{
	BOOL bEnable = m_eMode != eDialogMode_View;

	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_CLASS_NUM)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_FN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_UPDATE_STUDENT_LN)->EnableWindow(bEnable);
	m_dtStudent_CtrlBirthday.EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_EMAIL)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_PHONE_NUMBER)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_EGN)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_CITY)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_POST_CODE)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_NEIGHBORHOOD)->EnableWindow(bEnable);
	GetDlgItem(IDC_EDIT_STUDENT_ADDRESS)->EnableWindow(bEnable);
}

BOOL CStudentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;
	
	//BOXES
	if (m_eMode == eDialogMode_Add) {
		this->SetWindowText("Add Student");
	}
	else if (m_eMode == eDialogMode_Edit) {
		this->SetWindowText("Edit Student");
	}
	else if (m_eMode == eDialogMode_View) {
		this->SetWindowText("Student");
	}

	/*Set enable/disable of edit boxes*/
	EnableDisableBoxes();
	
	/*Fill edit boxes*/
	FillEditBoxes();

	/*Set range date*/
	SetRangeOfDTPicker();

	//LIST
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumnAtEnd("Email", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 200);
	m_listCtrl.InsertColumnAtEnd("Phone number", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumnAtEnd("City", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 70);
	m_listCtrl.InsertColumnAtEnd("Post code", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 70);
	m_listCtrl.InsertColumnAtEnd("Neighborhood", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumnAtEnd("Address", eListCtrlColumnTypeData_String, LVCFMT_LEFT, 600);

	if (m_eMode != eDialogMode_Add)
		LoadParents(m_oStudent.m_iStudentId);

	return TRUE;
}

BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_PARENT, OnAddParent)
	ON_BN_CLICKED(IDC_MENU_EDIT_PARENT, OnEditParent)
	ON_BN_CLICKED(IDC_MENU_DEL_PARENT, OnDeleteParent)
	ON_BN_CLICKED(IDC_MENU_VIEW_PARENT, OnViewParent)
	ON_BN_CLICKED(IDOK, &CStudentDlg::OnBnClickedOk)
END_MESSAGE_MAP()

BOOL CStudentDlg::ValidateData()
{
	//Student
	{
		if (m_strStudent_Fn.IsEmpty())
		{
			MessageBox("Missing first name of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Ln.IsEmpty())
		{
			MessageBox("Missing last name of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Email.IsEmpty())
		{
			MessageBox("Missing email of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_PhoneNumber.IsEmpty() || m_strStudent_PhoneNumber.GetLength() < 8)
		{
			MessageBox("Error phone number of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_EGN.IsEmpty())
		{
			MessageBox("Missing egn of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_City.IsEmpty())
		{
			MessageBox("Missing city of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_PostCode.IsEmpty())
		{
			MessageBox("Missing post code  of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Neighborhood.IsEmpty())
		{
			MessageBox("Missing neighborhood  of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
		else if (m_strStudent_Address.IsEmpty())
		{
			MessageBox("Missing address  of student!", "Error", MB_ICONHAND);
			return FALSE;
		}
	}

	//Parent
	//{
	//	if (m_strParent_Fn.IsEmpty())
	//	{
	//		MessageBox("Missing first name of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//	else if (m_strParent_Ln.IsEmpty())
	//	{
	//		MessageBox("Missing last name of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//	else if (m_strParent_PhoneNumber.IsEmpty() || m_strStudent_PhoneNumber.GetLength() < 8)
	//	{
	//		MessageBox("Error phone number of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//	else if (m_strParent_City.IsEmpty())
	//	{
	//		MessageBox("Missing city of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//	else if (m_strParent_PostCode.IsEmpty())
	//	{
	//		MessageBox("Missing post code of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//	else if (m_strParent_Neighborhood.IsEmpty())
	//	{
	//		MessageBox("Missing neighborhood of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//	else if (m_strParent_Address.IsEmpty())
	//	{
	//		MessageBox("Missing address of parent!", "Error", MB_ICONHAND);
	//		return FALSE;
	//	}
	//}

	return TRUE;
}

void CStudentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateData())
		return;
	
	list<CStudentData> objList;

	m_oStudent.m_iStudentId = atoi(m_strStudent_ClassNum);
	m_oStudent.m_strFirstName = m_strStudent_Fn;
	m_oStudent.m_strLastName = m_strStudent_Ln;
	m_dtStudent_CtrlBirthday.GetTime(m_oStudent.m_oleDTBirthday);
	m_oStudent.m_strEmail = m_strStudent_Email;
	m_oStudent.m_strPhoneNumber = m_strStudent_PhoneNumber;
	m_oStudent.m_strEgn = m_strStudent_EGN;
	m_oStudent.m_strCity = m_strStudent_City;
	m_oStudent.m_strPostCode = m_strStudent_PostCode;
	m_oStudent.m_strNeighborhood = m_strStudent_Neighborhood;
	m_oStudent.m_strAddress = m_strStudent_Address;
	objList.push_back(m_oStudent);
	
	//m_oStudent.m_iStudentId = 15;
	//m_oStudent.m_strFirstName = "test2";
	//m_oStudent.m_strLastName = "tets2";
	//m_dtStudent_CtrlBirthday.GetTime(m_oStudent.m_oleDTBirthday);
	//m_oStudent.m_strEmail = "test@mail.bg";
	//m_oStudent.m_strPhoneNumber = "0896541235";
	//m_oStudent.m_strEgn = "9785641236";
	//m_oStudent.m_strCity = "Varna";
	//m_oStudent.m_strPostCode = "9000";
	//m_oStudent.m_strNeighborhood = "Mladost";
	//m_oStudent.m_strAddress = "fjkhfkhgkjdfhgkfjdh";
	//objList.push_back(m_oStudent);
	//
	//m_oStudent.m_iParentId = 22;
	//m_oStudent.m_iStudentId = 15;
	//m_oStudent.m_strFirstName = "Plamenaaaa";
	//m_oStudent.m_strLastName = "Kirovaaaaa";
	//m_oStudent.m_strEmail = "PlamenaKirova@gmail.com";
	//m_oStudent.m_strPhoneNumber = "0879544566";
	//m_oStudent.m_strCity = "Plovdiv";
	//m_oStudent.m_strPostCode = "4000      ";
	//m_oStudent.m_strNeighborhood = "Mladost";
	//m_oStudent.m_strAddress = "ul. Konstantin Stoilov 19, bl.3 vh.3 et.1 ap.3";
	//objList.push_back(m_oStudent);

	m_oStudent.m_objList = objList;
	CDialogEx::OnOK();
}

void CStudentDlg::LoadParents(const int& nIdStudent) 
{
	m_listCtrl.DeleteAllItems();
	list<PARENT> listStudents;
	m_lParents.clear();

	CParent oParent;
	oParent.PrintParent(nIdStudent, m_lParents);

	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	for (auto& i = m_lParents.begin(); i != m_lParents.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).iId));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).szName);
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).szEmail);
			m_listCtrl.SetItemText(nItemIndex, 3, (*i).szPhoneNumber);
			m_listCtrl.SetItemText(nItemIndex, 4, (*i).szCity);
			m_listCtrl.SetItemText(nItemIndex, 5, (*i).szPostCode);
			m_listCtrl.SetItemText(nItemIndex, 6, (*i).szNeighborhood);
			m_listCtrl.SetItemText(nItemIndex, 7, (*i).szAddress);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->iId);
		}
	}
}

void CStudentDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	bool bIsItemSelected = pos != NULL;

	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_PARENT, "Add parent");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_PARENT, "Edit parent");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_PARENT, "Delete parent");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_PARENT, "View parent");

	//disable edit/delete/view from submenu
	submenu.EnableMenuItem(IDC_MENU_EDIT_PARENT, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_DEL_PARENT, !bIsItemSelected);
	submenu.EnableMenuItem(IDC_MENU_VIEW_PARENT, !bIsItemSelected);

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
}

void CStudentDlg::OnAddParent()
{
	CParentDlg dlg(m_oStudent.m_objList, eDialogMode_Add);
	
	if (dlg.DoModal() != IDOK)
		return;
	CStudent oStudent;
	if (!oStudent.AddStudent(m_oStudent))
	{
		if (IDRETRY)
			OnAddParent();
		return;
	}
	CStudentData oStudentData;
	LoadParents(oStudentData.m_iStudentId);
}

//Dovurshi
void CStudentDlg::OnEditParent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	//if don't get selected item
	if (nItem < 0)
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CStudentData oStudentData;
	CStudent oStudent;

	if (!oStudent.LoadStudent(nId, oStudentData))
		return;

	CStudentDlg dlg(oStudentData, eDialogMode_Edit);

	if (dlg.DoModal() != IDOK)
		return;


	if (!oStudent.EditStudent(oStudentData)) {

		if (IDRETRY)
			OnEditParent();
		return;
	}

	LoadParents(m_oStudent.m_iStudentId);
}
void CStudentDlg::OnDeleteParent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	if (nItem < 0)
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CStudent oStudent;

	CString message;
	message.Format("Do you want to delete subject with room # %d?", nId);
	int result = MessageBox(message, "Delete student", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	if (!oStudent.DeleteStudent(nId))
		return;

	m_listCtrl.DeleteItem(nItem);
}
void CStudentDlg::OnViewParent()
{
	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();

	if (pos == NULL)
		return;

	int nItem = m_listCtrl.GetNextSelectedItem(pos);

	//if don't get selected item
	if (nItem < 0)
	{
		MessageBox(NULL, "Don't get selected item!", MB_OK | MB_ICONERROR);
		return;
	}

	int nId = (int)m_listCtrl.GetItemData(nItem);

	CParentData oParentData;
	CStudentData oStudentData;

	CParent oParent;

	if (!oParent.LoadParent(nId, oParentData))
		return;

	CStudentDlg dlg(oStudentData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;
}