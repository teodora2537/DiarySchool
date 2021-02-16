#pragma once
#include<string>
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



