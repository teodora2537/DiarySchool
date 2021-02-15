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
	nItem = 0;
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
	ON_BN_CLICKED(IDC_BUTTON_AllStudent, &CTabReference::OnBnClickedButtonAllstudent)
	ON_BN_CLICKED(IDC_BUTTON_AllSubject, &CTabReference::OnBnClickedButtonAllsubject)
	ON_BN_CLICKED(IDC_BUTTON_AllScore, &CTabReference::OnBnClickedButtonAllscore)

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

//Print all students
void CTabReference::OnBnClickedButtonAllstudent()
{
	ClearListCtrl();

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	int nItem=0;

	Library lib_;
	map<int, vector<string>> mapStudent = lib_.PrintStudent();
	string str;

//	string number = to_string(mapStudent.begin()->first);

	int count = 0;
	
	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Name", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Date of birthday", LVCFMT_LEFT, 100);
	
	for (auto i = mapStudent.begin(); i != mapStudent.end(); i++)
	{
		string number = to_string((*i).first);
		string name = (*i).second[0] + " " + (*i).second[1];
		string dayOfBirth = (*i).second[2];

		CString cstrNumber(number.c_str());
		CString cstrName(name.c_str());
		CString cstrDayOfBirth(dayOfBirth.c_str());

		m_listCtrl.InsertItem(count, cstrNumber);
		m_listCtrl.SetItemText(count, 1, cstrName);
		m_listCtrl.SetItemText(count, 2, cstrDayOfBirth);
		
		count++;
	}	

	m_class = "student";
}
//Print all subject
void CTabReference::OnBnClickedButtonAllsubject()
{	
	ClearListCtrl();

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	Library lib;
	map<int, vector<string>> mapSubject = lib.PrintSubject();
	string str;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Teacher", LVCFMT_LEFT, 100);

	for (auto i = mapSubject.begin(); i != mapSubject.end(); i++)
	{
		string number = to_string((*i).first);
		string subject = (*i).second[0];
		string teacher = (*i).second[1] + " " + (*i).second[2];

		CString cstrNumber(number.c_str());
		CString cstrSubject(subject.c_str());
		CString cstrTeacher(teacher.c_str());

		m_listCtrl.InsertItem((*i).first-1, cstrNumber);
		m_listCtrl.SetItemText((*i).first-1, 1, cstrSubject);
		m_listCtrl.SetItemText((*i).first-1, 2, cstrTeacher);
	}

	m_class = "subject";
}
//Print all score
void CTabReference::OnBnClickedButtonAllscore()
{
	ClearListCtrl();

	m_listCtrl.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	Library lib;
	multimap<int, vector<string>> mapScore = lib.PrintScore();
	string str;
	int row = 0;

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Date", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(3, L"Score", LVCFMT_LEFT, 50);

	for (auto i = mapScore.begin(); i != mapScore.end(); i++)
	{
		string number = to_string((*i).first);
		string subject = (*i).second[0];
		string date = (*i).second[2];
		string score = (*i).second[1];

		CString cstrNumber(number.c_str());
		CString cstrSubject(subject.c_str());
		CString cstrDate(date.c_str());
		CString cstrScore(score.c_str());

		m_listCtrl.InsertItem(row, cstrNumber);
		m_listCtrl.SetItemText(row, 1, cstrSubject);
		m_listCtrl.SetItemText(row, 2, cstrDate);
		m_listCtrl.SetItemText(row, 3, cstrScore);
		row++;
	}
	m_class = "score";
}

// Print average score by subject1
void CTabReference::OnBnClickedButtonAvgscorebysubject()
{
	ClearListCtrl();

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Subject", LVCFMT_LEFT, 100);
	m_listCtrl.InsertColumn(2, L"Avg score", LVCFMT_LEFT, 100);

	Library lib;
	map<int, vector<string>> _map = lib.AverageScoreBySubject_new();
	
	int position = 0;
	int count = 0;

	for (auto i = _map.begin(); i != _map.end(); i++)
	{
		int i_student = (*i).first;
	
		for (int j = 0; j < _map[i_student].size(); j+=2) {
			
		string student = to_string(i_student);
		string subject = _map[i_student][j];
		string avgScore = _map[i_student][j+1];

		CString cstrNumber(student.c_str());
		CString cstrSubject(subject.c_str());
		CString cstrAvgScore(avgScore.c_str());

		m_listCtrl.InsertItem(position, cstrNumber);
		m_listCtrl.SetItemText(position, 1, cstrSubject);
		m_listCtrl.SetItemText(position, 2, cstrAvgScore);
		
		position++;
		}
	}
}
// Print average score by all subject
void CTabReference::OnBnClickedButtonAvgscorebyallsubjects()
{
	ClearListCtrl();

	Library lib;
	map<int, int> _map = lib.AverageScoreByAllSubject_new();
	string str;
	
	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Avg score", LVCFMT_LEFT, 70);

	for (auto i = _map.begin(); i != _map.end(); i++)
	{
		string number = to_string((*i).first);
		string avgScore = to_string((*i).second);

		CString cstrNumber(number.c_str());
		CString cstrAvgScore(avgScore.c_str());

		m_listCtrl.InsertItem((*i).first - 1, cstrNumber);
		m_listCtrl.SetItemText((*i).first - 1, 1, cstrAvgScore);
	}
}
//Print excelent student
void CTabReference::OnBnClickedButtonExcellentstudent()
{
	ClearListCtrl();

	Library lib;
	vector<string> _student = lib.ExcellentStudent();
	string str;
	int j = 0;
	m_listCtrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);

	for (auto i = _student.begin(); i != _student.end(); i++)
	{
		string name = *i;
		CString cstrName(name.c_str());
		m_listCtrl.InsertItem(j, cstrName);
		j++;
	}
}
//Print birthdays
void CTabReference::OnBnClickedButtonBirtdays()
{
	ClearListCtrl(); 

	Library lib;
	vector<string> _student = lib.PeopleHaveBirthdayToday();
	string str;
	int j = 0;

	m_listCtrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);

	for (auto i = _student.begin(); i != _student.end(); i++)
	{
		string name = *i;
		CString cstrName(name.c_str());
		m_listCtrl.InsertItem(j, cstrName);
		j++;
	}
}

//Remedial examination by subject
void CTabReference::OnBnClickedButton()
{
	ClearListCtrl(); 
	Library lib;
	map<int, vector<string>> _map = lib.remedialExaminationBySubject();

	m_listCtrl.InsertColumn(0, L"¹", LVCFMT_LEFT, 30);
	m_listCtrl.InsertColumn(1, L"Avg score", LVCFMT_LEFT, 100);

	int position = 0;
	int count = 0;

	for (auto i = _map.begin(); i != _map.end(); i++)
	{
		int i_student = (*i).first;
		vector<string> subjects = _map[i_student];
		string student = to_string(i_student);
		CString cstrNumber(student.c_str());
		
		for (int j = 0; j < subjects.size(); j++) {	
			string subject = _map[i_student][j];
			CString cstrSubject(subject.c_str());

			m_listCtrl.InsertItem(position, cstrNumber);
			m_listCtrl.SetItemText(position, 1, cstrSubject);

			position++;
		}
	}
}
//Remedial examination by more 3 subjects
void CTabReference::OnBnClickedButtonByMoreSubjects()
{
	ClearListCtrl();
	Library lib;
	vector<string> students = lib.remedialExaminationByMoreSubjects();

	m_listCtrl.InsertColumn(0, L"Name", LVCFMT_LEFT, 100);

		for (int j = 0; j < students.size(); j+=2) {
			string name = students[j] + " " + students[j+1];
			CString cstrName(name.c_str());

			m_listCtrl.InsertItem(j, cstrName);
		}
	}

void CTabReference::ClearListCtrl()
{
	int nColumnCount = m_listCtrl.GetHeaderCtrl()->GetItemCount();
	m_listCtrl.SetRedraw(FALSE);
	m_listCtrl.DeleteAllItems();
	m_listCtrl.SetRedraw(TRUE);
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CTabReference::OnContextMenu(CWnd* pWnd, CPoint point)
{
	nItem = m_listCtrl.GetSelectionMark()+1;
	if (nItem == 0)
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
	Library lib;
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
	MessageBox(message, L"CStudentData", MB_OK);
}
void CTabReference::OnDeleteStudent()
{
	getStudentFromDlg();
	Library lib;
	CStudentData m_oStudent;
	CString message;
	message.Format(L"Do you want to delete %s with ¹ in class %d?", m_oStudent.GetFullName(), m_oStudent.GetClassNumber());

	int result = MessageBox(message, L"Delete student", MB_YESNO);
	CDialogEx::OnOK();

	//button yes clicked
	if (result == 6)
	{
		UpdateData(TRUE);
		Library lib;
		string row = "";

		CStudentData student;
		//student.SetClassNumber(_ttoi(classNum));

		lib.DeleteStudent();
	}
	//CDeleteStudent dlg;
	//dlg.DoModal();


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
	CDialogEx::OnOK();
	Subject m_oSubject;
	CString message;
	message.Format(L"Do you want to delete %s with room ¹ %d?", m_oSubject.GetNameSubject(), m_oSubject.GetRoomNumber());

	int result = MessageBox(message, L"Delete subject", MB_YESNO);

	//button yes clicked
	if (result == 6)
	{
		UpdateData(TRUE);
		Library lib;
		string row = "";

		Subject subject;
		//subject.SetRoomNumber(_ttoi(roomNum));

		lib.DeleteSubject();
	}
	//CDeleteSubject dlg;
	//dlg.DoModal();
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
	Library lib;
	Score m_oScore;
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
}
void CTabReference::OnDeleteScore()
{
	getScoreFromDlg();
	CString message;
	Score m_oScore;
	message.Format(L"Do you want to delete score with id %s?", m_oScore.GetIdScore());
	MessageBox(message, L"Delete student", MB_YESNO);

	//button yes clicked
	if (true)
	{
		UpdateData(TRUE);
		Library lib;
		string row = "";

	//	m_oScore.SetIdScore(_ttoi(idScore));

		lib.DeleteScore();
	}

	CDialogEx::OnOK();
	//CDeleteScore dlg;
	//dlg.DoModal();
}

void CTabReference::SubmenuStudent(CWnd* pWnd, CPoint point)
{
	if (nItem == 0)
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
	Subject sub(_ttoi(m_cstrId), m_cstrSubject, lib.ConvertToStirng(m_cstrFirstName, ""), lib.ConvertToStirng(m_cstrLastName, ""));
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

	Score score(_ttoi(m_cstrClassNum), lib.ConvertToStirng(m_cstrSubject, ""), _ttoi(m_cstrScore), lib.ConvertToStirng(m_cstrDate, ""));
	score.SetIdScore(id);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////