#pragma once
#include<string>
#include<map>
#include<vector>
using namespace std;

class CScoreData
{
public:
	CScoreData(int _classNum, string _subject, int _score, string _date);
	CScoreData();

	int m_iIdScore, m_iClassNum, m_iScore;
	string m_strSubject, m_strDate;

	int GetIdScore();
	void SetIdScore(int _idScore);

	int GetClassNum();
	void SetClassNum(int _classNum);

	int GetScore();
	void SetScore(int _score);

	string GetSubject();
	void SetSubject(string _subject);

	string GetDate();
	void SetDate(string _date);
};

class CScore
{
public:
	CScore();
	virtual ~CScore();

public:

	bool AddScore(CScoreData& oScoreData);
	bool EditScore(const CScoreData& oScore);
	bool LoadScore(const int nClassNumber, CScoreData& oScore);
	bool DeleteScore(const int nClassNumber);
	
	vector<string> m_vecInfoStudent;
	map<int, vector<string>> m_mapAllStudent;
	multimap<int, vector<string>> PrintScore();
	multimap<int, vector<string>> m_mapAllScore;

	int m_iCount = 0;
	
	string m_strText;
	string m_strToken;
	string m_strName;
	
	size_t m_sizeTPosition;
	
	CScoreData oCurrentScore;
	
	bool m_bIsFind = false;
};