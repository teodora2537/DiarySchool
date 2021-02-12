#include "pch.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include<math.h>
using namespace std;

Library::Library(void) {}
Library::~Library(void) {}

//Convert CString to string
string Library::ConvertToStirng(CString str_cstr, string row) 
{
	CString s_cstring = str_cstr;
	CT2CA ct(s_cstring);
	row = ct;
	return row;
}

//Add student/subject/score to file
bool Library::AddInStudent()
{
	Student student;
	ofstream outFile;
	outFile.open("Student.txt",ios::app);
	outFile << student.GetClassNumber() <<'|'<< student.GetFirstName()<<'|'<<student.GetLastName()<< '|' <<student.GetBirthday()<< "\n";
	outFile.close();

	return true;
}
bool Library::AddInSubject()
{
	Subject subject;
	ofstream outFile;
	outFile.open("Subject.txt", ios::app);
	outFile <<subject.GetRoomNumber()<<'|' <<subject.GetNameSubject() << '|' << subject.GetFirstNameTeacher()<< '|' << subject.GetLastNameTeacher() << "\n";
	outFile.close();

	return true;
}
bool Library::AddInScore()
{
	Score score;
	int length=0;

	fstream outFile, inputfile;
	outFile.open("Score.txt", ios::app);
	
	int classNum = score.GetClassNum();
	int i_score = score.GetScore();
	string subject = score.GetSubject();
	string date = score.GetDate();

	multimap<int, vector<string>> mapScores = PrintScore();
	int idScore = mapScores.size()+1;

	outFile << idScore << '|' << classNum << '|' << subject << '|' << i_score<< '|' << date<< "\n";
	outFile.close();

	return true;
}

//Update student/subject/score
bool Library::UpdateStudent()
{
	//Datas from edit boxes
	Student student;
	int classNum = student.GetClassNumber();
	string fName = student.GetFirstName();
	string lName = student.GetLastName();
	string birthday = student.GetBirthday();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Student currentStudent;
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
			text = text.substr(position+1, text.length());
		}
		//if student exist (from edit box) save it and continue. 
		if (currentStudent.GetClassNumber() == classNum  || 
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
			outFile << (*i).first <<'|'<< (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;

}
bool Library::UpdateSubject()
{
	//Datas from edit boxes
	Subject subject;
	int roomNum = subject.GetRoomNumber();
	string fName = subject.GetFirstNameTeacher();
	string lName = subject.GetLastNameTeacher();
	string _subject = ConvertToStirng(subject.GetNameSubject(),"");


	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Subject currentSubject;
	bool isFind = false;
	map<int, vector<string>> mapSubject;


	file.open("Subject.txt", ios::in);
	while (getline(file, text))
	{
		position = 0;
		count = 0;
	// set data's subject to class subject
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1)currentSubject.SetRoomNumber(stoi(token));
			if (count == 2)
			{
				CString cstr(token.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (count == 3) currentSubject.SetFirstNameTeacher(token);
			else if (count == 4) {currentSubject.SetLastNameTeacher(token); break; }
			text = text.substr(position + 1, text.length());
		}
		//if subject exist (from edit box) save it and continue. 
		if (currentSubject.GetRoomNumber() == roomNum ||
			(currentSubject.GetFirstNameTeacher() == fName && currentSubject.GetLastNameTeacher() == lName) ||
			ConvertToStirng(currentSubject.GetNameSubject(),"") == _subject)
		{
			mapSubject[roomNum].push_back(_subject);
			mapSubject[roomNum].push_back(fName);
			mapSubject[roomNum].push_back(lName);
			isFind = true;
			continue;
		}
		//save subject from file
		mapSubject[currentSubject.GetRoomNumber()].push_back(ConvertToStirng(currentSubject.GetNameSubject(), ""));
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);
		//Set subject in the file.
		for (auto i = mapSubject.begin(); i != mapSubject.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}
bool Library::UpdateScore()
{
	//Datas from edit boxes
	Score score;
	int idScore = score.GetIdScore();
	int classNum = score.GetClassNum();
	string subject = score.GetSubject();
	int _score = score.GetScore();
	string date = score.GetDate();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Score currentScore;
	bool isFind = false;
	multimap<int, vector<string>> mapScore;
	vector<string> _vector;

	file.open("Score.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		// set data's score to class score
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1)
			{
				currentScore.SetIdScore(stoi(token));
				idScore = currentScore.GetIdScore();
			}
			if (count == 2) currentScore.SetClassNum(stoi(token));
			else if (count == 3) currentScore.SetSubject(token);
			else if (count == 4)  currentScore.SetScore(stoi(token));
			else if (count == 5) { currentScore.SetDate(token); break; }
			text = text.substr(position + 1, text.length());
		}

		//if exist (from edit box) save it and continue. 
		if (currentScore.GetClassNum() == classNum &&
			currentScore.GetSubject() == subject && currentScore.GetDate() == date)
		{
			_vector.push_back(to_string(classNum));
			_vector.push_back(subject);
			_vector.push_back(to_string(_score));
			_vector.push_back(date);
			mapScore.insert(pair<int, vector<string>>(idScore, _vector));
			_vector.clear();
			isFind = true;
			continue;
		}
		//save score from file
		_vector.push_back(to_string(currentScore.GetClassNum()));
		_vector.push_back(currentScore.GetSubject());
		_vector.push_back(to_string(currentScore.GetScore()));
		_vector.push_back(currentScore.GetDate());
			mapScore.insert(pair<int, vector<string>>(idScore, _vector));
		_vector.clear();
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Score.txt", ios::out | ios::trunc);
		//Set score in the file.
		for (auto i = mapScore.begin(); i != mapScore.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << '|' << (*i).second[3] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;

}
//Delete student/subject/score -> delete by exist number
bool Library::DeleteStudent()
{
	Student student;
	int classNum = student.GetClassNumber();
	string fName = student.GetFirstName();
	string lName = student.GetLastName();
	string birthday = student.GetBirthday();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Student currentStudent;
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
bool Library::DeleteSubject()
{
	Subject subject;
	int roomNum = subject.GetRoomNumber();
	string _subject = ConvertToStirng(subject.GetNameSubject(), "");
	string fName = subject.GetFirstNameTeacher();
	string lName = subject.GetLastNameTeacher();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Subject currentSubject;
	bool isFind = false;
	map<int, vector<string>> mapSubject;

	file.open("Subject.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentSubject.SetRoomNumber(stoi(token));
			else if (count == 2)
			{
				CString cstr(token.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (count == 3) currentSubject.SetFirstNameTeacher(token);
			else if (count == 4) { currentSubject.SetLastNameTeacher(token); break; }
			text = text.substr(position + 1, text.length());
		}

		if (currentSubject.GetRoomNumber() == roomNum)
		{
			isFind = true;
			continue;
		}

		mapSubject[currentSubject.GetRoomNumber()].push_back(ConvertToStirng(currentSubject.GetNameSubject(), ""));
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);

		for (auto i = mapSubject.begin(); i != mapSubject.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;

}
bool Library::DeleteScore()
{
	Score score;
	int idScore = score.GetIdScore();
	int classNum = score.GetClassNum();
	string subject = score.GetSubject();
	string date = score.GetDate();
	int _score = score.GetScore();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Score currentScore;
	bool isFind = false;
	multimap<int, vector<string>> mapScore;
	vector<string> _vector;

	file.open("Score.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;

		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentScore.SetIdScore(stoi(token));
			else if (count == 2) currentScore.SetClassNum(stoi(token));
			else if (count == 3) currentScore.SetSubject(token);
			else if (count == 4) currentScore.SetScore(stoi(token));
			else if (count == 5) { currentScore.SetDate(token); break; }
			text = text.substr(position + 1, text.length());
		}

		if (currentScore.GetIdScore() == idScore)
		{
			isFind = true;
			continue;
		}

		_vector.push_back(to_string(currentScore.GetClassNum()));
		_vector.push_back(currentScore.GetSubject());
		_vector.push_back(to_string(currentScore.GetScore()));
		_vector.push_back(currentScore.GetDate());
		mapScore.insert(pair<int, vector<string>>(currentScore.GetIdScore(), _vector));
		_vector.clear();
	}

	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Score.txt", ios::out | ios::trunc);

		for (auto i = mapScore.begin(); i != mapScore.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << '|' << (*i).second[3] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

//Report

//Print functions
map<int, vector<string>> Library::PrintStudent()
{
	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Student currentStudent;
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
map<int, vector<string>> Library::PrintSubject() {
		int count = 0;
		string text;
		string token;
		fstream file;
		size_t position;
		Subject currentSubject;
		bool isFind = false;
		map<int, vector<string>> mapSubject;

		file.open("Subject.txt", ios::in);

		while (getline(file, text))
		{
			position = 0;
			count = 0;
			while (true)
			{
				position = text.find('|');
				token = text.substr(0, position);
				count++;
				if (count == 1) currentSubject.SetRoomNumber(stoi(token));
				else if (count == 2) { 
					CString cstr(token.c_str());
					currentSubject.SetNameSubject(cstr);
				}
				else if (count == 3) currentSubject.SetFirstNameTeacher(token);
				else if (count == 4) {currentSubject.SetLastNameTeacher(token);break; }
				text = text.substr(position + 1, text.length());
			}

			mapSubject[currentSubject.GetRoomNumber()].push_back(ConvertToStirng(currentSubject.GetNameSubject(), ""));
			mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
			mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
		}
		file.close();

	return mapSubject;
}
multimap<int, vector<string>> Library::PrintScore()
{
	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	Score currentScore;
	bool isFind = false;
	multimap<int, vector<string>> mapScore;
	vector<string> _vector;

	file.open("Score.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) 
				currentScore.SetIdScore(stoi(token));
			else if (count == 2)
				currentScore.SetClassNum(stoi(token));
			else if (count == 3) 
				currentScore.SetSubject(token);
			else if (count == 4)
				currentScore.SetScore(stoi(token));
			else if (count == 5) 
			{ 
				currentScore.SetDate(token);
				break;
			}
			text = text.substr(position + 1, text.length());
		}
		_vector.push_back(currentScore.GetSubject());
		_vector.push_back(to_string(currentScore.GetScore()));
		_vector.push_back(currentScore.GetDate());
		mapScore.insert(pair<int, vector<string>>(currentScore.GetClassNum(), _vector));
		_vector.clear();
	}
	file.close();
	return mapScore;
}

//Average score

//Average score by subject
map<int, vector<string>> Library::AverageScoreBySubject_new()
{
	multimap<int, vector<string>> _map = PrintScore();

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
		float avg = sum / count;
		int i_averageScore = round(avg);
		string str_averageScore = to_string(i_averageScore);
		averageMap[student].push_back(subject);
		averageMap[student].push_back(str_averageScore);

		sum = 0;
		count = 0;
	}
	return averageMap;
}

//Average score by all subject
map<int, int> Library::AverageScoreByAllSubject_new() {
	
	multimap<int, vector<string>> _map = PrintScore();
	map<int, vector<string>> allStudents = PrintStudent();
	float sum = 0;
	int count = 0;
	map<int, int> averageMap;
	int countStudents = allStudents.size();

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
	return averageMap;
}

//Excellent student
vector<string> Library::ExcellentStudent() {
	
	vector<string> excelentStudents;
	multimap<int, vector<string>> _multimap = PrintScore();
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
				excelentStudents.push_back((*j).second[0]+" "+ (*j).second[1]);
				break;
			}
		}
	}
	
	return excelentStudents;
}

// Student have birthday today
vector<string> Library::PeopleHaveBirthdayToday()
{
	map<int, vector<string>> map_student = PrintStudent();
	vector<string> student;
	//get current date
		CTime time = CTime::GetCurrentTime();
		CString today = time.Format("%m%d%y");
		string s_today = ConvertToStirng(today,"");
		string month = s_today.substr(0, 2);
		string day = s_today.substr(2, 2);

		//get student who have a birthday today 
	for (auto i = map_student.begin(); i != map_student.end(); i++)
	{
		if ((*i).second[2].substr(0, 5) == month + "/" + day)
		{
			student.push_back((*i).second[0]+" "+ (*i).second[1]);
		}
	}
	return student;
}

map<int, vector<string>> Library::remedialExaminationBySubject()
{
	multimap<int, vector<string>> _map = PrintScore();

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
			averageMap[student].push_back(subject);
		}
		
		sum = 0;
		count = 0;
	}
	return averageMap;
}

vector<string> Library::remedialExaminationByMoreSubjects() {
	multimap<int, vector<string>> _map = PrintScore();
	map<int, vector<string>> student = PrintStudent();
	vector<string> students;

	map<int, vector<string>> studentWithPoor= remedialExaminationBySubject();

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

