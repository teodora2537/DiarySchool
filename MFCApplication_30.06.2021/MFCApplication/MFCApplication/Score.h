#pragma once
#include<list>
#include "Library.h"
#include "Student.h"
using namespace std;

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
	bool IsContainAStudent(CScoreData& oScoreData);
	bool AddScore(CScoreData& oScoreData);
	bool EditScore(CScoreData& oScore);
	bool DeleteScore(const int nIdScore);
	bool DeleteScoreByStudent(int nStudentID);
	bool LoadScore(const int nIdScore, CScoreData& oScore);
	
	void Print_Score(list<CScoreData>& listScore);
	
	bool GetIdSubject(CScoreData& oScore);//CString& strSubject, int& m_strIdSub);
	void GetSubject(CScoreData& oScore);
	void GetStudentName(CScoreData& oScore);
	void GetLastId(CScoreData& oScore);
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