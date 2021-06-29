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
	m_eParentMode = eRecordMode_None;
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
	CString formatStr = _T("yyyy'-'MM'-'dd");
	m_dtStudent_CtrlBirthday.SetFormat(formatStr);
	DDX_Text(pDX, IDC_EDIT_STUDENT_EMAIL, m_strStudent_Email);
	DDX_Text(pDX, IDC_EDIT_STUDENT_PHONE_NUMBER, m_strStudent_PhoneNumber);
	DDX_Text(pDX, IDC_EDIT_STUDENT_EGN, m_strStudent_EGN);
	DDX_Text(pDX, IDC_EDIT_STUDENT_CITY, m_strStudent_City);
	DDX_Text(pDX, IDC_EDIT_STUDENT_POST_CODE, m_strStudent_PostCode);
	DDX_Text(pDX, IDC_EDIT_STUDENT_NEIGHBORHOOD, m_strStudent_Neighborhood);
	DDX_Text(pDX, IDC_EDIT_STUDENT_ADDRESS, m_strStudent_Address);
}


BOOL CStudentDlg::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;
	
	//Set Title boxes
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
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVGF_SUBSETITEMS);
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Email", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Phone number", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("City", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Post code", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Neighborhood", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Address", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	if (m_eMode != eDialogMode_Add)
		LoadParents(m_oStudent.m_iStudentId);

	m_listCtrl.SetBkColor(GetSysColor(COLOR_3DFACE));

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i)
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);



	return TRUE;
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
	m_strStudent_ClassNum =	oLib.IntToCString(m_oStudent.m_iStudentId);
	m_strStudent_Fn = m_oStudent.m_strFirstName;
	m_strStudent_Ln = m_oStudent.m_strLastName;
	m_strStudent_PhoneNumber = m_oStudent.m_strPhoneNumber;
	m_strStudent_Email = m_oStudent.m_strEmail;
	m_strStudent_EGN = m_oStudent.m_strEgn;
	m_strStudent_City =	m_oStudent.m_strCity;
	m_strStudent_PostCode =	m_oStudent.m_strPostCode;
	m_strStudent_Neighborhood = m_oStudent.m_strNeighborhood;
	m_strStudent_Address = m_oStudent.m_strAddress;

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
	(FALSE);
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

BEGIN_MESSAGE_MAP(CStudentDlg, CDialogEx)
	ON_WM_CONTEXTMENU()
	ON_BN_CLICKED(IDC_MENU_ADD_PARENT, OnAddParent)
	ON_BN_CLICKED(IDC_MENU_EDIT_PARENT, OnEditParent)
	ON_BN_CLICKED(IDC_MENU_DEL_PARENT, OnDeleteParent)
	ON_BN_CLICKED(IDC_MENU_VIEW_PARENT, OnViewParent)
	ON_BN_CLICKED(IDOK, &CStudentDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_PARENT, &CStudentDlg::OnNMDblclkList)
END_MESSAGE_MAP()

void CStudentDlg::OnContextMenu(CWnd* pWnd, CPoint point)
{
	if (m_eMode == eDialogMode_View) {
		return;
	}

	POSITION pos = m_listCtrl.GetFirstSelectedItemPosition();
	
	bool bIsItemSelected = pos != NULL;

	//if (m_eParentMode != eRecordMode_None) 
	//{
	//	int nItem = m_listCtrl.GetNextSelectedItem(pos);
	//	int nId = (int)m_listCtrl.GetItemData(nItem);
	//
	//	if (nId == 0)
	//		return;
	//}

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
	//m_eParentMode = eRecordMode_Add;

	CParentData oParentData;
	CParentDlg dlg(oParentData, eDialogMode_Add);
	
	if (dlg.DoModal() != IDOK) {
		return;
	}

	oParentData.m_eRecordMode = eRecordMode_Add;
	m_oStudent.m_arrParents.push_back(oParentData);

	//Add parent in list
	int nCount = m_listCtrl.GetItemCount();

	Library oLib;

	int nItemIndex = m_listCtrl.InsertItem(nCount, "0");

	if (nItemIndex > -1)
	{
		CString strName = oParentData.m_strFirstName + " " + oParentData.m_strLastName;
		m_listCtrl.SetItemText(nItemIndex, 1, strName);
		m_listCtrl.SetItemText(nItemIndex, 2, oParentData.m_strEmail);
		m_listCtrl.SetItemText(nItemIndex, 3, oParentData.m_strPhoneNumber);
		m_listCtrl.SetItemText(nItemIndex, 4, oParentData.m_strCity);
		m_listCtrl.SetItemText(nItemIndex, 5, oParentData.m_strPostCode);
		m_listCtrl.SetItemText(nItemIndex, 6, oParentData.m_strNeighborhood);
		m_listCtrl.SetItemText(nItemIndex, 7, oParentData.m_strAddress);

		//set index back item
		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)oParentData.m_iParentId);
	}
}

void CStudentDlg::OnEditParent()
{
	//m_eParentMode = eRecordMode_Edit;

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
	CParentData oOldParentData;

	//find parent in list
	oParentData =  *find_if(std::begin(m_oStudent.m_arrParents), std::end(m_oStudent.m_arrParents),
		[&](CParentData const& p) { return p.m_iParentId == nId; });

	CParentDlg dlg(oParentData, eDialogMode_Edit);
	
	if (dlg.DoModal() != IDOK)
		return;
	
	m_oStudent.m_arrParents.erase(remove_if(m_oStudent.m_arrParents.begin(), m_oStudent.m_arrParents.end(),
		[&](CParentData const& p) { return p.m_iParentId == nId; }));

	oParentData.m_eRecordMode = eRecordMode_Edit;
	m_oStudent.m_arrParents.push_back(oParentData);

	//Show change parent
	CString strName = oParentData.m_strFirstName + " " + oParentData.m_strLastName;
	m_listCtrl.SetItemText(nItem, 1, strName);
	m_listCtrl.SetItemText(nItem, 2, oParentData.m_strEmail);
	m_listCtrl.SetItemText(nItem, 3, oParentData.m_strPhoneNumber);
	m_listCtrl.SetItemText(nItem, 4, oParentData.m_strCity);
	m_listCtrl.SetItemText(nItem, 5, oParentData.m_strPostCode);
	m_listCtrl.SetItemText(nItem, 6, oParentData.m_strNeighborhood);
	m_listCtrl.SetItemText(nItem, 7, oParentData.m_strAddress);
}

void CStudentDlg::OnDeleteParent()
{
	//m_eParentMode = eRecordMode_Delete;

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
	message.Format("Do you want to delete parent with # %d?", nId);
	int result = MessageBox(message, "Delete Parent", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

	CParentData oParentData;
	oParentData.m_eRecordMode = eRecordMode_Delete;
	oParentData.m_iParentId = nId;

	//Remove old 
	m_oStudent.m_arrParents.erase(remove_if(m_oStudent.m_arrParents.begin(), m_oStudent.m_arrParents.end(),
		[&](CParentData const& p) { return p.m_iParentId == nId; }));
	
	m_oStudent.m_arrParents.push_back(oParentData);

	m_listCtrl.DeleteItem(nItem);
}

void CStudentDlg::OnViewParent()
{
	//m_eParentMode = eRecordMode_View;

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

	if (nId == 0) {
		return;
	}

	CParent oParent;
	CParentData oParentData;
	
	oParentData.m_iParentId = nId;

	if (!oParent.LoadParent(oParentData))
		return;

	CParentDlg dlg(oParentData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;
}

void CStudentDlg::OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult)
{
	OnViewParent();
}

void CStudentDlg::LoadParents(const int& nIdStudent) 
{
	m_listCtrl.DeleteAllItems();
	m_lParents.clear();

	Library oLib;

	int nCount = 0;
	int nItemIndex = 0;

	for (auto& i = m_oStudent.m_arrParents.begin(); i != m_oStudent.m_arrParents.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).m_iParentId));

		if (nItemIndex > -1)
		{
			CString strName = (*i).m_strFirstName + " " + (*i).m_strLastName;
			m_listCtrl.SetItemText(nItemIndex, 1, strName);
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).m_strEmail);
			m_listCtrl.SetItemText(nItemIndex, 3, (*i).m_strPhoneNumber);
			m_listCtrl.SetItemText(nItemIndex, 4, (*i).m_strCity);
			m_listCtrl.SetItemText(nItemIndex, 5, (*i).m_strPostCode);
			m_listCtrl.SetItemText(nItemIndex, 6, (*i).m_strNeighborhood);
			m_listCtrl.SetItemText(nItemIndex, 7, (*i).m_strAddress);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->m_iParentId);
		}
	}

	/*DATA FROM STRUCT*/
	//list<PARENT> listStudents;
	//CParent oParent;
	//oParent.PrintParent(nIdStudent, m_lParents);
	//for (auto& i = m_lParents.begin(); i != m_lParents.end(); i++)
	//{
	//	//get Count list items
	//	nCount = m_listCtrl.GetItemCount();
	//
	//	nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).iId));
	//
	//	if (nItemIndex > -1)
	//	{
	//		m_listCtrl.SetItemText(nItemIndex, 1, (*i).szName);
	//		m_listCtrl.SetItemText(nItemIndex, 2, (*i).szEmail);
	//		m_listCtrl.SetItemText(nItemIndex, 3, (*i).szPhoneNumber);
	//		m_listCtrl.SetItemText(nItemIndex, 4, (*i).szCity);
	//		m_listCtrl.SetItemText(nItemIndex, 5, (*i).szPostCode);
	//		m_listCtrl.SetItemText(nItemIndex, 6, (*i).szNeighborhood);
	//		m_listCtrl.SetItemText(nItemIndex, 7, (*i).szAddress);
	//
	//		//set index back item
	//		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->iId);
	//	}
	//}
}

BOOL CStudentDlg::ValidateStudent()
{
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
	return TRUE;
}

void CStudentDlg::OnBnClickedOk()
{
	UpdateData(TRUE);

	if (m_eMode != eDialogMode_View && !ValidateStudent()) {
		return;
	}
	
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
	
	CDialogEx::OnOK();
}