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
	CStudentData oStudentData;
	int m_iClassNum = oStudentData.GetClassNumber();
	string m_strFName = oStudentData.GetFirstName();
	string m_strLName = oStudentData.GetLastName();
	string m_strBirthday = oStudentData.GetBirthday();

	int m_iCount = 0;
	string m_strText;
	string m_strToken;
	fstream m_file;
	size_t m_sizeTPosition;
	CStudentData oCurrentStudent;
	bool m_bIsFind = false;
	map<int, vector<string>> m_mapStudent;

	m_file.open("Student.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		// set data's student to class student
		while (true)
		{
			m_sizeTPosition = m_strText.find('|');
			m_strToken = m_strText.substr(0, m_sizeTPosition);
			m_iCount++;
			if (m_iCount == 1) oCurrentStudent.SetClassNumber(stoi(m_strToken));
			else if (m_iCount == 2) oCurrentStudent.SetFirstName(m_strToken);
			else if (m_iCount == 3) oCurrentStudent.SetLastName(m_strToken);
			else if (m_iCount == 4) { oCurrentStudent.SetBirthday(m_strToken); break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}
		//if student exist (from edit box) save it and continue. 
		if (oCurrentStudent.GetClassNumber() == m_iClassNum ||
			(oCurrentStudent.GetFirstName() == m_strFName && oCurrentStudent.GetLastName() == m_strLName) ||
			oCurrentStudent.GetBirthday() == m_strBirthday)
		{
			m_mapStudent[m_iClassNum].push_back(m_strFName);
			m_mapStudent[m_iClassNum].push_back(m_strLName);
			m_mapStudent[m_iClassNum].push_back(m_strBirthday);
			m_bIsFind = true;
			continue;
		}
		//save student from file
		m_mapStudent[oCurrentStudent.GetClassNumber()].push_back(oCurrentStudent.GetFirstName());
		m_mapStudent[oCurrentStudent.GetClassNumber()].push_back(oCurrentStudent.GetLastName());
		m_mapStudent[oCurrentStudent.GetClassNumber()].push_back(oCurrentStudent.GetBirthday());
	}
	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Student.txt", ios::out | ios::trunc);
		//Set student in the file.
		for (auto i = m_mapStudent.begin(); i != m_mapStudent.end(); i++)
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
	CStudentData oStudentData;
	int m_iClassNum = oStudentData.GetClassNumber();
	string m_strFName = oStudentData.GetFirstName();
	string m_strLName = oStudentData.GetLastName();
	string m_strBirthday = oStudentData.GetBirthday();

	int m_iCount = 0;
	string m_strText;
	string m_strToken;
	fstream m_File;
	size_t m_sizeTPosition;
	CStudentData oCurrentStudent;
	bool m_bIsFind = false;
	map<int, vector<string>> m_mapStudent;

	m_File.open("Student.txt", ios::in);

	while (getline(m_File, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		while (true)
		{
			m_sizeTPosition = m_strText.find('|');
			m_strToken = m_strText.substr(0, m_sizeTPosition);
			m_iCount++;
			if (m_iCount == 1) oCurrentStudent.SetClassNumber(stoi(m_strToken));
			else if (m_iCount == 2) oCurrentStudent.SetFirstName(m_strToken);
			else if (m_iCount == 3) oCurrentStudent.SetLastName(m_strToken);
			else if (m_iCount == 4) { oCurrentStudent.SetBirthday(m_strToken); break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		if (oCurrentStudent.GetClassNumber() == m_iClassNum)
		{
			m_bIsFind = true;
			continue;
		}

		m_mapStudent[oCurrentStudent.GetClassNumber()].push_back(oCurrentStudent.GetFirstName());
		m_mapStudent[oCurrentStudent.GetClassNumber()].push_back(oCurrentStudent.GetLastName());
		m_mapStudent[oCurrentStudent.GetClassNumber()].push_back(oCurrentStudent.GetBirthday());
	}
	m_File.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Student.txt", ios::out | ios::trunc);

		for (auto i = m_mapStudent.begin(); i != m_mapStudent.end(); i++)
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
	int m_iCount = 0;
	string m_strText;
	string m_strToken;
	fstream m_file;
	size_t m_sizeTPosition;
	CStudentData oCurrentStudent;
	map<int, vector<string>> m_mapStudent;

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
	multimap<int, vector<string>> _map = oScore.PrintScore();
	map<int, vector<string>> allStudents = PrintStudent();

	float sum = 0;
	int count = 0;
	map<int, vector<string>> averageMap;
	//loop for, for all score 
	for (auto i = _map.begin(); i != _map.end(); i++)
	{
		int student = (*i).first;
		string subject = (*i).second[0];
		string score = (*i).second[1];

		if (std::count(averageMap[student].begin(), averageMap[student].end(), subject))
			continue;

		//loop for, for all score 
		for (auto j = i; j != _map.end(); j++)
		{
			int currentStudent = (*j).first;
			string currentSubject = (*j).second[0];
			string currentScore = (*j).second[1];

			//sum all score of student by subject
			if (student == currentStudent && subject == currentSubject)
			{
				sum += stoi(currentScore);
				count++;
			}
		}

		//add in student subject and average score
		string nameStudent = allStudents[student][0] + " " + allStudents[student][1];
		float avg = sum / count;
		int i_averageScore = round(avg);
		string str_averageScore = to_string(i_averageScore);
		averageMap[student].push_back(nameStudent);
		averageMap[student].push_back(subject);
		averageMap[student].push_back(str_averageScore);

		sum = 0;
		count = 0;
	}
	return averageMap;
}

//Average score by all subject
map<int, vector<string>> CStudent::AverageScoreByAllSubject() {
	CScore oScore;
	multimap<int, vector<string>> _map = oScore.PrintScore();
	map<int, vector<string>> allStudents = PrintStudent();
	/*
	float sum = 0;
	int count = 0;
	map<int, int> averageMap;
	size_t countStudents = allStudents.size();

	//loop for, for all score 
	for (auto i = 1; i <= countStudents; i++)
	{
		//loop for, for all score 
		for (auto j = _map.begin(); j != _map.end(); j++)
		{
			int currentStudent = (*j).first;
			string currentScore = (*j).second[1];

			//sum all score of student by subject
			if (i == currentStudent)
			{
				sum += stoi(currentScore);
				count++;
			}
		}

		if (sum == 0)
			continue;

		//add in student subject and average score 
		float avg = sum / count;
		int i_averageScore = round(avg);
		averageMap[i] = i_averageScore;

		sum = 0;
		count = 0;
	}
	*/

	float sum = 0;
	int count = 0;
	int currentStudent;
	//vector[0] = name;  vector[1] = score
	map<int, vector<string>> averageMap; 
	size_t countStudents = allStudents.size();

	//loop for, for all score 
	for (auto i = 1; i <= countStudents; i++)
	{
		//loop for, for all score 
		for (auto j = _map.begin(); j != _map.end(); j++)
		{
			 currentStudent = (*j).first;
			string currentScore = (*j).second[1];

			//sum all score of student by subject
			if (i == currentStudent)
			{
				sum += stoi(currentScore);
				count++;
			}
		}

		if (sum == 0)
			continue;

		//add subject and average score in student
		string nameStudent = allStudents[i][0]+" "+ allStudents[i][1];
		averageMap[i].push_back(nameStudent);
		float avg = sum / count;
		int i_averageScore = round(avg);
		averageMap[i].push_back(to_string(i_averageScore));
		
		sum = 0;
		count = 0;
	}
	return averageMap;
}

//Excellent student
vector<string> CStudent::ExcellentStudent() {

	vector<string> excelentStudents;
	CScore oScore;
	multimap<int, vector<string>> _multimap = oScore.PrintScore();
	map<int, vector<string>> mapStudent = PrintStudent();
	int sum = 0;
	int count = 0;
	string studentName;
	map<int, int> _map;

	//loop for all score
	for (auto i = _multimap.begin(); i != _multimap.end(); i++)
	{
		//if student exist -> continue
		if (_map.count((*i).first))
		{
			sum = 0;
			count = 0;
			continue;
		}
		//loop for student -> sum all score of student
		for (auto j = _multimap.begin(); j != _multimap.end(); j++)
		{
			if ((*i).first == (*j).first)
			{
				sum += stoi((*j).second[1]);
				count++;
			}
		}
		//add average score of student
		_map[(*i).first] = sum / count;
	}

	//Get name excellent students
	for (auto i = _map.begin(); i != _map.end(); i++)
	{
		for (auto j = mapStudent.begin(); j != mapStudent.end(); j++)
		{
			if ((*i).first == (*j).first && (*i).second >= 5.5)
			{
				excelentStudents.push_back((*j).second[0] + " " + (*j).second[1]);
				break;
			}
		}
	}

	return excelentStudents;
}

// CStudentData have birthday today
vector<string> CStudent::PeopleHaveBirthdayToday()
{
	Library lib;
	map<int, vector<string>> map_student = PrintStudent();
	vector<string> student;
	//get current date
	CTime time = CTime::GetCurrentTime();
	CString today = time.Format("%m%d%y");
	string s_today = lib.ConvertToStirng(today, "");
	string month = s_today.substr(0, 2);
	string day = s_today.substr(2, 2);

	//get student who have a birthday today 
	for (auto i = map_student.begin(); i != map_student.end(); i++)
	{
		if ((*i).second[2].substr(0, 5) == month + "/" + day)
		{
			student.push_back((*i).second[0] + " " + (*i).second[1]);
		}
	}
	return student;
}

map<int, vector<string>> CStudent::remedialExaminationBySubject()
{
	CScore oScore;
	multimap<int, vector<string>> _map = oScore.PrintScore();
	map<int, vector<string>> allStudents = PrintStudent();

	float sum = 0;
	int count = 0;
	map<int, vector<string>> averageMap;
	
	//loop for, for all score 
	for (auto i = _map.begin(); i != _map.end(); i++)
	{
		int student = (*i).first;
		string subject = (*i).second[0];
		string score = (*i).second[1];

		if (averageMap.count(student) > 0) {
			vector<string> vec_subjects = averageMap[student];
			if (find(vec_subjects.begin(), vec_subjects.end(), subject) != vec_subjects.end()) {
				continue;
			}
		}

		//loop for, for all score 
		for (auto j = _map.begin(); j != _map.end(); j++)
		{
			int currentStudent = (*j).first;
			string currentSubject = (*j).second[0];
			string currentScore = (*j).second[1];

			//sum all score of student by subject
			if (student == currentStudent && subject == currentSubject)
			{
				sum += stoi(currentScore);
				count++;
			}
		}

		//add in student subject and average score 
		float avg = sum / count;
		int i_averageScore = round(avg);

		if (i_averageScore == 2) {
			string nameStudent = allStudents[student][0] + " " + allStudents[student][1];
			averageMap[student].push_back(nameStudent);
			averageMap[student].push_back(subject);
		}

		sum = 0;
		count = 0;
	}
	return averageMap;
}

vector<string> CStudent::remedialExaminationByMoreSubjects() {
	CScore oScore;
	multimap<int, vector<string>> _map = oScore.PrintScore();
	map<int, vector<string>> student = PrintStudent();
	vector<string> students;

	map<int, vector<string>> studentWithPoor = remedialExaminationBySubject();

	for (auto i = studentWithPoor.begin(); i != studentWithPoor.end(); i++)
	{
		int studentNum = (*i).first;
		if ((*i).second.size() >= 3)
		{
			string fn = student[studentNum][0];
			string ln = student[studentNum][1];
			//set student name
			students.push_back(fn);
			students.push_back(ln);
		}
	}
	return students;
}
