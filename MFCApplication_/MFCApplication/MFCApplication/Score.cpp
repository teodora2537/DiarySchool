#include "pch.h"
#include "Score.h"
#include <string>
using namespace std;

int idScore;
int classNum;
int score;
string subject;
string date;

Score::Score(int _classNum, string _subject, int _score, string _date)
{
	classNum = _classNum;
	subject = _subject;
	score = _score;
	date = _date;
}

Score::Score()
{
}


int Score::GetIdScore()
{
	return idScore;
}
void Score::SetIdScore(int _idScore)
{
	idScore = _idScore;
}
int Score::GetClassNum()
{
	return classNum;
}
void Score::SetClassNum(int _classNum)
{
	classNum = _classNum;
}

int Score::GetScore()
{
	return score;
}

void Score::SetScore(int _score)
{
	score = _score;
}

string Score::GetSubject()
{
	return subject;
}

void Score::SetSubject(string _subject)
{
	subject = _subject;
}

string Score::GetDate()
{
	return date;
}

void Score::SetDate(string _date)
{
	date = _date;
}

