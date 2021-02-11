#pragma once
#include<string>
using namespace std;

class Score
{
public:
	Score(int _classNum, string _subject, int _score, string _date);
//	Score(int _classNum);
	Score();

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

