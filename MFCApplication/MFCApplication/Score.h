#pragma once
#include<string>
#include<map>
#include<vector>
using namespace std;

class CScoreData
{
public:
	CScoreData(int _classNum, string _subject, int _score, string _date);
//	Score(int _classNum);
	CScoreData();

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
	multimap<int, vector<string>> PrintScore();
};