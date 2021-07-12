#pragma once
#include "afxdb.h"
#include "Score.h"
#include "Library.h"

#define DEF_NAME_LEN 100

struct SCORE
{
	int iIdScore; // id score
	int iIdStudent; // id student
	char szName[DEF_NAME_LEN + 1]; // sz- char array ->name student
	int iIdSubject; // id subject
	char szSubject[DEF_NAME_LEN + 1]; // name subject
	int iScore; //score
	char szDate[9 + 1];//DBTIMESTAMP ->date of score

	SCORE()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CScoreTable : public CRecordset
{
public:
	CScoreTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CScoreTable)
	virtual ~CScoreTable();

protected: //methods
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();

public: //memeber
	int m_iIdScore;
	int m_iIdStudent;
	int m_iIdSubject;
	int m_iScore;
	CString m_oleDateTime;

public: //methods
	void Add_Edit_Score(SCORE& stScore);
	void Load(CScoreData& oScore);
};
