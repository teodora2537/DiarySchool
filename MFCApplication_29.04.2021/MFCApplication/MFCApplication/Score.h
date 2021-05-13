#pragma once
#include<list>
//#include "CListMethods.h"
#include "Library.h"
#include "Student.h"
using namespace std;

#define DEF_SCORE_NAME_LEN 100

struct SCORE
{
	int iId; // id score
	int iClassNum; // id student
	char szName[DEF_SCORE_NAME_LEN + 1]; // sz- char array ->name student
	int iRoomNumber; // id subject
	char szSubject[DEF_SCORE_NAME_LEN + 1]; // name subject
	int iScore; //score
	char szDate[9 + 1];//DBTIMESTAMP ->date of score

	SCORE()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CScoreData
{
public:
	CScoreData(int _idScore, int _classNum, CString _subject, int _score, COleDateTime _date);
	CScoreData();

	int m_iIdScore;
	int m_iIdStudent;
	int m_iIdSubject;
	int m_iScore;
	CString m_strSubject;
	COleDateTime m_oleDateTime;
	CString m_strNameStudent;
};

class CScore
{
public:
	CScore();
	virtual ~CScore();

public:
	bool AddScore(CScoreData& oScoreData);
	bool EditScore(CScoreData& oScore);
	bool LoadScore(const int nIdScore, CScoreData& oScore);
	bool DeleteScore(const int nIdScore);
	void Print_Score(list<SCORE>& listScore);
};

struct COMBO_DATA
{
	char szName[101];
	int nID;
};

class CMyComboBox : public CComboBox
{
public:
	void LoadData(const CArray<COMBO_DATA>& arrData, CComboBox& m_combo);

	int GetSelectedValue(CComboBox& m_combo) const;
};

void isContainAStudent(CString& sqlString, CScoreData& oScoreData, CString& isContains);

void GetIdSubject(CScoreData& oScoreData, int& m_strIdSub);

void GetStudentName(CString& whereClause, CScoreData& oScore);

void GetSubject(CString& whereClause, CScoreData& oScore);
