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

CStudentData::CStudentData(int _classNum, CString _fName, CString _lName, CString _birthday)
{
	m_iClassNumber = _classNum;
	m_strFirstName = _fName;
	m_strLastName = _lName;
	m_strBirthday = _birthday;
}

CStudentData::CStudentData()
{
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
	outFile << oStudent.m_iClassNumber << DEF_FILE_DATA_SEPARATOR << oStudent.m_strFirstName << DEF_FILE_DATA_SEPARATOR << oStudent.m_strLastName << DEF_FILE_DATA_SEPARATOR << oStudent.m_strBirthday << "\n";
	outFile.close();

	return true;
}

bool CStudent::EditStudent(const CStudentData& oStudent)
{
	//Datas from edit boxes
	Library oLib;
	int classNum = oStudent.m_iClassNumber;
	CString fName = oStudent.m_strFirstName;
	CString lName = oStudent.m_strLastName;
	CString birthday = oStudent.m_strBirthday;

	int count = 0;
	string text;
	CString token;
	fstream file;
	size_t position;
	CStudentData currentStudent;
	bool isFind = false;
	map<int, vector<CString>> mapStudent;

	file.open("Student.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		// set data's student to class student
		while (true)
		{
			position = text.find(DEF_FILE_DATA_SEPARATOR);
			token =  (text.substr(0, position)).c_str();
			count++;
			if (count == 1) currentStudent.m_iClassNumber = atoi(token);
			else if (count == 2) currentStudent.m_strFirstName = token;
			else if (count == 3) currentStudent.m_strLastName = token;
			else if (count == 4) { currentStudent.m_strBirthday = token; break; }
			text = text.substr(position + 1, text.length());
		}
		//if student exist (from edit box) save it and continue. 
		if (currentStudent.m_iClassNumber == classNum ||
			(currentStudent.m_strFirstName == fName && currentStudent.m_strLastName == lName) ||
			currentStudent.m_strBirthday == birthday)
		{
			mapStudent[classNum].push_back(fName);
			mapStudent[classNum].push_back(lName);
			mapStudent[classNum].push_back(birthday);
			isFind = true;
			continue;
		}
		//save student from file
		mapStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strFirstName);
		mapStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strLastName);
		mapStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strBirthday);
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Student.txt", ios::out | ios::trunc);
		//Set student in the file.
		for (auto i = mapStudent.begin(); i != mapStudent.end(); i++)
		{
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR << (*i).second[0] << DEF_FILE_DATA_SEPARATOR << (*i).second[1] << DEF_FILE_DATA_SEPARATOR << (*i).second[2] << "\n";
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

bool CStudent::DeleteStudent(const int nClassNumber)
{
	CStudentData student;
	//int classNum = student.m_iClassNumber;
	CString fName = student.m_strFirstName;
	CString lName = student.m_strLastName;
	CString birthday = student.m_strBirthday;

	int count = 0;
	string text;
	CString token;
	fstream file;
	size_t position;
	bool isFind = false;
	map<int, vector<CString>> mapStudent;
	CStudentData currentStudent;

	file.open("Student.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find(DEF_FILE_DATA_SEPARATOR);
			token = (text.substr(0, position)).c_str();
			count++;
			if (count == 1) currentStudent.m_iClassNumber = atoi(token);
			else if (count == 2) currentStudent.m_strFirstName = token;
			else if (count == 3) currentStudent.m_strLastName = token;
			else if (count == 4) { currentStudent.m_strBirthday = token; break; }
			text = text.substr(position + 1, text.length());
		}

		if (currentStudent.m_iClassNumber == nClassNumber)
		{
			isFind = true;
			continue;
		}

		mapStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strFirstName);
		mapStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strLastName);
		mapStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strBirthday);
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Student.txt", ios::out | ios::trunc);

		for (auto i = mapStudent.begin(); i != mapStudent.end(); i++)
		{
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR << (*i).second[0] << DEF_FILE_DATA_SEPARATOR << (*i).second[1] << DEF_FILE_DATA_SEPARATOR << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

void CStudent::PrintStudent(map<int, vector<CString>>& m_mapAllStudent)
{
	int count = 0;
	string text;
	CString token;
	fstream file;
	size_t position;
	CStudentData currentStudent;
	//map<int, vector<CString>> mapStudent;

	file.open("Student.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find(DEF_FILE_DATA_SEPARATOR);
			token = (text.substr(0, position)).c_str();
			count++;
			if (count == 1) currentStudent.m_iClassNumber = atoi(token);
			else if (count == 2) currentStudent.m_strFirstName = token;
			else if (count == 3) currentStudent.m_strLastName = token;
			else if (count == 4) { currentStudent.m_strBirthday = token; break; }
			text = text.substr(position + 1, text.length());
		}

		m_mapAllStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strFirstName);
		m_mapAllStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strLastName);
		m_mapAllStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strBirthday);
	}
	file.close();

	//return mapSAlltudents;
}

///////// All functions below use Score.PrintScore() /////////

//Average score by subject
 void CStudent::AverageScoreBySubject(map<int, vector<CString>>& m_mapAverageScoreBySub)
{
	multimap<int, vector<CString>> m_mapAllScore;
	CScore oScore;
	oScore.PrintScore(m_mapAllScore);
	int m_iStudent;
	CString m_strSubject;
	int m_iCurrentStudent;
	CString m_strCurrentSubject;
	CString m_strCurrentScore;
	float m_fSum = 0;
	int m_iCount = 0;
	float m_fAvg;
	int m_iAverageScore;
	CString m_strName;

	//loop for, for all score 
	for (multimap<int, vector<CString>>::iterator i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		m_iStudent = (*i).first;
		m_strSubject = (*i).second[1];
		map<int, vector<CString>> m_mapStudent;
		PrintStudent(m_mapStudent);

		if (std::count(m_mapAverageScoreBySub[m_iStudent].begin(), m_mapAverageScoreBySub[m_iStudent].end(), m_strSubject))
			continue;

		//loop for, for all score 
		for (multimap<int, vector<CString>>::iterator j = i; j != m_mapAllScore.end(); j++)
		{
			m_iCurrentStudent = (*j).first;
			m_strCurrentSubject = (*j).second[1];
			m_strCurrentScore = (*j).second[2];

			//sum all score of student by subject
			if (m_iStudent == m_iCurrentStudent && m_strSubject == m_strCurrentSubject)
			{
				m_fSum += atoi(m_strCurrentScore);
				m_iCount++;
			}
		}

		//add in student subject and average score 
		m_fAvg = m_fSum / m_iCount;
		m_iAverageScore = round(m_fAvg);
		CString m_strAverageScore;
		m_strAverageScore.Format("%d",m_iAverageScore);
		m_strAverageScore = m_strAverageScore;
		m_strName = m_mapStudent[m_iStudent][0] + " " + m_mapStudent[m_iStudent][1];

		m_mapAverageScoreBySub[m_iStudent].push_back(m_strName);
		m_mapAverageScoreBySub[m_iStudent].push_back(m_strSubject);
		m_mapAverageScoreBySub[m_iStudent].push_back(m_strAverageScore);

		m_fSum = 0;
		m_iCount = 0;
	}
	;
}

//Average score by all subject
 void CStudent::AverageScoreByAllSubject(map<int, vector<CString>>& m_mapAverageScore) {
	 multimap<int, vector<CString>> m_mapAllScore;
	 map<int, vector<CString>> m_mapStudent;  
	 PrintStudent(m_mapStudent);
	 
	 float m_fSum = 0;
	 float m_fAvg;
	 
	 int m_iCount = 0;
	 int m_iCurrentStudent;
	 int m_iAverageScore;
	 
	 CString m_strCurrentScore;
	 CString m_strName;
	 
	 size_t countStudents = m_mapStudent.size();

	CScore oScore; 
	oScore.PrintScore(m_mapAllScore);

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
				m_fSum += atoi(m_strCurrentScore);
				m_iCount++;
			}
		}

		if (m_fSum == 0)
			continue;

		//add in student subject and average score 
		m_fAvg = m_fSum / m_iCount;
		m_iAverageScore = round(m_fAvg);
		CString m_strAverageScore;
		m_strAverageScore.Format("%d", m_iAverageScore);
		m_strName = m_mapStudent[i][0] + " " + m_mapStudent[i][1];
		m_mapAverageScore[i].push_back(m_strName);
		m_mapAverageScore[i].push_back(m_strAverageScore);

		m_fSum = 0;
		m_iCount = 0;
	}
}

//Excellent student
 void CStudent::ExcellentStudent(vector<CString>& m_vecStudentsName) {
	 map<int, int> m_mapStudentScore;
	 map<int, vector<CString>> m_mapStudent;
	 PrintStudent(m_mapStudent);
	 
	 float m_fSum = 0;
	 
	 int m_iCount = 0;

	 multimap<int, vector<CString>> m_mapAllScore;
	 CScore oScore;
	 oScore.PrintScore(m_mapAllScore);
	
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
		for (multimap<int, vector<CString>>::iterator j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			if ((*i).first == (*j).first)
			{
				m_fSum += atoi((*j).second[2]);
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
}

// CStudentData have birthday today
void CStudent::PeopleHaveBirthdayToday(vector<CString>& m_vecStudentsName)
{
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	Library lib;
	//get current date
	CTime time = CTime::GetCurrentTime();
	CString today = time.Format("%m%d%y");
	string s_today = lib.ConvertToString(today, "");
	string month = s_today.substr(0, 2);
	string day = s_today.substr(2, 2);

	//get student who have a birthday today 
	for (auto i = m_mapStudent.begin(); i != m_mapStudent.end(); i++)
	{	
		//m_strMD -> month/day
		string m_strMD = (*i).second[2];
		if (m_strMD.substr(0, 5) == month + "/" + day)
		{
			m_vecStudentsName.push_back((*i).second[0] + " " + (*i).second[1]);
		}
	}
}

void CStudent::remedialExaminationBySubject(map<int, vector<CString>>& m_mapAverageScore)
{
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);
	float m_fSum = 0;
	float m_fAvg;
	int m_iCount = 0;
	int m_iStudent;
	int m_iCurrentStudent;
	int m_iAverageScore;
	CString m_strSubject;
	CString m_strCurrentSubject;
	CString m_strCurrentScore;
	CString m_strName;

	CScore oScore;
	multimap<int, vector<CString>> m_mapAllScore;
	oScore.PrintScore(m_mapAllScore);

	//loop for, for all score 
	for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		m_iStudent = (*i).first;
		m_strSubject = (*i).second[1];

		if (m_mapAverageScore.count(m_iStudent) > 0) {
			vector<CString> vec_subjects = m_mapAverageScore[m_iStudent];
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
				m_fSum += atoi(m_strCurrentScore);
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
}

void CStudent::remedialExaminationByMoreSubjects(vector<CString>& m_vecStudentsName) {

	map<int, vector<CString>> m_mapStudent;
		PrintStudent(m_mapStudent);

	map<int, vector<CString>> studentWithPoor;
		remedialExaminationBySubject(studentWithPoor);

	for (auto i = studentWithPoor.begin(); i != studentWithPoor.end(); i++)
	{
		int studentNum = (*i).first;
		if ((*i).second.size() >= 3)
		{
			CString m_strFN = m_mapStudent[studentNum][0];
			CString m_strLN = m_mapStudent[studentNum][1];
			//set student name
			m_vecStudentsName.push_back(m_strFN);
			m_vecStudentsName.push_back(m_strLN);
		}
	}
}
