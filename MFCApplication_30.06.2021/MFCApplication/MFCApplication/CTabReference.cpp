#include "pch.h"
#include "CTabReference.h"

IMPLEMENT_DYNAMIC(CTabReference, CDialogEx)

CTabReference::CTabReference()
	: CDialogEx(IDD_TAB_REFERENCES)
{
	m_bIsOnlyNames = false;
}

CTabReference::~CTabReference()
{
}

void CTabReference::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);

}

BEGIN_MESSAGE_MAP(CTabReference, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AvgScoreBySubject, &CTabReference::OnBnClickedButtonAvgscorebysubject)
	ON_BN_CLICKED(IDC_BUTTON_AvgScoreByAllSubjects, &CTabReference::OnBnClickedButtonAvgscorebyallsubjects)
	ON_BN_CLICKED(IDC_BUTTON_ExcellentStudent, &CTabReference::OnBnClickedButtonExcellentstudent)
	ON_BN_CLICKED(IDC_BUTTON_BIRTDAYS, &CTabReference::OnBnClickedButtonBirtdays)
	ON_BN_CLICKED(IDC_BUTTON_, &CTabReference::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON_BY_MORE_SUBJECTS, &CTabReference::OnBnClickedButtonByMoreSubjects)
END_MESSAGE_MAP()

BOOL CTabReference::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

// Print average score by subject
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	Library oLib;
	m_bIsOnlyNames = false;

	m_listReference.clear();

	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int,LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Subject", eListCtrlColumnTypeData_String,LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Avg score", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);

	m_strName = "Avg score by subject";
	LoadData();

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{
	Library oLib;
	m_bIsOnlyNames = false;

	m_listReference.clear();

	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Avg score", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	
	m_strName = "Avg score";
	LoadData();

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	Library oLib;

	m_bIsOnlyNames = false;

	m_listReference.clear();

	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Subject", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	m_strName = "Correct by subject";
	LoadData();

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

//Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	Library oLib;
	m_listReference.clear();

	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_bIsOnlyNames = true;

	m_strName = "Excellent";
	LoadData();

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	Library oLib;
	m_bIsOnlyNames = true;

	m_listReference.clear();

	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	m_strName = "Birthday";
	LoadData();

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	Library oLib;
	m_bIsOnlyNames = true;

	m_listReference.clear();
	
	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	m_strName = "Correct by more subject";
	LoadData();

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

void CTabReference::LoadData() 
{
	CStudent oStudent;

	if (m_listReference.size() != 0)
	{
		MessageBox("The list is not empty!");
		return;
	}
	
	if (m_strName == "Excellent") {
		oStudent.ExcellentStud(m_listReference);
	}
	else if (m_strName == "Birthday") {
		oStudent.PeopleHaveBirthday(m_listReference);
	}
	else if (m_strName == "Correct by more subject") {
		oStudent.RemedialExaminationByMoreSub(m_listReference);
	}
	else if (m_strName == "Avg score by subject") {
		oStudent.AvgScoreBySubject(m_listReference);
	}
	else if (m_strName == "Avg score") {
		oStudent.AvgScoreByAllSubject(m_listReference);
	}
	else if (m_strName == "Correct by subject") {
		oStudent.RemedialExaminationBySub(m_listReference);
	}

	Library oLib;
	int nCount = 0;
	int nItemIndex = 0;
	int iId = 0;

	for (auto& it = m_listReference.begin(); it != m_listReference.end(); it++)
	{
		nCount = m_listCtrl.GetItemCount();
		
		if (m_strName == "Excellent" || m_strName == "Birthday" || m_strName == "Correct by more subject")
		{
			nItemIndex = m_listCtrl.InsertItem(nCount, it->szClm0);
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)iId);
			iId++;
			continue;
		}
	
		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->iId));

		if (nCount > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->szClm1);
			m_listCtrl.SetItemText(nItemIndex, 2, it->szClm2);
		
			if (it->szClm3 != "")
				m_listCtrl.SetItemText(nItemIndex, 3, it->szClm3);

			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->iId);
		}
	}
}