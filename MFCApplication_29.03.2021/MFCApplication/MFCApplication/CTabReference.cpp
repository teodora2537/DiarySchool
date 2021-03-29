#include <list>
#include "pch.h"
#include "MFCApplication.h"
#include "CTabReference.h"
#include "afxdialogex.h"
#include "Library.h"
#include "CUpdateStudent.h"
#include "CUpdateSubject.h"
#include "CUpdateScore.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"
#include "CListMethods.h"

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
	bool isVector = false;

	list<ReferenceStruct> m_listReference;

	SortOrder orderClm0 = SORT_None;
	SortOrder orderClm1= SORT_None;
	SortOrder orderClm2 = SORT_None;
	SortOrder orderClm3 = SORT_None;
	
/*MAP*/
// Print average score by subject
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	isVector = false;
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
	map<vector<CString>, vector<CString>> m_mapAverageScoreBySub;
	oStudent.AverageScoreBySubject(m_mapAverageScoreBySub);
	
	if (m_mapAverageScoreBySub.size() == 0)
		return;

	SortOrder orderIdStudent = SORT_None;
	SortOrder orderStudents = SORT_None;
	SortOrder orderSub = SORT_None;
	SortOrder orderScore = SORT_None;

	nCount = 0;
	nItemIndex = 0;
	
	//id student, subject | full name student, avg score by subject
	for (auto i = m_mapAverageScoreBySub.begin(); i != m_mapAverageScoreBySub.end(); i++)
	{
		//id student, full name student, sub, avg score
		LoadStudentInfoFromFile((*i).first[0],  (*i).second[0], (*i).first[1], (*i).second[1]);
	}
}

/*MAP*/
// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{
	isVector = false;
	m_listReference.clear();

	orderClm0 = SORT_None;
	orderClm1 = SORT_None;
	orderClm2 = SORT_None;
	orderClm3 = SORT_None;

	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Avg score", LVCFMT_LEFT, 70);
	
	CStudent oStudent;
	map<int, vector<CString>> m_mapAverageScore;
	oStudent.AverageScoreByAllSubject(m_mapAverageScore);

	if (m_mapAverageScore.size() == 0)
		return;

	SortOrder orderIdStudent = SORT_None;
	SortOrder orderStudents = SORT_None;
	SortOrder orderSub = SORT_None;
	SortOrder orderScore = SORT_None;

	//idStud | full name student, avg score
	for (auto i = m_mapAverageScore.begin(); i != m_mapAverageScore.end(); i++)
		LoadStudentInfoFromFile(oLib.IntToCString((*i).first), (*i).second[0], (*i).second[1], "");
}

/*MAP*/
//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	isVector = false;
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
	map<vector<CString>, CString> m_mapRemedialExaminationBySubject;
	oStudent.remedialExaminationBySubject(m_mapRemedialExaminationBySubject);

	if (m_mapRemedialExaminationBySubject.size() == 0)
		return;

	SortOrder orderIdStudent = SORT_None;
	SortOrder orderStudents = SORT_None;
	SortOrder orderSub = SORT_None;
	SortOrder orderScore = SORT_None;

	//id student, subject | full name
	for (auto i = m_mapRemedialExaminationBySubject.begin(); i != m_mapRemedialExaminationBySubject.end(); i++)
		LoadStudentInfoFromFile((*i).first[0], (*i).second, (*i).first[1], "");
}

/*VECTOR*/ 
//Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	orderClm0 = SORT_None;
	isVector = true;

	m_listReference.clear();
	LoadStudentFromFile("Excellent");
}

/*VECTOR*/  
//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	isVector = true;
	orderClm0 = SORT_None;
	
	m_listReference.clear();
	LoadStudentFromFile("Birthday");
}

/*VECTOR*/ 
//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	isVector = true;
	orderClm0 = SORT_None;
	
	m_listReference.clear();
	LoadStudentFromFile("");
}

////////////////////////////////////////////////////////////////////////////

SortOrder sortOrderReference = SORT_None;

int sortClmReference = -1;   // not set

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
	oList.SortListReference(sortClmReference, m_listReference, sortOrderReference, isVector);
	
	if(isVector)
		LoadDataFromListStructVector();
	else
		LoadDataFromListStructMap();
	*pResult = 0;
}

//////////////////////////////////////////////////////////////////////////////

//print vector: excellent, birthday, correct by  more sub
void CTabReference::LoadStudentFromFile(CString nameVector) {
	
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	CStudent oStudent;
	vector<CString> m_vNameStudents;
	
	if(nameVector == "Excellent")
		oStudent.ExcellentStudent(m_vNameStudents);
	else if(nameVector == "Birthday")
		oStudent.PeopleHaveBirthdayToday(m_vNameStudents);
	else
		oStudent.remedialExaminationByMoreSubjects(m_vNameStudents);

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);

	int id = 0;
	
	for (auto i = m_vNameStudents.begin(); i != m_vNameStudents.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();
		
		ReferenceStruct refStruct;
		refStruct.strClm0 = *i;
		m_listReference.push_back(refStruct);

		nItemIndex = m_listCtrl.InsertItem(nCount, *i);
		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)id);
		id++;
	}
}

//print map-functions: Avg score by sub, avg score, correct by sub
void CTabReference::LoadStudentInfoFromFile(CString idStudent, CString nameStud, CString strClm2, CString strClm3) {
	
	//get Count list items
	nCount = m_listCtrl.GetItemCount();

	ReferenceStruct refStruct;
	refStruct.nIdStudent = atoi(idStudent);
	refStruct.strClm1 = nameStud;
	refStruct.strClm2 = strClm2;
	refStruct.strClm3 = strClm3;

	m_listReference.push_back(refStruct);

	nItemIndex = m_listCtrl.InsertItem(nCount, idStudent);

	if (nItemIndex > -1)
	{
		m_listCtrl.SetItemText(nItemIndex, 1, nameStud);
		m_listCtrl.SetItemText(nItemIndex, 2, strClm2);
		if(strClm3 != "")				   
		m_listCtrl.SetItemText(nItemIndex, 3, strClm3);

		//set index back item
		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(idStudent));
	}
}

void CTabReference::LoadDataFromListStructVector()
{
	m_listCtrl.DeleteAllItems();
	Library oLib;
	CSubject oSubject;

	nCount = 0;
	nItemIndex = 0;
	int id = 0;

	//IdRoom | subject, fn, ln
	for (list<ReferenceStruct>::iterator it = m_listReference.begin(); it != m_listReference.end(); it++) {

		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, it->strClm0);
		nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)id);
		id++;
	}
}

void CTabReference::LoadDataFromListStructMap() {
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

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)it->nIdStudent);
		}
	}
}

/*
1|	1 |Biology		|2|11/12/2020
2|	1 |Biology		|6|11/23/2020
3|	1 |Mathematics	|4|11/19/2020
4|	1 |Geography	|2|12/16/2020
5|	1 |Mathematics	|4|11/19/2020
6|	1 |Geography	|2|11/19/2020
7|	1 |Geography	|2|11/19/2020
8|	3 |Biology		|6|11/19/2020
9|	2 |Geography	|2|11/21/2020
10|	2 |Geography	|2|11/21/2020
11|	1 |Mathematics	|6|11/19/2020
12|	3 |Literature	|6|11/19/2020
13|	1 |Biology		|6|11/19/2020
14|	1 |Literature	|6|11/19/2020
15|	1 |Biology		|6|11/19/2020
16|	2 |Mathematics	|6|11/19/2020
17|	2 |Literature	|6|11/19/2020
18|	1 |Biology		|2|11/19/2020
19|	1 |Biology		|2|11/19/2020
20|	2 |Biology		|2|11/19/2020
21|	2 |Biology		|2|11/19/2020
22|	4 |Biology		|6|11/19/2020
23|	5 |Literature	|2|11/19/2020
24|	4 |Biology		|2|11/19/2020
25|	4 |Mathematics	|2|11/19/2020
26|	4 |Literature	|2|11/19/2020
27|	5 |Geography	|2|11/19/2020
28|	5 |Biology		|2|11/19/2020
29|	4 |Literature	|2|11/19/2020
30|	5 |Mathematics	|2|11/19/2020
31|	8 |Biology		|6|11/19/2020
32|	8 |Biology		|6|11/19/2020
33|	6 |Biology		|2|11/19/2020
34|	6 |Literature	|2|11/19/2020
35|	6 |Mathematics	|2|11/19/2020
36|	9 |Biology		|2|11/19/2020
37|	9 |Literature	|2|11/19/2020
38|	9 |Mathematics	|2|11/19/2020
39|	10|Biology		|2|11/19/2020
40|	10|Literature	|2|11/19/2020
41|	10|Mathematics  |2|11/19/2020
*/