#include "pch.h"
#include "Score.h"
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include "Library.h"
#include "Student.h"
using namespace std;

CScoreData::CScoreData(int _classNum, CString _subject, int _score, CString _date)
{
	m_iClassNum = _classNum;
	m_strSubject = _subject;
	m_iScore = _score;
	m_strDate = _date;
}

CScoreData::CScoreData()
{
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
	int length = 0;

	fstream outFile, inputfile;
	outFile.open("Score.txt", ios::app);

	int classNum = oScoreData.m_iClassNum;
	int i_score = oScoreData.m_iScore;
	CString subject = oScoreData.m_strSubject;
	CString date = oScoreData.m_strDate;
	CScore oScore;
	multimap<int, vector<CString>> mapScores;
	oScore.PrintScore(mapScores);

	int idScore = mapScores.size() + 1;

	outFile << idScore << DEF_FILE_DATA_SEPARATOR << classNum << DEF_FILE_DATA_SEPARATOR << subject << DEF_FILE_DATA_SEPARATOR << i_score << DEF_FILE_DATA_SEPARATOR << date << "\n";
	outFile.close();

	return true;
}

//	! you must use the parametter oScore
bool CScore::EditScore(const CScoreData& oScore)
{
	//Datas from edit boxes
	int m_iIdScore = oScore.m_iIdScore;
	int m_iClassNum = oScore.m_iClassNum;
	CString m_strSubject = oScore.m_strSubject;
	int m_iScore = oScore.m_iScore;
	CString m_strDate = oScore.m_strDate;

	int m_iCount = 0;
	string m_strText;
	CString m_strToken;
	fstream m_file;
	size_t m_sizeTPosition;
	CScoreData oCurrentScore;
	bool m_bIsFind = false;
	multimap<int, vector<CString>> m_mapAllScore;
	vector<CString> m_vecInfoScore;

	m_file.open("Score.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		// set data's score to class score
		while (true)
		{
			m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
			m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
			m_iCount++;
			if (m_iCount == 1)
			{
				oCurrentScore.m_iIdScore = atoi(m_strToken);
				m_iIdScore = oCurrentScore.m_iIdScore;
			} 
			if (m_iCount == 2) oCurrentScore.m_iClassNum = atoi(m_strToken);
			else if (m_iCount == 3) oCurrentScore.m_strSubject = m_strToken;
			else if (m_iCount == 4)  oCurrentScore.m_iScore = atoi(m_strToken);
			else if (m_iCount == 5) { oCurrentScore.m_strDate = m_strToken; break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		//if exist (from edit box) save it and continue. 
		if (oCurrentScore.m_iClassNum == m_iClassNum &&
			oCurrentScore.m_strSubject == m_strSubject && oCurrentScore.m_strDate == m_strDate)
		{
			CString m_strClassNum;
			m_strClassNum.Format("%d", m_iClassNum);
			m_vecInfoScore.push_back(m_strClassNum);
			m_vecInfoScore.push_back(m_strSubject);
			CString m_strScore;
			m_strScore.Format("%d", m_iScore);
			m_vecInfoScore.push_back(m_strScore);
			m_vecInfoScore.push_back(m_strDate);
			m_mapAllScore.insert(pair<int, vector<CString>>(m_iIdScore, m_vecInfoScore));
			m_vecInfoScore.clear();
			m_bIsFind = true;
			continue;
		}
		//save score from file
		CString m_strCurrentClassNum;
		m_strCurrentClassNum.Format("%d", oCurrentScore.m_iClassNum);
		m_vecInfoScore.push_back(m_strCurrentClassNum);
		m_vecInfoScore.push_back(oCurrentScore.m_strSubject);
		CString m_strCurrentScore;
		m_strCurrentScore.Format("%d", oCurrentScore.m_iScore);
		m_vecInfoScore.push_back(m_strCurrentScore);
		m_vecInfoScore.push_back(oCurrentScore.m_strDate);
		m_mapAllScore.insert(pair<int, vector<CString>>(m_iIdScore, m_vecInfoScore));
		m_vecInfoScore.clear();
	}
	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Score.txt", ios::out | ios::trunc);
		//Set score in the file.
		for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
		{
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR << (*i).second[0] << DEF_FILE_DATA_SEPARATOR << (*i).second[1] << DEF_FILE_DATA_SEPARATOR << (*i).second[2] << DEF_FILE_DATA_SEPARATOR << (*i).second[3] << "\n";
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

bool CScore::DeleteScore(const int nClassNumber)
{
	CScoreData oScoreData;

	int m_iCount = 0;
	string m_strText;
	CString m_strToken;
	fstream m_file;
	size_t m_sizeTPosition;
	CScoreData oCurrentScoreData;
	bool m_bIsFind = false;
	multimap<int, vector<CString>> m_mapAllScore;
	vector<CString> m_vecInfoScore;

	m_file.open("Score.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;

		while (true)
		{
			m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
			m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
			m_iCount++;
			if (m_iCount == 1) oCurrentScoreData.m_iIdScore = atoi(m_strToken);
			else if (m_iCount == 2) oCurrentScoreData.m_iClassNum = atoi(m_strToken);
			else if (m_iCount == 3) oCurrentScoreData.m_strSubject = m_strToken;
			else if (m_iCount == 4) oCurrentScoreData.m_iScore = atoi(m_strToken);
			else if (m_iCount == 5) { oCurrentScoreData.m_strDate = m_strToken; break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		if (oCurrentScoreData.m_iIdScore == nClassNumber)
		{
			m_bIsFind = true;
			continue;
		}

		CString m_strClassNum;
		m_strClassNum.Format("%d", oCurrentScoreData.m_iClassNum);
		m_vecInfoScore.push_back(m_strClassNum);
		m_vecInfoScore.push_back(oCurrentScoreData.m_strSubject);
		CString m_strScore;
		m_strScore.Format("%d", oCurrentScoreData.m_iScore);
		m_vecInfoScore.push_back(m_strScore);
		m_vecInfoScore.push_back(oCurrentScoreData.m_strDate);
		m_mapAllScore.insert(pair<int, vector<CString>>(oCurrentScoreData.m_iIdScore, m_vecInfoScore));
		m_vecInfoScore.clear();
	}

	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Score.txt", ios::out | ios::trunc);

		for (auto i = m_mapAllScore.begin(); i != m_mapAllScore.end(); i++)
		{
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR << (*i).second[0] << DEF_FILE_DATA_SEPARATOR << (*i).second[1] << DEF_FILE_DATA_SEPARATOR << (*i).second[2] << DEF_FILE_DATA_SEPARATOR << (*i).second[3] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

void CScore::PrintScore(multimap<int, vector<CString>>& mapScore)
{
	vector<CString> m_vecInfoStudent;
	map<int, vector<CString>> m_mapAllStudent;
	

	int m_iCount = 0;
	
	string m_strText;
	CString m_strToken;
	CString m_strName;

	size_t m_sizeTPosition;
	
	CScoreData oCurrentScore;
	
	bool m_bIsFind = false;

	mapScore.clear();
	
	fstream m_file;

	m_file.open("Score.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		while (true)
		{
			m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
			m_strToken = (m_strText.substr(0, m_sizeTPosition).c_str());
			m_iCount++;
			if (m_iCount == 1)
				oCurrentScore.m_iIdScore = atoi(m_strToken);
			else if (m_iCount == 2)
				oCurrentScore.m_iClassNum = atoi(m_strToken);
			else if (m_iCount == 3)
				oCurrentScore.m_strSubject = m_strToken;
			else if (m_iCount == 4)
				oCurrentScore.m_iScore = atoi(m_strToken);
			else if (m_iCount == 5)
			{
				oCurrentScore.m_strDate = m_strToken;
				break;
			}
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}
		CStudent oStud;
		oStud.PrintStudent(m_mapAllStudent);
		m_strName = m_mapAllStudent[oCurrentScore.m_iClassNum][0] + " " + m_mapAllStudent[oCurrentScore.m_iClassNum][1];
		m_vecInfoStudent.push_back(m_strName);
		m_vecInfoStudent.push_back(oCurrentScore.m_strSubject);
		CString m_strScore;
		m_strScore.Format("%d", oCurrentScore.m_iScore);
		m_vecInfoStudent.push_back(m_strScore);
		m_vecInfoStudent.push_back(oCurrentScore.m_strDate);
		mapScore.insert(pair<int, vector<CString>>(oCurrentScore.m_iClassNum, m_vecInfoStudent));
		m_vecInfoStudent.clear();
	}
	m_file.close();
}