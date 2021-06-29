#pragma once
#include "afxdb.h"

class CScoreTable : public CRecordset
{
public:
	CScoreTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CScoreTable)

public:
	virtual ~CScoreTable();

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

public:
	int m_iIdScore;
	int m_iIdStudent;
	int m_iIdSubject;
	int m_iScore;
	COleDateTime _oleDateTime;
	CString m_oleDateTime;
};
