#pragma once
#include "afxdb.h"
#include "Score.h"
#include "Library.h"

#define DEF_NAME_LEN 100

struct SCORE
{
	int iIdScore; // id score
	int iIdStudent; // id student
	int iIdSubject; // id subject
	int iScore; //score
	char szDate[10 + 1];//DBTIMESTAMP ->date of score

	SCORE()
	{
		SecureZeroMemory(this, sizeof(*this));
	}

  const	BOOL IsEquals(const SCORE& obj1, const SCORE& obj2);
};

class CScoreTable : public CRecordset
{
public:
	CScoreTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CScoreTable)
	virtual ~CScoreTable();

protected: //methods
	virtual void DoFieldExchange(CFieldExchange* pFX);
	//get
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();

	void GetRecStruct(SCORE& oScore);

public: //memeber
	int m_iIdScore;
	int m_iIdStudent;
	int m_iIdSubject;
	int m_iScore;
	CString m_oleDateTime;

public: //methods
	void Add_Edit_Score(SCORE& stScore);
	BOOL LoadScore(SCORE& recScore);
	
	BOOL AddRec(SCORE& recScore);
	BOOL EditRec(SCORE& recScore);
	BOOL DeleteRec(SCORE& recScore);
};
