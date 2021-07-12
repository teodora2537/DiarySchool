#include "pch.h"
#include "CTabReference.h"

IMPLEMENT_DYNAMIC(CTabReference, CDialogEx)

CTabReference::CTabReference()
	: CDialogEx(IDD_DIALOG_TAB_REFERENCES)
{
	m_bIsOnlyNames = false;
}

CTabReference::~CTabReference()
{
}

void CTabReference::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_REFERENCE, m_listCtrl);

}

BEGIN_MESSAGE_MAP(CTabReference, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AVG_SCORE_BY_SUBJECT, &CTabReference::OnBnClickedButtonAvgScoreBySubject)
	ON_BN_CLICKED(IDC_BUTTON_AVG_SCORE, &CTabReference::OnBnClickedButtonAvgScore)
	ON_BN_CLICKED(IDC_BUTTON_EXCELLENT_STUDENT, &CTabReference::OnBnClickedButtonExcellentStudent)
	ON_BN_CLICKED(IDC_BUTTON_BIRTDAYS, &CTabReference::OnBnClickedButtonBirtdays)
	ON_BN_CLICKED(IDC_BUTTON_CORRECTION_BY_SUBJECT, &CTabReference::OnBnClickedButtonCorrectionBySubject)
	ON_BN_CLICKED(IDC_BUTTON_CORRECTION_BY_MORE_SUBJECTS, &CTabReference::OnBnClickedButtonCorrectionByMoreSubjects)
END_MESSAGE_MAP()

BOOL CTabReference::OnInitDialog()
{
	if (!__super::OnInitDialog())
		return FALSE;

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

// Print average score by subject
void CTabReference::OnBnClickedButtonAvgScoreBySubject()
{
	m_bIsOnlyNames = false;

	ClearList();

	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Subject", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Avg score", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);

	CStudent oStudent;
	oStudent.AvgScoreBySubject(m_listReference);
	LoadData();

	//m_listCtrl.SetColumnWidth(3, 0); // hight column	
}

// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgScore()
{
	m_bIsOnlyNames = false;

	ClearList();
	
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Avg score", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);

	CStudent oStudent;
	oStudent.AvgScoreByAllSubject(m_listReference);
	LoadData();
}

//Correct by subject
void CTabReference::OnBnClickedButtonCorrectionBySubject()
{
	m_bIsOnlyNames = false;

	ClearList();
	
	m_listCtrl.InsertColumnAtEnd("#", eListCtrlColumnTypeData_Int, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);
	m_listCtrl.InsertColumnAtEnd("Subject", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	CStudent oStudent;
	oStudent.AvgScoreBySubject(m_listReference);
	LoadData();
}

//Print excelent student
void CTabReference::OnBnClickedButtonExcellentStudent()
{
	m_bIsOnlyNames = true;

	ClearList();

	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	CStudent oStudent;
	oStudent.ExcellentStud(m_listReference);
	LoadData();
}

//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	m_bIsOnlyNames = true;

	ClearList();
	
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	CStudent oStudent;
	oStudent.PeopleHaveBirthday(m_listReference);
	LoadData();
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonCorrectionByMoreSubjects()
{
	m_bIsOnlyNames = true;

	ClearList();
	m_listCtrl.InsertColumnAtEnd("Name", eListCtrlColumnTypeData_String, LVCFMT_LEFT);

	CStudent oStudent;
	oStudent.RemedialExaminationByMoreSub(m_listReference);
	LoadData();
}

void CTabReference::LoadData() 
{
	//fill datas in listCtrl
	Library oLib;
	int iId = 0;
	int nCount = 0;
	int nItemIndex = 0;
	CString strClmn;

	for (auto& it = m_listReference.begin(); it != m_listReference.end(); it++)
	{
		nCount = m_listCtrl.GetItemCount();
		nItemIndex = m_listCtrl.InsertItem(nCount, it->szClm0);
		
		if (nCount > -1) 
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->szClm1);
			m_listCtrl.SetItemText(nItemIndex, 2, it->szClm2);
			if (it->szClm3 != "") {
				m_listCtrl.SetItemText(nItemIndex, 3, it->szClm3);
			}
		}

		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)iId);
		iId++;
	}

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}
}

void CTabReference::ClearList()
{
	Library oLib;
	m_listReference.clear();
	oLib.ClearListCtrl(m_listCtrl);

	if (m_listReference.size() != 0)
	{
		MessageBox("The list is not empty!");
		return;
	}
}