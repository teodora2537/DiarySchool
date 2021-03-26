/*
// CTabReference.cpp : implementation file
//
//#include "CTabCRUD.h"
//#include <codecvt>
//#include <locale>
//#include <stdlib.h>
//#include "AddStudent.h"
//#include "CAddScore.h"
//#include <string>
*/

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
// CTabReference dialog
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

/*MAP*/
// Print average score by subject
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	CStudent oStudent;
	
	map<vector<CString>, vector<CString>> m_mapAverageScoreBySub;
	oStudent.AverageScoreBySubject(m_mapAverageScoreBySub);

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, "Avg score", LVCFMT_LEFT, 70);
	
	int nCount = 0;
	int nItemIndex = 0;
	
	//id student, subject | full name student, avg score by subject
	for (auto i = m_mapAverageScoreBySub.begin(); i != m_mapAverageScoreBySub.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, (*i).first[0]);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).second[0]);
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).first[1]);
			m_listCtrl.SetItemText(nItemIndex, 3, (*i).second[1]);
			
			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(i->first[0]));
		}
	}
}
/*
void CTabReference::LoadDataFromFile()
{
	CScore oScore;
	m_listCtrl.DeleteAllItems();
	map<int, vector<CString>> mapScore;
	oScore.PrintScore(mapScore);
	Library oLib;
	int nCount = 0;
	int nItemIndex = 0;

	//idScore | idStudent, nameStudent, subject, Score, date
	for (auto it = mapScore.begin(); it != mapScore.end(); it++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		ScoreStruct scoreStruct = { it->first, it->second[0], it->second[1], it->second[2], it->second[3], it->second[4] };
		m_listScore.push_back(scoreStruct);

		nItemIndex = m_listCtrl.InsertItem(nCount, scoreStruct.strIdStudent);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, scoreStruct.strNameStudent);
			m_listCtrl.SetItemText(nItemIndex, 2, scoreStruct.strSubject);
			m_listCtrl.SetItemText(nItemIndex, 3, scoreStruct.strScore);
			m_listCtrl.SetItemText(nItemIndex, 4, scoreStruct.strDate);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)scoreStruct.nIdScore);
		}
	}
}
*/

/*MAP*/
// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	CStudent oStudent;
	map<int, vector<CString>> m_mapAverageScore;
	oStudent.AverageScoreByAllSubject(m_mapAverageScore);
	

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Avg score", LVCFMT_LEFT, 70);
	int nCount{ 0 };
	int nItemIndex{ 0 };

	for (auto i = m_mapAverageScore.begin(); i != m_mapAverageScore.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();
		
		nItemIndex = m_listCtrl.InsertItem(nCount, oLib.IntToCString((*i).first));
	
		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).second[0]);
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).second[1]);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)i->first);
		}
	}
}

/*MAP*/
//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);

	CStudent oStudent;
	map<vector<CString>, CString> m_mapRemedialExaminationBySubject;
	oStudent.remedialExaminationBySubject(m_mapRemedialExaminationBySubject);
	
	int nCount{ 0 };
	int nItemIndex{ 0 };

	//id student, subject | full name
	for (auto i = m_mapRemedialExaminationBySubject.begin(); i != m_mapRemedialExaminationBySubject.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, (*i).first[0]);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).second);
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).first[1]);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(i->first[0]));
		}
	}
}

void CTabReference::LoadStudentInfoFromFile(CString nameMap) {
	
	//in func
	CStudent oStudent;
	map<vector<CString>, CString> m_mapRemedialExaminationBySub;
		oStudent.remedialExaminationBySubject(m_mapRemedialExaminationBySub);
	map<int, vector<CString>> m_mapAverageScore;
		oStudent.AverageScoreByAllSubject(m_mapAverageScore);
	map<vector<CString>, vector<CString>> m_mapAverageScoreBySub;
		oStudent.AverageScoreBySubject(m_mapAverageScoreBySub);

	
	int nCount{ 0 };
	int nItemIndex{ 0 };

	//id student, subject | full name
	for (auto i = m_mapRemedialExaminationBySub.begin(); i != m_mapRemedialExaminationBySub.end(); i++)
	{
		//get Count list items
		nCount = m_listCtrl.GetItemCount();

		nItemIndex = m_listCtrl.InsertItem(nCount, (*i).first[0]);

		if (nItemIndex > -1)
		{
			m_listCtrl.SetItemText(nItemIndex, 2, (*i).second);
			m_listCtrl.SetItemText(nItemIndex, 1, (*i).first[1]);

			//set index back item
			nItemIndex = m_listCtrl.SetItemData(nCount, (DWORD_PTR)atoi(i->first[0]));
		}
	}
}

//
void testFunc(auto it) {


}

/*VECTOR*/ //Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	LoadStudentFromFile("Excellent");
}

/*VECTOR*/  //Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	LoadStudentFromFile("Birthday");
}

/*VECTOR*/ //Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	LoadStudentFromFile("");
}

////////////////////////////////////////////////////////////////////////////
list<ReferenceStruct> m_listReference;

SortOrder orderIdStudent = SORT_None;
SortOrder orderStudents = SORT_None;
SortOrder orderSub = SORT_None;
SortOrder orderScore = SORT_None;

SortOrder sortOrderReference = SORT_None;

void CTabReference::OnLvnColumnclickList(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);

	*pResult = 0;
}

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
	
	if (m_vNameStudents.size() == 0)
		return;

	int nPosition{0};

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);

	for (auto i = m_vNameStudents.begin(); i != m_vNameStudents.end(); i++)
	{
		m_listCtrl.InsertItem(nPosition, *i);
		nPosition++;
	}
}
//////////////////////////////////////////////////////////////////////////////