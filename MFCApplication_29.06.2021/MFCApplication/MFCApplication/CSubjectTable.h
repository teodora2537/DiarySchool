#pragma once
#include <afxdb.h>
#include "Subject.h"

class CSubjectTable : public CRecordset
{
public:
	CSubjectTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubjectTable)

public:
	virtual ~CSubjectTable();

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

public:
	int	m_iId;
	CString m_strSubject;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
	CString m_strStatus;
	void Add(CSubjectData& oSubject);
	void EditSubject(CSubjectData& oSubject);
	void DeleteSubject();
	void Load(CSubjectData& oSubject);
	bool IsExist(CSubjectData& oSubject);
};