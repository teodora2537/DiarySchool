#pragma once
#include "afxdb.h"

class CScoreTable : public CDialogEx, public CRecordset
{
public:
	CScoreTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CScoreTable)

public:
	virtual ~CScoreTable();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SCORE };
#endif

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
	DECLARE_MESSAGE_MAP()

public:
	int m_iIdScore;
	int m_iIdStudent;
	int m_iIdSubject;
	int m_iScore;
	COleDateTime _oleDateTime;
	CString m_oleDateTime;
};
