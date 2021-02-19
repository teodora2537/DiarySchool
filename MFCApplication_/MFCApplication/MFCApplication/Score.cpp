#include "pch.h"
#include "Score.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Library.h"
#include "Student.h"
using namespace std;

CScoreData::CScoreData(int _classNum, string _subject, int _score, string _date)
{
	m_iClassNum = _classNum;
	m_strSubject = _subject;
	m_iScore = _score;
	m_strDate = _date;
}

CScoreData::CScoreData()
{
}

int CScoreData::GetIdScore()
{
	return m_iIdScore;
}
void CScoreData::SetIdScore(int _idScore)
{
	m_iIdScore = _idScore;
}

int CScoreData::GetClassNum()
{
	return m_iClassNum;
}
void CScoreData::SetClassNum(int _classNum)
{
	m_iClassNum = _classNum;
}

int CScoreData::GetScore()
{
	return m_iScore;
}
void CScoreData::SetScore(int _score)
{
	m_iScore = _score;
}

string CScoreData::GetSubject()
{
	return m_strSubject;
}
void CScoreData::SetSubject(string _subject)
{
	m_strSubject = _subject;
}

string CScoreData::GetDate()
{
	return m_strDate;
}
void CScoreData::SetDate(string _date)
{
	m_strDate = _date;
}

CScore::CScore()
{
}

CScore::~CScore()
{
}

bool CScore::AddScore(CScoreData& oScoreData)
{
	Library lib;
	CScoreData score;
	int length = 0;

	fstream outFile, inputfile;
	outFile.open("Score.txt", ios::app);

	int classNum = score.GetClassNum();
	int i_score = score.GetScore();
	string subject = score.GetSubject();
	string date = score.GetDate();
	CScore oScore;
	multimap<int, vector<string>> mapScores = oScore.PrintScore();
	int idScore = mapScores.size() + 1;

	outFile << idScore << '|' << classNum << '|' << subject << '|' << i_score << '|' << date << "\n";
	outFile.close();

	return true;
}

//	! you must use the parametter oScore
bool CScore::EditScore(const CScoreData& oScore)
{
	//Datas from edit boxes
	CScoreData score;
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
	CScoreData currentScore;
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

//Empty
bool CScore::LoadScore(const int nClassNumber, CScoreData& oScore)
{
	return false;
}

//	! you must use the parametter nClassNumber
bool CScore::DeleteScore(const int nClassNumber)
{
	CScoreData score;
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
	CScoreData currentScore;
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

multimap<int, vector<string>> CScore::PrintScore()
{
	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	CScoreData currentScore;
	bool isFind = false;
	multimap<int, vector<string>> mapScore;
	vector<string> _vector;
	CStudent oStudent;
	map<int, vector<string>> allStudents = oStudent.PrintStudent();

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
		string nameStudent = allStudents[currentScore.GetClassNum()][0] + " " + allStudents[currentScore.GetClassNum()][1];
		_vector.push_back(nameStudent);
		_vector.push_back(currentScore.GetSubject());
		_vector.push_back(to_string(currentScore.GetScore()));
		_vector.push_back(currentScore.GetDate());
		mapScore.insert(pair<int, vector<string>>(currentScore.GetClassNum(), _vector));
		_vector.clear();
	}
	file.close();
	return mapScore;
}