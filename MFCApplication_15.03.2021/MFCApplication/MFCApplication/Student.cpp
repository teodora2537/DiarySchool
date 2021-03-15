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

/*
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
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[0] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[1] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;

}
*/

bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	map<int, vector<CString>> m_mapStudents;
	PrintStudent(m_mapStudents);
	oStudent.m_iClassNumber = nClassNumber;
	oStudent.m_strFirstName =  m_mapStudents[nClassNumber][0];
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

/*
bool CStudent::DeleteStudent(const int nClassNumber)
{
	CStudentData student;
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
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[0] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[1] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}
*/

void CStudent::PrintStudent(map<int, vector<CString>>& m_mapAllStudent)
{
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
	//id student | fn, ln, birthday
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	//id student, subject | scores
	map<vector<CString>, vector<int>> mapAllScoreBySub;
	AverageScore(mapAllScoreBySub);

	for (map<vector<CString>, vector<int>>::iterator i = mapAllScoreBySub.begin(); i != mapAllScoreBySub.end(); i++)
	{
		CString fullNameStudent = m_mapStudent[atoi((*i).first[0])][0] + " " + m_mapStudent[atoi((*i).first[0])][1];
		CString m_strAvgScore;
		m_strAvgScore.Format("%d", (i->second[0]));

		m_mapAverageScoreBySub.insert(pair<vector<CString>, vector<CString>>(i->first, vector<CString>{fullNameStudent, m_strAvgScore}));
	}
}

//Average score by subject
/*
 void CStudent::AverageScoreBySubject(map<int, vector<CString>>& m_mapAverageScoreBySub)
 {
	 map<vector<CString>, vector<int>> mapAllScoreBySub;
	 AverageScore(mapAllScoreBySub);

	map<int, vector<CString>> m_mapAllScore;
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
	for (map<int, vector<CString>>::iterator i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		//m_iStudent = (*i).first;
		m_iStudent = atoi((*i).second[0]);
		m_strSubject = (*i).second[2];
		map<int, vector<CString>> m_mapStudent;
		PrintStudent(m_mapStudent);

		if (std::count(m_mapAverageScoreBySub[m_iStudent].begin(), m_mapAverageScoreBySub[m_iStudent].end(), m_strSubject))
			continue;

		//loop for, for all score 
		for (multimap<int, vector<CString>>::iterator j = i; j != m_mapAllScore.end(); j++)
		{
			//m_iCurrentStudent = (*j).first;
			m_iCurrentStudent = atoi((*j).second[0]);
			m_strCurrentSubject = (*j).second[2];
			m_strCurrentScore = (*j).second[3];

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
}
*/

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
	/// 
	float m_fAvg;
	int m_iAverageScore;
	CString m_strAvgScore;
	/// 

	for (map<vector<CString>, vector<int>>::iterator i = mapAllScoreBySub.begin(); i != mapAllScoreBySub.end(); i++)
	{
		CString m_strAvgScore;
		m_strAvgScore.Format("%d", (i->second[0]));
		if (atoi(i->first[0]) == idStudent)
		{
			sum += i->second[0];
			count++;
		}
			if(atoi(i->first[0]) != idStudent || (i->first == mapAllScoreBySub.rbegin()->first && i->second == mapAllScoreBySub.rbegin()->second)){
			CString fullNameStudent = m_mapStudent[idStudent][0] + " " + m_mapStudent[idStudent][1];
			m_fAvg = sum * 1.0 / count;
			m_iAverageScore = round(m_fAvg);
			m_strAvgScore.Format("%d", m_iAverageScore);
			//insert datas
			m_mapAverageScore.insert(pair<int, vector<CString>>(idStudent, vector<CString>{fullNameStudent, m_strAvgScore}));
			//last student
			idStudent++;
			count = 0;
			sum = 0;
			//sum score of last student
			sum += i->second[0];
			count++;
		}
	}
}
/*
 void CStudent::AverageScoreByAllSubject(map<int, vector<CString>>& m_mapAverageScore) {	 
	 map<int, vector<CString>> m_mapAllScore;
	 map<int, vector<CString>> m_mapStudent;  
	 PrintStudent(m_mapStudent);
	 size_t countStudents = m_mapStudent.size();
	 
	 float m_fSum = 0;
	 float m_fAvg;
	 
	 int m_iCount = 0;
	 int m_iCurrentStudent;
	 int m_iAverageScore;
	 
	 CString m_strCurrentScore;
	 CString m_strName;

	CScore oScore; 
	oScore.PrintScore(m_mapAllScore);

	//loop for, for all score 
	for (auto i = 1; i <= countStudents; i++)
	{
		//loop for, for all score 
		for (auto j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			//m_iCurrentStudent = (*j).first;
			m_iCurrentStudent = atoi((*j).second[0]);
			m_strCurrentScore = (*j).second[3];

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
*/

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

	 /*
	 map<int, int> m_mapStudentScore;
	 map<int, vector<CString>> m_mapStudent;
	 PrintStudent(m_mapStudent);
	 
	 float m_fSum = 0;
	 
	 int m_iCount = 0;

	 map<int, vector<CString>> m_mapAllScore;
	 CScore oScore;
	 oScore.PrintScore(m_mapAllScore);
	
	//loop for all score
	for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		//if student exist -> continue
		if (m_mapStudentScore.count(atoi((*i).second[0])))
		{
			m_fSum = m_iCount = 0;
			continue;
		}

	
		if (std::find(m_mapAllScore[(*i).first].begin(), m_mapAllScore[(*i).first].end(), 20) != m_mapAllScore[(*i).first].end()) {
		
		}

		//loop for student -> sum all score of student
		for (multimap<int, vector<CString>>::iterator j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			if ((*i).second[0] == (*j).second[0])
			{
				m_fSum += atoi((*j).second[3]);
				m_iCount++;
			}
		}
		//add average score of student
		m_mapStudentScore[atoi((*i).second[0])] = m_fSum / m_iCount;
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
	 */
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

		if(date.GetDay() == oleDate.GetDay() && date.GetMonth() == oleDate.GetMonth())
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

	/*
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
	map<int, vector<CString>> m_mapAllScore;
	oScore.PrintScore(m_mapAllScore);

	//loop for, for all score 
	for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
	{
		m_iStudent = atoi((*i).second[0]);
		m_strSubject = (*i).second[2];

		//if student and subject exist -> continue
		if (m_mapAverageScore.count(m_iStudent) > 0) {
			vector<CString> vec_subjects = m_mapAverageScore[m_iStudent];
			if (find(vec_subjects.begin(), vec_subjects.end(), m_strSubject) != vec_subjects.end()) {
				continue;
			}
		}

		//loop for, for all score 
		for (auto j = m_mapAllScore.begin(); j != m_mapAllScore.end(); j++)
		{
			m_iCurrentStudent = atoi((*j).second[0]);
			m_strCurrentSubject = (*j).second[2];
			m_strCurrentScore = (*j).second[3];

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
	*/
}

void CStudent::remedialExaminationByMoreSubjects(vector<CString>& m_vecStudentsName) {

	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);
	//id student, subject | full name
	map<vector<CString>, CString> studentWithPoor;
	remedialExaminationBySubject(studentWithPoor);
	int count = 0;
	int idStudent = 1;

	for (map<vector<CString>, CString>::iterator i = studentWithPoor.begin(); i != studentWithPoor.end(); i++)
	{
		if (atoi(i->first[0]) == idStudent)
			count++;

		if (atoi(i->first[0]) != idStudent || (i->first == studentWithPoor.rbegin()->first && i->second == studentWithPoor.rbegin()->second))
		{
			if(count >= 3)
			m_vecStudentsName.push_back(i->second); //full name student
			idStudent++;
			count = 0;
		}
	}

	/*
	map<int, vector<CString>> m_mapStudent;
		PrintStudent(m_mapStudent);
		//id student, subject | full name
		map<vector<CString>, CString> studentWithPoor;
		remedialExaminationBySubject(studentWithPoor);

	for (auto i = studentWithPoor.begin(); i != studentWithPoor.end(); i++)
	{

		int studentNum = (*i).first;
		//((*i).second.size())/2 -> /2 because inside i have name and score
		if (((*i).second.size())/2 >= 3)
		{
			CString m_strFN = m_mapStudent[studentNum][0];
			CString m_strLN = m_mapStudent[studentNum][1];
			//set student name
			m_vecStudentsName.push_back(m_strFN);
			m_vecStudentsName.push_back(m_strLN);
		}
	}
	*/
}

int CStudent::CountStudent()
{
	map<int, vector<CString>> m_mapStudent;
	PrintStudent(m_mapStudent);

	return m_mapStudent.size();
}

//Average score: //id student, subject | average scores(int)
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
			vector<CString> m_vKey = vector<CString> {m_strIdStudent, m_strSubject};
			vector<int> m_vValue= vector<int>{m_iScore};
			
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
		//m_strAvgScore.Format("%d", m_iAverageScore);
		m_vecScore.clear();
		m_vecScore.push_back(m_iAverageScore);
		mapAllScoreBySub[i->first] = m_vecScore;
	}
}

/*
1  | 1 | Geography     | 2 | 11 / 21 / 2020
2  | 1 | Biology       | 6 | 11 / 23 / 2020
3  | 1 | Mathematics   | 4 | 11 / 19 / 2020
4  | 1 | Geography	   | 2 | 11 / 21 / 2020
5  | 1 | Mathematics   | 4 | 11 / 19 / 2020
6  | 1 | Geography	   | 2 | 11 / 19 / 2020
7  | 1 | Geography	   | 2 | 11 / 19 / 2020
8  | 3 | Biology	   | 6 | 11 / 19 / 2020
9  | 2 | Geography	   | 2 | 11 / 21 / 2020
10 | 2 | Geography	   | 2 | 11 / 21 / 2020
11 | 1 | Mathematics   | 6 | 11 / 19 / 2020
12 | 3 | Literature	   | 6 | 11 / 19 / 2020
13 | 1 | Biology	   | 6 | 11 / 19 / 2020
14 | 1 | Literature	   | 6 | 11 / 19 / 2020
15 | 1 | Biology	   | 6 | 11 / 19 / 2020
16 | 2 | Mathematics   | 6 | 11 / 19 / 2020
17 | 2 | Literature	   | 6 | 11 / 19 / 2020
18 | 1 | Biology	   | 2 | 11 / 19 / 2020
19 | 1 | Biology	   | 2 | 11 / 19 / 2020
20 | 2 | Biology	   | 2 | 11 / 19 / 2020
21 | 2 | Biology	   | 2 | 11 / 19 / 2020
22 | 4 | Biology	   | 6 | 11 / 19 / 2020
23 | 5 | Literature	   | 2 | 11 / 19 / 2020
24 | 4 | Biology	   | 2 | 11 / 19 / 2020
25 | 4 | Mathematics   | 2 | 11 / 19 / 2020
26 | 4 | Literature    | 2 | 11 / 19 / 2020
27 | 5 | Geography     | 2 | 11 / 19 / 2020
28 | 5 | Biology       | 2 | 11 / 19 / 2020
29 | 4 | Literature    | 2 | 11 / 19 / 2020
30 | 5 | Mathematics   | 2 | 11 / 19 / 2020
31 | 1 | Literature    | 5 | 12 / 12 / 2020
*/