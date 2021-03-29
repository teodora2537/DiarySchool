#include "pch.h"
#include "Student.h"
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include "Score.h"
#include "Library.h"
#include "CUpdateStudent.h"
#include <list>
#include <numeric> //accumulate

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
	outFile << oStudent.m_iClassNumber << DEF_FILE_DATA_SEPARATOR
		<< oStudent.m_strFirstName << DEF_FILE_DATA_SEPARATOR
		<< oStudent.m_strLastName << DEF_FILE_DATA_SEPARATOR
		<< oStudent.m_strBirthday << "\n";
	outFile.close();

	return true;
}

bool CStudent::EditStudent(const CStudentData& oStudent) {
	fstream m_file;
	string m_strText;
	string m_strFileInfo;
	Library oLib;
	int m_sizeTPosition = 0;
	CString	m_strToken;
	m_file.open("Student.txt", ios::in);
	while (getline(m_file, m_strText)) {

		m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
		m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
		//if id score is find => save changes else save line from file
		if (oStudent.m_iClassNumber == atoi(m_strToken))
		{
			m_strFileInfo += to_string(oStudent.m_iClassNumber) + DEF_FILE_DATA_SEPARATOR +
				oLib.ConvertToString(oStudent.m_strFirstName, "") + DEF_FILE_DATA_SEPARATOR +
				oLib.ConvertToString(oStudent.m_strLastName, "") + DEF_FILE_DATA_SEPARATOR +
				oLib.ConvertToString(oStudent.m_strBirthday, "") + "\n";
		}
		else {
			m_strFileInfo += m_strText + "\n";
		}
	}
	m_file.close();

	//save string in file
	ofstream outFile;
	outFile.open("Student.txt", ios::out | ios::trunc);
	//Set score in the file.
	outFile << m_strFileInfo;
	outFile.close();

	return true;
}

bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	map<int, vector<CString>> m_mapStudents;
	PrintStudent(m_mapStudents);
	oStudent.m_iClassNumber = nClassNumber;
	oStudent.m_strFirstName = m_mapStudents[nClassNumber][0];
	oStudent.m_strLastName = m_mapStudents[nClassNumber][1];
	oStudent.m_strBirthday = m_mapStudents[nClassNumber][2];

	return true;
}

bool CStudent::DeleteStudent(const int nClassNumber) {
	fstream m_file;
	string m_strText;
	string m_strFileInfo;
	Library oLib;
	int m_sizeTPosition = 0;
	CString	m_strToken;

	m_file.open("Student.txt", ios::in);

	while (getline(m_file, m_strText)) {
		m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
		m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
		//if id score is find => save changes else save line from file
		if (nClassNumber == atoi(m_strToken))
			continue;
		else
			m_strFileInfo += m_strText + "\n";
	}
	m_file.close();

	//save string in file
	ofstream outFile;
	outFile.open("Student.txt", ios::out | ios::trunc);
	//Set score in the file.
	outFile << m_strFileInfo;
	outFile.close();
	return true;
}

void CStudent::PrintStudent(map<int, vector<CString>>& m_mapAllStudent)
{
	//validation file: is exist or empty
	ifstream is;
	is.open("Student.txt", ios::binary);
	is.seekg(0, ios::end);
	if (is.tellg() <= 0)
		return;

	int count = 0;
	string text;
	CString token;
	fstream file;
	size_t position;
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

		m_mapAllStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strFirstName);
		m_mapAllStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strLastName);
		m_mapAllStudent[currentStudent.m_iClassNumber].push_back(currentStudent.m_strBirthday);
	}
	file.close();
}

//Average score by subject -> id student, subject | full name student, avg score by subject
void CStudent::AverageScoreBySubject(map<vector<CString>, vector<CString>>& m_mapAverageScoreBySub)
{
	Library oLib;
	//id student | fn, ln, birthday
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	
	map<vector<CString>, vector<int>> mapAllScoreBySub;
	AverageScore(mapAllScoreBySub);
	
	//id student, subject | scores
	for (map<vector<CString>, vector<int>>::iterator i = mapAllScoreBySub.begin(); i != mapAllScoreBySub.end(); i++)
	{
		CString fullNameStudent = m_mapStudent[atoi((*i).first[0])][0] + " " + m_mapStudent[atoi((*i).first[0])][1];
		CString m_strAvgScore;
		m_strAvgScore = oLib.IntToCString(i->second[0]);

		m_mapAverageScoreBySub.insert(pair<vector<CString>, vector<CString>>(i->first, vector<CString>{ fullNameStudent, m_strAvgScore }));
	}
}

//Average score by all subject
//id student| full name student, avg score
void CStudent::AverageScoreByAllSubject(map<int, vector<CString>>& m_mapAverageScore) {
	//id student | fn, ln, birthday
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	//id student, subject | scores
	map<vector<CString>, vector<int>> mapAllScoreBySub;
	AverageScore(mapAllScoreBySub);
	int idStudent = 1;
	int count = 0;
	int sum = 0;
	
	float m_fAvg;
	int m_iAverageScore;
	CString m_strAvgScore;
	Library oLib;

	int nCurrentIdStudent;
	int nPreviousIdStudent;

	bool isFirstElement = true;

	for (map<vector<CString>, vector<int>>::iterator i = mapAllScoreBySub.begin(); i != mapAllScoreBySub.end(); i++)
	{
		if (isFirstElement)
		{
			nCurrentIdStudent = nPreviousIdStudent = atoi(i->first[0]);
			isFirstElement = false;
		}
		else nCurrentIdStudent = atoi(i->first[0]);

		m_strAvgScore = oLib.IntToCString((i->second[0]));
		
		if (nCurrentIdStudent == nPreviousIdStudent){
			sum += i->second[0];
			count++;
		}else{
			CString fullNameStudent = m_mapStudent[nPreviousIdStudent][0] + " " + m_mapStudent[nPreviousIdStudent][1];
			m_fAvg = sum * 1.0 / count;
			m_iAverageScore = round(m_fAvg);
			m_strAvgScore = oLib.IntToCString(m_iAverageScore);
			//insert datas
			m_mapAverageScore.insert(pair<int, vector<CString>>(nPreviousIdStudent, vector<CString>{fullNameStudent, m_strAvgScore}));
			count = 0;
			sum = 0;
			//sum score of last student
			sum += i->second[0];
			count++;
		}	
		
		if (nCurrentIdStudent != nPreviousIdStudent && i->first == mapAllScoreBySub.rbegin()->first && i->second == mapAllScoreBySub.rbegin()->second)
				m_mapAverageScore.insert(pair<int, vector<CString>>(nCurrentIdStudent, vector<CString>{m_mapStudent[nCurrentIdStudent][0] + " " + m_mapStudent[nCurrentIdStudent][1], oLib.IntToCString(i->second[0])}));
		else if (nCurrentIdStudent == nPreviousIdStudent && i->first == mapAllScoreBySub.rbegin()->first && i->second == mapAllScoreBySub.rbegin()->second)
		{
			m_fAvg = sum * 1.0 / count;
			m_iAverageScore = round(m_fAvg);
			m_strAvgScore = oLib.IntToCString(m_iAverageScore);

			m_mapAverageScore.insert(pair<int, vector<CString>>(nCurrentIdStudent, vector<CString>{m_mapStudent[nCurrentIdStudent][0] + " " + m_mapStudent[nCurrentIdStudent][1], m_strAvgScore}));
		}

		nPreviousIdStudent = atoi(i->first[0]);
	}
}

//Excellent student
void CStudent::ExcellentStudent(vector<CString>& m_vecStudentsName) {
	//id student | full name, average score
	map<int, vector<CString>> m_mapAverageScore;
	AverageScoreByAllSubject(m_mapAverageScore);

	for (map<int, vector<CString>>::iterator i = m_mapAverageScore.begin(); i != m_mapAverageScore.end(); i++)
	{
		if (i->second[1] == "6")
			m_vecStudentsName.push_back(i->second[0]);
	}
}

// CStudentData have birthday today
void CStudent::PeopleHaveBirthdayToday(vector<CString>& m_vecStudentsName)
{
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	COleDateTime date;
	COleDateTime oleDate = COleDateTime::GetCurrentTime();

	//get student who have a birthday today 
	for (auto i = m_mapStudent.begin(); i != m_mapStudent.end(); i++)
	{
		date.ParseDateTime((*i).second[2], 0, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));

		if (date.GetDay() == oleDate.GetDay() && date.GetMonth() == oleDate.GetMonth())
			m_vecStudentsName.push_back((*i).second[0] + " " + (*i).second[1]);
	}
}

//id student, subject | full name
void CStudent::remedialExaminationBySubject(map<vector<CString>, CString>& mapAverageScore)
{
	//id student, subject | full name student, avg score by subject
	map<vector<CString>, vector<CString>> m_mapAverageScore;
	AverageScoreBySubject(m_mapAverageScore);

	for (map<vector<CString>, vector<CString>>::iterator i = m_mapAverageScore.begin(); i != m_mapAverageScore.end(); i++)
	{
		if (i->second[1] == "2")
		{
			mapAverageScore.insert(pair<vector<CString>, CString>(vector<CString>{i->first[0], i->first[1]}, i->second[0]));
		}
	}
}

void CStudent::remedialExaminationByMoreSubjects(vector<CString>& m_vecStudentsName) {

	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);
	
	map<vector<CString>, CString> studentWithPoor;
	remedialExaminationBySubject(studentWithPoor);
	int count = 0;

	int nCurrentIdStudent;
	int nPreviousIdStudent;
	bool isFirstItem = true;
	CString strCurrentName;
	CString strPreviousName;

	//id student, subject | full name
	for (map<vector<CString>, CString>::iterator i = studentWithPoor.begin(); i != studentWithPoor.end(); i++)
	{
		if (isFirstItem)
		{
			nCurrentIdStudent = nPreviousIdStudent = atoi(i->first[0]);
			strCurrentName = i->second;
			isFirstItem = false;
		}

		nCurrentIdStudent = atoi(i->first[0]);

		if (nPreviousIdStudent == nCurrentIdStudent)
			count++;

		if (nPreviousIdStudent != nCurrentIdStudent || (i->first == studentWithPoor.rbegin()->first && i->second == studentWithPoor.rbegin()->second))
		{
			if (count >= 3)
				m_vecStudentsName.push_back(strPreviousName); //full name student
			count = 1;
		}
		nPreviousIdStudent = atoi(i->first[0]);
		strPreviousName = i->second;
	}
}

int CStudent::CountStudent()
{
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	return m_mapStudent.size();
}

//Average score: 
//id student, subject | average scores(int)
void CStudent::AverageScore(map<vector<CString>, vector<int>>& mapAllScoreBySub) {
	//map: idScore; [0]= # class, [1] = full name, [2] = subject, [3] = score, [4] = date
	map<int, vector<CString>> m_mapAllScore;
	CScore oScore;
	oScore.PrintScore(m_mapAllScore);

	//id stud, subject | Score

	CString m_strIdStudent;
	CString m_strSubject;

	int m_iScore;

	for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		m_strIdStudent = (*i).second[0];
		m_strSubject = i->second[2];
		m_iScore = atoi(i->second[3]);


		if (mapAllScoreBySub.find({ m_strIdStudent, m_strSubject }) != mapAllScoreBySub.end()) {
			//is found
			mapAllScoreBySub[{ m_strIdStudent, m_strSubject }].push_back(m_iScore);
		}
		else {
			//is not found
			vector<CString> m_vKey = vector<CString>{ m_strIdStudent, m_strSubject };
			vector<int> m_vValue = vector<int>{ m_iScore };

			mapAllScoreBySub.insert(pair<vector<CString>, vector<int>>(m_vKey, m_vValue));
		}
	}

	float m_fAvg;
	int m_iAverageScore;
	CString m_strAvgScore;

	//id student, subject | scores
	for (map<vector<CString>, vector<int>>::iterator i = mapAllScoreBySub.begin(); i != mapAllScoreBySub.end(); i++)
	{
		vector<int> m_vecScore = i->second;
		int sum = accumulate(m_vecScore.begin(), m_vecScore.end(), 0);

		m_fAvg = sum * 1.0 / m_vecScore.capacity();
		m_iAverageScore = round(m_fAvg);
		m_vecScore.clear();
		m_vecScore.push_back(m_iAverageScore);
		mapAllScoreBySub[i->first] = m_vecScore;
	}
}