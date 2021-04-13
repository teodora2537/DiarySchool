#include "pch.h"
#include "MFCApplication.h"
#include "CTabReference.h"
using namespace std;

IMPLEMENT_DYNAMIC(CTabReference, CDialogEx)

CTabReference::CTabReference(CWnd* pParent)
	: CDialogEx(IDD_TAB_REFERENCES, pParent)
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

//global variable
	int nCount = 0;
	int nItemIndex = 0;
	int nIndex = 0;
	bool isOnlyNames = false;

	list<ReferenceStruct> m_listReference;

	SortOrder orderClm0 = SORT_None;
	SortOrder orderClm1= SORT_None;
	SortOrder orderClm2 = SORT_None;
	SortOrder orderClm3 = SORT_None;
	
// Print average score by subject
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	isOnlyNames = false;
	m_listReference.clear();

	orderClm0 = SORT_None;
	orderClm1 = SORT_None;
	orderClm2 = SORT_None;
	orderClm3 = SORT_None;

	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, "Avg score", LVCFMT_LEFT, 70);

	CStudent oStudent;
	oStudent.AvgScoreBySubject(m_listReference);

	SortOrder orderIdStudent = SORT_None;
	SortOrder orderStudents = SORT_None;
	SortOrder orderSub = SORT_None;
	SortOrder orderScore = SORT_None;
	
	for (auto i = m_listReference.begin(); i != m_listReference.end(); i++)
	{
		//id student, full name student, sub, avg score
		LoadStudentInfoFromFile(oLib.IntToCString((*i).nIdStudent),  (*i).strClm1, (*i).strClm2, (*i).strClm3);
	}
}

// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{

	isOnlyNames = false;
	m_listReference.clear();

	CStudent oStudent;
	oStudent.AvgScoreByAllSubject(m_listReference);
	
	orderClm0 = SORT_None;
	orderClm1 = SORT_None;
	orderClm2 = SORT_None;
	orderClm3 = SORT_None;

	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Avg score", LVCFMT_LEFT, 70);
	
	SortOrder orderIdStudent = SORT_None;
	SortOrder orderStudents = SORT_None;
	SortOrder orderSub = SORT_None;
	SortOrder orderScore = SORT_None;

	//idStud , full name student, avg score
	for (auto i = m_listReference.begin(); i != m_listReference.end(); i++)
		LoadStudentInfoFromFile(oLib.IntToCString((*i).nIdStudent), (*i).strClm1, (*i).strClm2, "");
}

//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	isOnlyNames = false;
	m_listReference.clear();

	orderClm0 = SORT_None;
	orderClm1 = SORT_None;
	orderClm2 = SORT_None;
	orderClm3 = SORT_None;

	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);

	CStudent oStudent;

	SortOrder orderIdStudent = SORT_None;
	SortOrder orderStudents = SORT_None;
	SortOrder orderSub = SORT_None;
	SortOrder orderScore = SORT_None;

	oStudent.remedialExaminationBySub(m_listReference);

	//id student, full name, subject 
	for (auto i = m_listReference.begin(); i != m_listReference.end(); i++)
		LoadStudentInfoFromFile(oLib.IntToCString((*i).nIdStudent), (*i).strClm1, (*i).strClm2, "");
}

//Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	orderClm0 = SORT_None;
	isOnlyNames = true;

	m_listReference.clear();
	LoadStudentFromFile("Excellent");
}

//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	isOnlyNames = true;
	orderClm0 = SORT_None;
	
	m_listReference.clear();
	LoadStudentFromFile("Birthday");
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	isOnlyNames = true;
	orderClm0 = SORT_None;
	
	m_listReference.clear();
	LoadStudentFromFile("");
}

SortOrder sortOrderReference = SORT_None;

int sortClmReference = -1; 

void CTabReference::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	sortClmReference = pNMLV->iSubItem; //save column for the callback

	if (sortClmReference == 0)
	{
		if (orderClm0 == SORT_None) orderClm0 = SORT_AZ;
		else orderClm0 = (SortOrder)-orderClm0; // -1 to 1, 1 to -1
		sortOrderReference = orderClm0;
	}
	else if (sortClmReference == 1)
	{
		if (orderClm1 == SORT_None) orderClm1 = SORT_AZ;
		else orderClm1 = (SortOrder)-orderClm1;
		sortOrderReference = orderClm1;
	}
	else if (sortClmReference == 2)
	{
		if (orderClm2 == SORT_None) orderClm2 = SORT_AZ;
		else orderClm2 = (SortOrder)-orderClm2;
		sortOrderReference = orderClm2;
	}
	else if (sortClmReference == 3)
	{
		if (orderClm3 == SORT_None) orderClm3 = SORT_AZ;
		else orderClm3 = (SortOrder)-orderClm3;
		sortOrderReference = orderClm3;
	}
	
	CListMethods oList;
	oList.SortListReference(sortClmReference, m_listReference, sortOrderReference, isOnlyNames);
	
	if(isOnlyNames)
		LoadDataFromListStructNames();
	else
		LoadDataFromListStructInfo();
	*pResult = 0;
}

//print only student's names: excellent, birthday, correct by  more sub
void CTabReference::LoadStudentFromFile(CString name) {
	
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	CStudent oStudent;
	
	if (name == "Excellent")
		oStudent.ExcellentStud(m_listReference);
	else if (name == "Birthday")
		oStudent.PeopleHaveBirthday(m_listReference);
	else
		oStudent.remedialExaminationByMoreSub(m_listReference);
	
	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);

	int id = 0;
	
	for (auto i = m_listReference.begin(); i != m_listReference.end(); i++)
	{
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, i->strClm0);
		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)id);
		id++;
	}
}

//print info for students(functions): Avg score by sub, avg score, correct by sub
void CTabReference::LoadStudentInfoFromFile(CString idStudent, CString nameStud, CString strClm2, CString strClm3) {
	
	nCount = m_listCtrl.GetItemCount();

	nItemIndex = m_listCtrl.InsertItem(nCount, idStudent);

	if (nItemIndex > -1)
	{
		m_listCtrl.SetItemText(nItemIndex, 1, nameStud);
		m_listCtrl.SetItemText(nItemIndex, 2, strClm2);
		if(strClm3 != "")				   
		m_listCtrl.SetItemText(nItemIndex, 3, strClm3);

		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(idStudent));
	}
}

//load only student's names 
void CTabReference::LoadDataFromListStructNames()
{
	m_listCtrl.DeleteAllItems();
	Library oLib;
	CSubject oSubject;

	nCount = 0;
	nItemIndex = 0;
	int id = 0;

	for (list<ReferenceStruct>::iterator it = m_listReference.begin(); it != m_listReference.end(); it++) {

		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, it->strClm0);
		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)id);
		id++;
	}
}

//load info for students
void CTabReference::LoadDataFromListStructInfo() {
	m_listCtrl.DeleteAllItems();
	Library oLib;
	CSubject oSubject;

		nCount = 0;
		nItemIndex = 0;

	//(int)idStudent, nameStud, sub, avgScore	
	for (list<ReferenceStruct>::iterator it = m_listReference.begin(); it != m_listReference.end(); it++) {
			nCount = m_listCtrl.GetItemCount();

			nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString(it->nIdStudent));

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, it->strClm1);
			m_listCtrl.SetItemText(nItemIndex, 2, it->strClm2);
			if (it->strClm3 != "")
				m_listCtrl.SetItemText(nItemIndex, 3, it->strClm3);

			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->nIdStudent);
		}
	}
}