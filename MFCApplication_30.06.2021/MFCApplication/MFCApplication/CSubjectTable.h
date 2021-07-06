#pragma once
#include <afxdb.h>
#include "Subject.h"

#define DEF_NAME_LEN 100

struct SUBJECT {
	int iId;
	char szSubject[DEF_NAME_LEN + 1];
	char szTeacher[DEF_NAME_LEN + 1];
	char sz_First_Name[DEF_NAME_LEN + 1];
	char sz_Last_Name[DEF_NAME_LEN + 1];

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

protected: //methods
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();

public: //member
	int	m_iId;
	CString m_strSubject;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
	CString m_strStatus;
	
public: //methods
	void Add_Edit(SUBJECT& stSubject);
	void DeleteSubject();
	void Load(CSubjectData& oSubject);
	bool IsExist(CSubjectData& oSubject);
};