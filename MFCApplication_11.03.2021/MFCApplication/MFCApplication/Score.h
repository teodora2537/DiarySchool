#pragma once
#include<string>
#include<map>
#include<vector>
using namespace std;

#define DEF_SCORE_NAME_LEN 100

struct SCORE
{
	int iId;
	int iClassNum;
	int iScore;
	int iRoomNumber;
	char szName[DEF_SCORE_NAME_LEN + 1]; // sz- char array
	char szDate[9+1];//DBTIMESTAMP

	SCORE()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CScoreData
{
public:
	CScoreData(int _classNum, CString _subject, int _score, CString _date);
	CScoreData();

	int m_iIdScore, m_iClassNum, m_iScore;
	CString m_strSubject, m_strDate;
};

class CScore
{
public:
	CScore();
	virtual ~CScore();

public:
	bool AddScore(CScoreData& oScoreData);
	bool EditScore(const CScoreData& oScore);
	bool LoadScore(const int nIdScore, CScoreData& oScore);
	bool DeleteScore(const int nClassNumber);
	void PrintScore(map<int, vector<CString>>& mapScore); /*LoadAllScores*/
};	