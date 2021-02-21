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
#include "CAddSubject.h"
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
	
	//////////////////////////////////////
	ON_WM_CONTEXTMENU()

	ON_BN_CLICKED(IDC_MENU_ADD_STUDENT, OnAddStudent)
	ON_BN_CLICKED(IDC_MENU_EDIT_STUDENT, OnEditStudent)
	ON_BN_CLICKED(IDC_MENU_DEL_STUDENT, OnDeleteStudent)
	ON_BN_CLICKED(IDC_MENU_VIEW_STUDENT, OnViewStudent)

	ON_BN_CLICKED(IDC_MENU_ADD_SUBJECT, OnAddSubject)
	ON_BN_CLICKED(IDC_MENU_EDIT_SUBJECT, OnEditSubject)
	ON_BN_CLICKED(IDC_MENU_DEL_SUBJECT, OnDeleteSubject)
	ON_BN_CLICKED(IDC_MENU_VIEW_SUBJECT, OnViewSubject)

	ON_BN_CLICKED(IDC_MENU_ADD_SCORE, OnAddScore)
	ON_BN_CLICKED(IDC_MENU_EDIT_SCORE, OnEditScore)
	ON_BN_CLICKED(IDC_MENU_DEL_SCORE, OnDeleteScore)
	ON_BN_CLICKED(IDC_MENU_VIEW_SCORE, OnViewScore)
	///////////////////////////////////////
END_MESSAGE_MAP()

// CTabReference message handlers

// Print average score by subject1
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	CStudent oStudent;
	map<int, vector<string>> m_mapAverageScoreBySub = oStudent.AverageScoreBySubject();
	
	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Avg score", LVCFMT_LEFT, 70);

	m_iPosition = 0;
	for (auto i = m_mapAverageScoreBySub.begin(); i != m_mapAverageScoreBySub.end(); i++)
	{
		 m_iStudent = (*i).first;
	
		for (int j = 0; j < m_mapAverageScoreBySub[m_iStudent].size(); j+=3) {
			
		string m_strStudent = to_string(m_iStudent);
		string m_strName = m_mapAverageScoreBySub[m_iStudent][j];
		string m_strSubject = m_mapAverageScoreBySub[m_iStudent][j+1];
		string m_strAvgScore = m_mapAverageScoreBySub[m_iStudent][j+2];

		CString m_cstrNumber(m_strStudent.c_str());
		CString m_cstrName(m_strName.c_str());
		CString m_cstrSubject(m_strSubject.c_str());
		CString m_cstrAvgScore(m_strAvgScore.c_str());

		m_listCtrl.InsertItem(m_iPosition, m_cstrNumber);
		m_listCtrl.SetItemText(m_iPosition, 1, m_cstrName);
		m_listCtrl.SetItemText(m_iPosition, 2, m_cstrSubject);
		m_listCtrl.SetItemText(m_iPosition, 3, m_cstrAvgScore);
		
		m_iPosition++;
		}
	}
}
// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);

	CStudent oStudent;
	map<int, vector<string>> m_mapAverageScore = oStudent.AverageScoreByAllSubject();
	
	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Avg score", LVCFMT_LEFT, 70);

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
	vector<string> m_cstrAvgScore = oStudent.ExcellentStudent();
	string m_strStudentName;
	m_iCount = 0;
	m_listCtrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);
	
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
	vector<string> m_vecStudentBirthday = oStudent.PeopleHaveBirthdayToday();
	string m_strStudentName;
	m_iCount = 0;

	m_listCtrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);

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
	map<int, vector<string>> m_mapRemedialExaminationBySubject = oStudent.remedialExaminationBySubject();

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Subject", LVCFMT_LEFT, 100);

	m_iPosition = 0;
	m_iCount = 0;

	for (auto i = m_mapRemedialExaminationBySubject.begin(); i != m_mapRemedialExaminationBySubject.end(); i++)
	{
		m_iStudent = (*i).first;
		
		vector<string> m_vecSubjects = m_mapRemedialExaminationBySubject[m_iStudent];
		
		string m_strIdStudent = to_string(m_iStudent);
		CString cstrNumber(m_strIdStudent.c_str());
		
		for (int j = 0; j < m_vecSubjects.size(); j+=2) {
			
			string m_strStudentName = m_mapRemedialExaminationBySubject[m_iStudent][j];
			string m_strSubject = m_mapRemedialExaminationBySubject[m_iStudent][j+1];
			
			CString m_cstrName(m_strStudentName.c_str());
			CString m_cstrSubject(m_strSubject.c_str());
			
			m_listCtrl.InsertItem(m_iPosition, cstrNumber);
			m_listCtrl.SetItemText(m_iPosition, 1, m_cstrName);
			m_listCtrl.SetItemText(m_iPosition, 2, m_cstrSubject);

			m_iPosition++;
		}
	}
}

//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	Library oLib;
	oLib.ClearListCtrl(m_listCtrl);
	
	CStudent oStudent;
	vector<string> m_vecStudentRemedialExamination = oStudent.remedialExaminationByMoreSubjects();

	m_listCtrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);

		for (int j = 0; j < m_vecStudentRemedialExamination.size(); j+=2) {
			CString cstrName((m_vecStudentRemedialExamination[j] + " " + m_vecStudentRemedialExamination[j+1]).c_str());
			m_listCtrl.InsertItem(j, cstrName);
		}
	}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTabReference::OnContextMenu(CWnd* pWnd, CPoint point)
{
	m_nItem = m_listCtrl.GetSelectionMark()+1;
	if (m_nItem == 0)
		return;

		if (m_class == "student")
			SubmenuStudent(pWnd, point);
		else if (m_class == "subject")
			SubmenuSubject(pWnd, point);
		else if (m_class == "score")
			SubmenuScore(pWnd, point);
}

void CTabReference::OnAddStudent()
{
	CStudentData oStudentData;

	CAddStudentDlg dlg(oStudentData, eDialogMode_View);

	if (dlg.DoModal() != IDOK)
		return;

	CStudent oStudent;

	oStudent.AddStudent(oStudentData);
}
void CTabReference::OnEditStudent()
{
	getStudentFromDlg();
	CUpdateStudentDlg dlg;
	dlg.DoModal();
}
void CTabReference::OnViewStudent()
{
	/*Library lib;
	CStudentData m_oStudent;
	multimap<int, vector<string>> infoScores = lib.PrintScore();
	map<string, vector<int>> m_mapScoresStudent;
	string m_strMessageSubAndScore = "¹: %d\nName: %s\n";
	getStudentFromDlg();
	
	//Get Score only for student
	for (auto i = infoScores.begin(); i != infoScores.end(); i++)
	{
		if (i->first == m_oStudent.GetClassNumber()) {
			m_mapScoresStudent[i->second[0]].push_back(stoi(i->second[1]));
		}
	}

	for (auto i = m_mapScoresStudent.begin(); i != m_mapScoresStudent.end(); i++)
	{
		int sizeVectorScore = i->second.size();
		string subject = i->first;
		m_strMessageSubAndScore += subject + ": ";
		for (auto j = 0; j < sizeVectorScore; j++)
		{
			int score = i->second[j];
			m_strMessageSubAndScore +=to_string(score);
			
			if (j < sizeVectorScore - 1)
				m_strMessageSubAndScore += ", ";
		}
		m_strMessageSubAndScore += "\n";
	}

	CString m_cstrMessageSubAndScore(m_strMessageSubAndScore.c_str());
	CString message;
	message.Format(m_cstrMessageSubAndScore, m_oStudent.GetClassNumber(), m_oStudent.GetFullName());
	MessageBox(message, L"CStudentData", MB_OK);*/
	getStudentFromDlg();
	CUpdateStudentDlg dlg;
	dlg.DoModal();
}
void CTabReference::OnDeleteStudent()
{
	getStudentFromDlg();
	//Library lib;
	CStudentData oStudentData;
	CString message;
	message.Format(L"Do you want to delete %s with ¹ in class %d?", oStudentData.GetFullName() , oStudentData.GetClassNumber());

	int result = MessageBox(message, L"Delete student", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;

		UpdateData(TRUE);

		CStudent oStudent;
		oStudent.DeleteStudent(oStudentData.GetClassNumber());
		DeleteItem();
}

void CTabReference::OnAddSubject()
{
	CAddSubjectDlg dlg;
	dlg.DoModal();
}
void CTabReference::OnEditSubject()
{
	getSubjectFromDlg();
	CUpdateSubjectDlg dlg;
	dlg.DoModal();
}
void CTabReference::OnViewSubject()
{

	MessageBox(L"You clicked VIEW");
}
void CTabReference::OnDeleteSubject()
{
	getSubjectFromDlg();
	//CDialogEx::OnOK();
	CSubjectData oSubjectData;
	CString message;
	message.Format(L"Do you want to delete %s with room ¹ %d?", oSubjectData.GetNameSubject(), oSubjectData.GetRoomNumber());
	int result = MessageBox(message, L"Delete subject", MB_YESNO);

	//button yes clicked
	if (result != IDYES)
		return;
		UpdateData(TRUE);
		/*
		Library lib;
		lib.DeleteSubject();
		*/
		CSubject oSubject;
		oSubject.DeleteSubject(oSubjectData.GetRoomNumber());
		DeleteItem();
}

void CTabReference::OnAddScore()
{
	CAddScoreDlg dlg;
	dlg.DoModal();
}
void CTabReference::OnEditScore()
{
	getScoreFromDlg();
	CUpdateScoreDlg dlg;
	dlg.DoModal();
	
	}
void CTabReference::OnViewScore()
{
	/*
	Library lib;
	CScoreData m_oScore;
	multimap<int, vector<string>> infoScores = lib.PrintScore();
	vector<int> m_vecScoresStudent;
	getScoreFromDlg();
	CString sub(m_oScore.GetSubject().c_str());
	string m_strMessageSubAndScore = "¹: %d\nSubject: %s\nScores: ";
	//Get Score only for student
	for (auto i = infoScores.begin(); i != infoScores.end(); i++)
	{
		if (i->first == m_oScore.GetClassNum())
		{

		if(i->second[0] == m_oScore.GetSubject()) {
			m_vecScoresStudent.push_back(stoi(i->second[1]));
		
		}
		}
	}

	for (auto i = 0; i != m_vecScoresStudent.size(); i++)
	{
			int score = m_vecScoresStudent[i];
			m_strMessageSubAndScore += to_string(score);

			if (i < m_vecScoresStudent.size() - 1)
				m_strMessageSubAndScore += ", ";
	}

	CString m_cstrMessageSubAndScore(m_strMessageSubAndScore.c_str());
	CString message;
	message.Format(m_cstrMessageSubAndScore, m_oScore.GetClassNum(), sub);
	MessageBox(message, L"", MB_OK);
	*/
}
void CTabReference::OnDeleteScore()
{
	getScoreFromDlg();
	CScoreData oScoreData;
	
	CString message;
	message.Format(L"Do you want to delete score with id %d?", oScoreData.GetIdScore());
	int result = MessageBox(message, L"Delete score", MB_YESNO);

	if (result != IDYES)
		return;

	//button yes clicked
		UpdateData(TRUE);
		/*
		Library lib;
		lib.DeleteScore();
		*/
		CScore oScore;
		oScore.DeleteScore(oScoreData.GetIdScore());
		DeleteItem();
}

void CTabReference::SubmenuStudent(CWnd* pWnd, CPoint point)
{
	if (m_nItem == 0)
		return;

	CMenu submenu;
	submenu.CreatePopupMenu();
	 
	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_STUDENT, L"Add student");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_STUDENT, L"Edit student");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_STUDENT, L"Delete student");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_STUDENT, L"View student");

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

}
void CTabReference::SubmenuSubject(CWnd* pWnd, CPoint point)
{
	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SUBJECT, L"Add subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SUBJECT, L"Edit subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SUBJECT, L"Delete subject");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SUBJECT, L"View subject");

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

}
void CTabReference::SubmenuScore(CWnd* pWnd, CPoint point)
{
	CMenu submenu;
	submenu.CreatePopupMenu();

	submenu.AppendMenu(MF_STRING, IDC_MENU_ADD_SCORE, L"Add score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_EDIT_SCORE, L"Edit score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_DEL_SCORE, L"Delete score");
	submenu.AppendMenu(MF_STRING, IDC_MENU_VIEW_SCORE, L"View score");

	submenu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

}

void CTabReference::getStudentFromDlg()
{
	m_cstrId = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	m_cstrName = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	m_cstrBirthday = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);
	m_cstrFirstName = L"";
	m_cstrLastName = L"";
	int nTokenPos = 0;
	int count = 0;
	Library lib;
	CString strToken = m_cstrName.Tokenize(_T(" "), nTokenPos);

	while (!strToken.IsEmpty())
	{
		if (count == 0)
		{
			m_cstrFirstName = strToken;
			count++;
		}
		else if (count == 1)
		{
			m_cstrLastName = strToken;
		}
		strToken = m_cstrName.Tokenize(_T(" "), nTokenPos);
	}

	CStudentData m_oStudent(_ttoi(m_cstrId), lib.ConvertToStirng(m_cstrFirstName, ""), lib.ConvertToStirng(m_cstrLastName, ""), lib.ConvertToStirng(m_cstrBirthday, ""));
	m_oStudent.SetFullName(m_cstrName);
}
void CTabReference::getSubjectFromDlg()
{
	 m_cstrId = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	 m_cstrSubject = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	 m_cstrTeacher = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);

	m_cstrFirstName = L"";
	m_cstrLastName = L"";
	int nTokenPos = 0;
	int count = 0;
	Library lib;
	CString strToken = m_cstrTeacher.Tokenize(_T(" "), nTokenPos);

	while (!strToken.IsEmpty())
	{
		if (count == 0)
		{
			m_cstrFirstName = strToken;
			count++;
		}
		else if (count == 1)
		{
			m_cstrLastName = strToken;
		}
		strToken = m_cstrTeacher.Tokenize(_T(" "), nTokenPos);
	}
	CSubjectData sub(_ttoi(m_cstrId), m_cstrSubject, lib.ConvertToStirng(m_cstrFirstName, ""), lib.ConvertToStirng(m_cstrLastName, ""));
	sub.SetFullNameTeacher(m_cstrTeacher);
}
void CTabReference::getScoreFromDlg()
{
	Library lib;

	CString m_cstrClassNum = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 0);
	CString m_cstrSubject = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 1);
	CString m_cstrDate = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 2);
	CString m_cstrScore = m_listCtrl.GetItemText(m_listCtrl.GetSelectionMark(), 3);

	int id = m_listCtrl.GetSelectionMark()+1;

	CScoreData score(_ttoi(m_cstrClassNum), lib.ConvertToStirng(m_cstrSubject, ""), _ttoi(m_cstrScore), lib.ConvertToStirng(m_cstrDate, ""));
	score.SetIdScore(id);
}

void CTabReference::DeleteItem() {
		for (int nItem = 0; nItem < m_listCtrl.GetItemCount(); )
		{
			if (m_listCtrl.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
				m_listCtrl.DeleteItem(nItem);
			else
				++nItem;
		}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
