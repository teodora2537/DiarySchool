// CTabReference.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CTabReference.h"
#include "CTabCRUD.h"
#include "afxdialogex.h"
#include "Library.h"
#include <string>
#include <codecvt>
#include <locale>
#include <stdlib.h>
#include <list>
#include "AddStudent.h"
#include "CUpdateStudent.h"
#include "CUpdateSubject.h"
#include "CAddScore.h"
#include "CUpdateScore.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"

using namespace std;
// CTabReference dialog
IMPLEMENT_DYNAMIC(CTabReference, CDialogEx)

CTabReference::CTabReference(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_REFERENCES, pParent)
{
	m_nItem = 0;
}

CTabReference::~CTabReference()
{
}

void CTabReference::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST, m_listCtrl);
	m_class = "";
}

BEGIN_MESSAGE_MAP(CTabReference, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_AvgScoreBySubject, &CTabReference::OnBnClickedButtonAvgscorebysubject)
	ON_BN_CLICKED(IDC_BUTTON_AvgScoreByAllSubjects, &CTabReference::OnBnClickedButtonAvgscorebyallsubjects)
	ON_BN_CLICKED(IDC_BUTTON_ExcellentStudent, &CTabReference::OnBnClickedButtonExcellentstudent)
	ON_BN_CLICKED(IDC_BUTTON_BIRTDAYS, &CTabReference::OnBnClickedButtonBirtdays)
	ON_BN_CLICKED(IDC_BUTTON_, &CTabReference::OnBnClickedButton)
	ON_BN_CLICKED(IDC_BUTTON_BY_MORE_SUBJECTS, &CTabReference::OnBnClickedButtonByMoreSubjects)
END_MESSAGE_MAP()

// CTabReference message handlers

// Print average score by subject
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	CStudent oStudent;
	//id student, subject | full name student, avg score by subject
	map<vector<CString>, vector<CString>> m_mapAverageScoreBySub;
		oStudent.AverageScoreBySubject(m_mapAverageScoreBySub);
	
	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, "Avg score", LVCFMT_LEFT, 70);

	m_iPosition = 0;
	for (auto i = m_mapAverageScoreBySub.begin(); i != m_mapAverageScoreBySub.end(); i++)
	{
			CString m_stridStudent = (*i).first[0];
			CString m_strSubject = (*i).first[1];
			CString m_strName = (*i).second[0];
			CString m_strAvgScore = (*i).second[1];

		m_listCtrl.InsertItem(m_iPosition, m_stridStudent);
		m_listCtrl.SetItemText(m_iPosition, 1, m_strName);
		m_listCtrl.SetItemText(m_iPosition, 2, m_strSubject);
		m_listCtrl.SetItemText(m_iPosition, 3, m_strAvgScore);
		
		m_iPosition++;
	}
}

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

	for (auto i = m_mapAverageScore.begin(); i != m_mapAverageScore.end(); i++)
	{
		string m_strNumber = to_string((*i).first);
		string m_strName = (*i).second[0];
		string m_strAvgScore = (*i).second[1];

		CString m_cstrNumber(m_strNumber.c_str());
		CString m_cstrName(m_strName.c_str());
		CString m_cstrAvgScore(m_strAvgScore.c_str());

		m_listCtrl.InsertItem((*i).first - 1, m_cstrNumber);
		m_listCtrl.SetItemText((*i).first - 1, 1, m_cstrName);
		m_listCtrl.SetItemText((*i).first - 1, 2, m_cstrAvgScore);
	}
}
//Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	CStudent oStudent;
	vector<CString> m_cstrAvgScore;
	oStudent.ExcellentStudent(m_cstrAvgScore);
	string m_strStudentName;
	m_iCount = 0;
	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
	
	for (auto i = m_cstrAvgScore.begin(); i != m_cstrAvgScore.end(); i++)
	{
		m_strStudentName = *i;
		CString m_cstrName(m_strStudentName.c_str());
		m_listCtrl.InsertItem(m_iCount, m_cstrName);
		m_iCount++;
	}
}
//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	CStudent oStudent;
	vector<CString> m_vecStudentBirthday;
	oStudent.PeopleHaveBirthdayToday(m_vecStudentBirthday);
	string m_strStudentName;
	m_iCount = 0;

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);

	for (auto i = m_vecStudentBirthday.begin(); i != m_vecStudentBirthday.end(); i++)
	{
		m_strStudentName = *i;
		CString cstrName(m_strStudentName.c_str());
		m_listCtrl.InsertItem(m_iCount, cstrName);
		m_iCount++;
	}
}

//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	CStudent oStudent;

	//id student, subject | full name
	map<vector<CString>, CString> m_mapRemedialExaminationBySubject;
	oStudent.remedialExaminationBySubject(m_mapRemedialExaminationBySubject);

	m_listCtrl.InsertColumn(0, "#", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, "Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, "Subject", LVCFMT_LEFT, 100);

	m_iPosition = 0;
	m_iCount = 0;
	
	for (auto i = m_mapRemedialExaminationBySubject.begin(); i != m_mapRemedialExaminationBySubject.end(); i++)
	{
			m_listCtrl.InsertItem(m_iPosition, i->first[0]);
			m_listCtrl.SetItemText(m_iPosition, 1, i->second);
			m_listCtrl.SetItemText(m_iPosition, 2, i->first[1]);

			m_iPosition++;
	}
	
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	CStudent oStudent;
	vector<CString> m_vecStudentRemedialExamination;
	oStudent.remedialExaminationByMoreSubjects(m_vecStudentRemedialExamination);

	m_listCtrl.InsertColumn(0, "Name", LVCFMT_LEFT, 100);
	int position = 0;

		for (auto j = m_vecStudentRemedialExamination.begin(); j != m_vecStudentRemedialExamination.end(); j++) {
			m_listCtrl.InsertItem(position, *j);
		}
	}