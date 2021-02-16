#include "pch.h"
#include "Score.h"
#include <string>
using namespace std;

int idScore;
int classNum;
int score;
string subject;
string date;

CScoreData::CScoreData(int _classNum, string _subject, int _score, string _date)
{
	classNum = _classNum;
	subject = _subject;
	score = _score;
	date = _date;
}

CScoreData::CScoreData()
{
}


int CScoreData::GetIdScore()
{
	return idScore;
}
void CScoreData::SetIdScore(int _idScore)
{
	idScore = _idScore;
}
int CScoreData::GetClassNum()
{
	return classNum;
}
void CScoreData::SetClassNum(int _classNum)
{
	classNum = _classNum;
}

int CScoreData::GetScore()
{
	return score;
}

void CScoreData::SetScore(int _score)
{
	score = _score;
}

string CScoreData::GetSubject()
{
	return subject;
}

void CScoreData::SetSubject(string _subject)
{
	subject = _subject;
}

string CScoreData::GetDate()
{
	return date;
}

void CScoreData::SetDate(string _date)
{
	date = _date;
}

