#include "pch.h"
#include "CTabReference.h"

IMPLEMENT_DYNAMIC(CTabReference, CDialogEx)

CTabReference::CTabReference()
	: CDialogEx(IDD_DIALOG_TAB_REFERENCES)
{
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

DataColumn::DataColumn(CString strName, ListCtrlColumnTypeData eColumnType)
{
	m_strName = strName; 
	m_eColumnType = eColumnType;
}


// Print average score by subject
void CTabReference::OnBnClickedButtonAvgScoreBySubject()
{
	ClearList();

	m_lClmn.push_back(new DataColumn("#", eListCtrlColumnTypeData_Int));
	m_lClmn.push_back(new DataColumn("Name", eListCtrlColumnTypeData_String));
	m_lClmn.push_back(new DataColumn("Subject", eListCtrlColumnTypeData_String));
	m_lClmn.push_back(new DataColumn("Avg score", eListCtrlColumnTypeData_Int));

	CStudent oStudent;
	oStudent.AvgScoreBySubject(m_listReference);
	LoadData();
}

// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgScore()
{
	ClearList();
	
	m_lClmn.push_back(new DataColumn("#", eListCtrlColumnTypeData_Int));
	m_lClmn.push_back(new DataColumn("Name", eListCtrlColumnTypeData_String));
	m_lClmn.push_back(new DataColumn("Avg score", eListCtrlColumnTypeData_Int));
	
	CStudent oStudent;
	oStudent.AvgScoreByAllSubject(m_listReference);
	LoadData();
}

//Correct by subject
void CTabReference::OnBnClickedButtonCorrectionBySubject()
{
	ClearList();
	
	m_lClmn.push_back(new DataColumn("#", eListCtrlColumnTypeData_Int));
	m_lClmn.push_back(new DataColumn("Name", eListCtrlColumnTypeData_String));
	m_lClmn.push_back(new DataColumn("Subject", eListCtrlColumnTypeData_String));

	CStudent oStudent;
	oStudent.AvgScoreBySubject(m_listReference);
	LoadData();
}

//Print excelent student
void CTabReference::OnBnClickedButtonExcellentStudent()
{
	ClearList();

	m_lClmn.push_back(new DataColumn("Name", eListCtrlColumnTypeData_String));

	CStudent oStudent;
	oStudent.ExcellentStud(m_listReference);
	LoadData();
}

//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	ClearList();
	
	m_lClmn.push_back(new DataColumn("Name", eListCtrlColumnTypeData_String));

	CStudent oStudent;
	oStudent.PeopleHaveBirthday(m_listReference);
	LoadData();
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonCorrectionByMoreSubjects()
{
	ClearList();
	m_lClmn.push_back(new DataColumn("Name", eListCtrlColumnTypeData_String));

	CStudent oStudent;
	oStudent.RemedialExaminationByMoreSub(m_listReference);
	LoadData();
}

void CTabReference::LoadData() 
{
	//create column
	for (auto i = m_lClmn.begin(); i != m_lClmn.end(); ++i) {
		m_listCtrl.InsertColumnAtEnd((*i)->m_strName, (*i)->m_eColumnType, LVCFMT_LEFT);
	}

	//fill datas in listCtrl
	int iId = 0;
	int nCount = 0;
	int nItemIndex = 0;

	for (auto& it = m_listReference.begin(); it != m_listReference.end(); it++)
	{
		nCount = m_listCtrl.GetItemCount();
		nItemIndex = m_listCtrl.InsertItem(nCount, it->szClm0);
		
		if(nCount > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->szClm1);
			m_listCtrl.SetItemText(nItemIndex, 2, it->szClm2);
			m_listCtrl.SetItemText(nItemIndex, 3, it->szClm3);
		}

		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)iId);
		iId++;
	}

	//autosize column
	for (int i = 0; i < m_listCtrl.GetHeaderCtrl()->GetItemCount(); ++i) {
		m_listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);
	}

	//clear list column
	m_lClmn.clear();
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