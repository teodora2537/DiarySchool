#include "pch.h"
#include "MFCApplication.h"
#include "CTabReference.h"
using namespace std;

IMPLEMENT_DYNAMIC(CTabReference, CDialogEx)

CTabReference::CTabReference()
	: CDialogEx(IDD_TAB_REFERENCES)
{

}

CTabReference::~CTabReference()
{
}

void CTabReference::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
}

BEGIN_MESSAGE_MAP(CTabReference, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AvgScoreBySubject, &CTabReference::OnBnClickedButtonAvgscorebysubject)
	ON_BN_CLICKED(IDC_BUTTON_AvgScoreByAllSubjects, &CTabReference::OnBnClickedButtonAvgscorebyallsubjects)
	ON_BN_CLICKED(IDC_BUTTON_ExcellentStudent, &CTabReference::OnBnClickedButtonExcellentstudent)
	ON_BN_CLICKED(IDC_BUTTON_BIRTDAYS, &CTabReference::OnBnClickedButtonBirtdays)
	ON_BN_CLICKED(IDC_BUTTON_, &CTabReference::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON_BY_MORE_SUBJECTS, &CTabReference::OnBnClickedButtonByMoreSubjects)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST, &CTabReference::OnLvnColumnclickList)
END_MESSAGE_MAP()

// Print average score by subject
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	Library oLib;
	m_bIsOnlyNames = false;

	m_listReference.clear();

	m_orderClm0 = m_orderClm1 = m_orderClm2 = m_orderClm3 = SORT_None;

	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, "Avg score", LVCFMT_LEFT, 70);

	m_strName = "Avg score by subject";
	LoadData(m_strName);
}

// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{
	Library oLib;
	m_bIsOnlyNames = false;

	m_listReference.clear();

	m_orderClm0 = m_orderClm1 = m_orderClm2 = m_orderClm3 = SORT_None;

	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Avg score", LVCFMT_LEFT, 70);
	
	m_strName = "Avg score";
	LoadData(m_strName);
}

//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	Library oLib;

	m_bIsOnlyNames = false;

	m_listReference.clear();

	m_orderClm0 = m_orderClm1 = m_orderClm2 = m_orderClm3 = SORT_None;

	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);

	m_strName = "Correct by subject";
	LoadData(m_strName);
}

//Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	Library oLib;
	m_listReference.clear();
	
	m_orderClm0 = SORT_None;

	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
	m_bIsOnlyNames = true;

	m_strName = "Excellent";
	LoadData(m_strName);
}

//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	Library oLib;
	m_bIsOnlyNames = true;

	m_listReference.clear();

	m_orderClm0 = SORT_None;

	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);

	m_strName = "Birthday";
	LoadData(m_strName);
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	Library oLib;
	m_bIsOnlyNames = true;

	m_listReference.clear();

	m_orderClm0 = SORT_None;
	
	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);

	m_strName = "Correct by more subject";
	LoadData(m_strName);
}

void CTabReference::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	int iSortClmReference = -1;
	iSortClmReference = pNMLV->iSubItem; //save column for the callback

	if (iSortClmReference == 0)
	{
		if (m_orderClm0 == SORT_None)m_orderClm0 = SORT_AZ;
		else m_orderClm0 = (SortOrder) - m_orderClm0; // -1 to 1, 1 to -1
		m_sortOrderReference = m_orderClm0;
	}
	else if (iSortClmReference == 1)
	{
		if (m_orderClm1 == SORT_None) m_orderClm1 = SORT_AZ;
		else m_orderClm1 = (SortOrder) - m_orderClm1;
		m_sortOrderReference = m_orderClm1;
	}
	else if (iSortClmReference == 2)
	{
		if (m_orderClm2 == SORT_None)  m_orderClm2 = SORT_AZ;
		else m_orderClm2 = (SortOrder) - m_orderClm2;
		m_sortOrderReference = m_orderClm2;
	}
	else if (iSortClmReference == 3)
	{
		if (m_orderClm3 == SORT_None) m_orderClm3 = SORT_AZ;
		else m_orderClm3 = (SortOrder) - m_orderClm3;
		m_sortOrderReference = m_orderClm3;
	}
	
	CListMethods oList;
	oList.SortListReference(iSortClmReference, m_listReference, m_sortOrderReference, m_bIsOnlyNames);
	m_listCtrl.DeleteAllItems();
	LoadData(m_strName);

	*pResult = 0;
}

void CTabReference::LoadData(CString name) {

	Library oLib;
	CStudent oStudent;

	if (m_listReference.size() == 0)
	{
		if (name == "Excellent") {
			oStudent.ExcellentStud(m_listReference);
		}
		else if (name == "Birthday") {
			oStudent.PeopleHaveBirthday(m_listReference);
		}
		else if (name == "Correct by more subject") {
			oStudent.RemedialExaminationByMoreSub(m_listReference);
		}
		else if (name == "Avg score by subject") {
			oStudent.AvgScoreBySubject(m_listReference);
		}
		else if (name == "Avg score") {
			oStudent.AvgScoreByAllSubject(m_listReference);
		}
		else if (name == "Correct by subject") {
			oStudent.RemedialExaminationBySub(m_listReference);
		}
	}

	int nCount = 0;
	int nItemIndex = 0;
	int iId = 0;

	for (auto& it = m_listReference.begin(); it != m_listReference.end(); it++)
	{
		nCount = m_listCtrl.GetItemCount();
		
		if (name == "Excellent" || name == "Birthday" || name == "Correct by more subject" || name == "")
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