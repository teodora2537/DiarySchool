#include "pch.h"
#include "Student.h"
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Score.h"
#include "Library.h"
#include "CUpdateStudent.h"

using namespace std;

CStudentData::CStudentData(int _classNum, string _fName, string _lName, string _birthday)
{
	m_iClassNumber = _classNum;
	m_strFirstName = _fName;
	m_strLastName = _lName;
	m_strBirthday = _birthday;
}

CStudentData::CStudentData()
{
}

string CStudentData::GetFirstName() {
	return m_strFirstName;
}
void CStudentData::SetFirstName(string _firstName) {
	m_strFirstName = _firstName;
}

string CStudentData::GetLastName() {
	return m_strLastName;
}
void CStudentData::SetLastName(string _lastName) {
	m_strLastName = _lastName;
}

string CStudentData::GetBirthday() {
	return m_strBirthday;
}
void CStudentData::SetBirthday(string _birthday) {
	m_strBirthday = _birthday;
}

int CStudentData::GetClassNumber() {
	return m_iClassNumber;
}
void CStudentData::SetClassNumber(int _classNumber) {
	m_iClassNumber = _classNumber;
}

CString CStudentData::GetFullName() {
	return m_cstrFullName;
}
void CStudentData::SetFullName(CString _fullName) {
	m_cstrFullName = _fullName;
}

CStudent::CStudent()
{
}

/*virtual*/
CStudent::~CStudent()
{
}



bool CStudent::AddStudent(CStudentData& oStudent)
{
	ofstream outFile;
	outFile.open("Student.txt", ios::app);
	outFile << oStudent.GetClassNumber() << '|' << oStudent.GetFirstName() << '|' << oStudent.GetLastName() << '|' << oStudent.GetBirthday() << "\n";
	outFile.close();

	return true;
}

//	! you must use the parametter oStudent
bool CStudent::EditStudent(const CStudentData& oStudent)
{
	//Datas from edit boxes
	CStudentData student;
	int classNum = student.GetClassNumber();
	string fName = student.GetFirstName();
	string lName = student.GetLastName();
	string birthday = student.GetBirthday();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	CStudentData currentStudent;
	bool isFind = false;
	map<int, vector<string>> mapStudent;

	file.open("Student.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		// set data's student to class student
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentStudent.SetClassNumber(stoi(token));
			else if (count == 2) currentStudent.SetFirstName(token);
			else if (count == 3) currentStudent.SetLastName(token);
			else if (count == 4) { currentStudent.SetBirthday(token); break; }
			text = text.substr(position + 1, text.length());
		}
		//if student exist (from edit box) save it and continue. 
		if (currentStudent.GetClassNumber() == classNum ||
			(currentStudent.GetFirstName() == fName && currentStudent.GetLastName() == lName) ||
			currentStudent.GetBirthday() == birthday)
		{
			mapStudent[classNum].push_back(fName);
			mapStudent[classNum].push_back(lName);
			mapStudent[classNum].push_back(birthday);
			isFind = true;
			continue;
		}
		//save student from file
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetFirstName());
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetLastName());
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetBirthday());
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Student.txt", ios::out | ios::trunc);
		//Set student in the file.
		for (auto i = mapStudent.begin(); i != mapStudent.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;

}

//Empty
bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	
	return false;
}

//	! you must use the parametter nClassNumber
bool CStudent::DeleteStudent(const int nClassNumber)
{
	CStudentData student;
	int classNum = student.GetClassNumber();
	string fName = student.GetFirstName();
	string lName = student.GetLastName();
	string birthday = student.GetBirthday();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	CStudentData currentStudent;
	bool isFind = false;
	map<int, vector<string>> mapStudent;

	file.open("Student.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentStudent.SetClassNumber(stoi(token));
			else if (count == 2) currentStudent.SetFirstName(token);
			else if (count == 3) currentStudent.SetLastName(token);
			else if (count == 4) { currentStudent.SetBirthday(token); break; }
			text = text.substr(position + 1, text.length());
		}

		if (currentStudent.GetClassNumber() == classNum)
		{
			isFind = true;
			continue;
		}

		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetFirstName());
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetLastName());
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetBirthday());
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Student.txt", ios::out | ios::trunc);

		for (auto i = mapStudent.begin(); i != mapStudent.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

map<int, vector<string>> CStudent::PrintStudent()
{
	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	CStudentData currentStudent;
	map<int, vector<string>> mapStudent;

	file.open("Student.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentStudent.SetClassNumber(stoi(token));
			else if (count == 2) currentStudent.SetFirstName(token);
			else if (count == 3) currentStudent.SetLastName(token);
			else if (count == 4) { currentStudent.SetBirthday(token); break; }
			text = text.substr(position + 1, text.length());
		}

		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetFirstName());
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetLastName());
		mapStudent[currentStudent.GetClassNumber()].push_back(currentStudent.GetBirthday());
	}
	file.close();

	return mapStudent;
}

///////// All functions below use Score.PrintScore() /////////

//Average score by subject
map<int, vector<string>> CStudent::AverageScoreBySubject()
{
	
	CScore oScore;
	m_mapAllScore = oScore.PrintScore();

	//loop for, for all score 
	for (multimap<int, vector<string>>::iterator i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		m_iStudent = (*i).first;
		m_strSubject = (*i).second[1];
		//m_strScore = (*i).second[2];

		if (std::count(m_mapAverageScore[m_iStudent].begin(), m_mapAverageScore[m_iStudent].end(), m_strSubject))
			continue;

		//loop for, for all score 
		for (multimap<int, vector<string>>::iterator j = i; j != m_mapAllScore.end(); j++)
		{
			m_iCurrentStudent = (*j).first;
			m_strCurrentSubject = (*j).second[1];
			m_strCurrentScore = (*j).second[2];

			//sum all score of student by subject
			if (m_iStudent == m_iCurrentStudent && m_strSubject == m_strCurrentSubject)
			{
				m_fSum += stoi(m_strCurrentScore);
				m_iCount++;
			}
		}

		//add in student subject and average score 
		
		m_fAvg = m_fSum / m_iCount;
		m_iAverageScore = round(m_fAvg);
		m_strAverageScore = to_string(m_iAverageScore);
		m_strName = m_mapStudent[m_iStudent][0] + " " + m_mapStudent[m_iStudent][1];

		m_mapAverageScore[m_iStudent].push_back(m_strName);
		m_mapAverageScore[m_iStudent].push_back(m_strSubject);
		m_mapAverageScore[m_iStudent].push_back(m_strAverageScore);

		m_fSum = 0;
		m_iCount = 0;
	}
	return m_mapAverageScore;
}

//Average score by all subject
map<int, vector<string>> CStudent::AverageScoreByAllSubject() {
	CScore oScore;
	multimap<int, vector<string>> m_mapAllScore = oScore.PrintScore();

	//loop for, for all score 
	for (auto i = 1; i <= countStudents; i++)
	{
		//loop for, for all score 
		for (auto j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			m_iCurrentStudent = (*j).first;
			m_strCurrentScore = (*j).second[2];

			//sum all score of student by subject
			if (i == m_iCurrentStudent)
			{
				m_fSum += stoi(m_strCurrentScore);
				m_iCount++;
			}
		}

		if (m_fSum == 0)
			continue;

		//add in student subject and average score 
		m_fAvg = m_fSum / m_iCount;
		m_iAverageScore = round(m_fAvg);
		m_strName = m_mapStudent[i][0] + " " + m_mapStudent[i][1];
		m_mapAverageScore[i].push_back(m_strName);
		m_mapAverageScore[i].push_back(to_string(m_iAverageScore));

		m_fSum = 0;
		m_iCount = 0;
	}
	return m_mapAverageScore;
}

//Excellent student
vector<string> CStudent::ExcellentStudent() {

	CScore oScore;
	multimap<int, vector<string>> m_mapAllScore = oScore.PrintScore();
	//int sum = 0;
	
	//loop for all score
	for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		//if student exist -> continue
		if (m_mapStudentScore.count((*i).first))
		{
			m_fSum = m_iCount = 0;
			continue;
		}
	
		//loop for student -> sum all score of student
		for (multimap<int, vector<string>>::iterator j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			if ((*i).first == (*j).first)
			{
				m_fSum += stoi((*j).second[2]);
				m_iCount++;
			}
		}
		//add average score of student
		m_mapStudentScore[(*i).first] = m_fSum / m_iCount;
	}

	//Get name excellent students
	for (auto i = m_mapStudentScore.begin(); i != m_mapStudentScore.end(); i++)
	{
		for (auto j = m_mapStudent.begin(); j != m_mapStudent.end(); j++)
		{
			if ((*i).first == (*j).first && (*i).second >= 5.5)
			{
				m_vecStudentsName.push_back((*j).second[0] + " " + (*j).second[1]);
				break;
			}
		}
	}

	return m_vecStudentsName;
}

// CStudentData have birthday today
vector<string> CStudent::PeopleHaveBirthdayToday()
{
	Library lib;
	//get current date
	CTime time = CTime::GetCurrentTime();
	CString today = time.Format("%m%d%y");
	string s_today = lib.ConvertToStirng(today, "");
	string month = s_today.substr(0, 2);
	string day = s_today.substr(2, 2);

	//get student who have a birthday today 
	for (auto i = m_mapStudent.begin(); i != m_mapStudent.end(); i++)
	{
		if ((*i).second[2].substr(0, 5) == month + "/" + day)
		{
			m_vecStudentsName.push_back((*i).second[0] + " " + (*i).second[1]);
		}
	}
	return m_vecStudentsName;
}

map<int, vector<string>> CStudent::remedialExaminationBySubject()
{
	CScore oScore;
	multimap<int, vector<string>> m_mapAllScore = oScore.PrintScore();

	//loop for, for all score 
	for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		m_iStudent = (*i).first;
		m_strSubject = (*i).second[1];
		//m_strScore = (*i).second[2];

		if (m_mapAverageScore.count(m_iStudent) > 0) {
			vector<string> vec_subjects = m_mapAverageScore[m_iStudent];
			if (find(vec_subjects.begin(), vec_subjects.end(), m_strSubject) != vec_subjects.end()) {
				continue;
			}
		}

		//loop for, for all score 
		for (auto j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			m_iCurrentStudent = (*j).first;
			m_strCurrentSubject = (*j).second[1];
			m_strCurrentScore = (*j).second[2];

			//sum all score of student by subject
			if (m_iStudent == m_iCurrentStudent && m_strSubject == m_strCurrentSubject)
			{
				m_fSum += stoi(m_strCurrentScore);
				m_iCount++;
			}
		}

		//add in student subject and average score 
		m_fAvg = m_fSum / m_iCount;
		m_iAverageScore = round(m_fAvg);

		if (m_iAverageScore == 2) {
			m_strName = m_mapStudent[m_iStudent][0] + " " + m_mapStudent[m_iStudent][1];
			m_mapAverageScore[m_iStudent].push_back(m_strName);
			m_mapAverageScore[m_iStudent].push_back(m_strSubject);
		}

		m_fSum = 0;
		m_iCount = 0;
	}
	return m_mapAverageScore;
}

vector<string> CStudent::remedialExaminationByMoreSubjects() {

	map<int, vector<string>> studentWithPoor = remedialExaminationBySubject();

	for (auto i = studentWithPoor.begin(); i != studentWithPoor.end(); i++)
	{
		int studentNum = (*i).first;
		if ((*i).second.size() >= 3)
		{
			string m_strFN = m_mapStudent[studentNum][0];
			string m_strLN = m_mapStudent[studentNum][1];
			//set student name
			m_vecStudentsName.push_back(m_strFN);
			m_vecStudentsName.push_back(m_strLN);
		}
	}
	return m_vecStudentsName;
}
