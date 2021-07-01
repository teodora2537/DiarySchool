#pragma once
#include <afxdb.h>
#include "Subject.h"

#define DEF_SUBJECT_NAME_LEN 100
#define DEF_SUBJECT_TEACHER_NAME_LEN 100

struct SUBJECT {
	int iId;
	char szSubject[DEF_SUBJECT_NAME_LEN + 1];
	char szTeacher[DEF_SUBJECT_TEACHER_NAME_LEN + 1];
	char sz_First_Name[50 + 1];
	char sz_Last_Name[50 + 1];

	SUBJECT()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

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
	
	void Add_Edit(SUBJECT& stSubject);
	void DeleteSubject();
	void Load(CSubjectData& oSubject);
	bool IsExist(CSubjectData& oSubject);
};