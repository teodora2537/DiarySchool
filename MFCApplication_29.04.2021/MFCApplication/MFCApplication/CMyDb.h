#pragma once
#include <afxdb.h>
using namespace std;

class CMyDb :
    public CRecordset
{
public:
	CMyDb(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CMyDb);
	CString m_strClassNum;
	CString m_strFn;
	CString m_strLn;
	CString m_strBirthday;

public:
void DoFieldExchange(CFieldExchange* pFX);
};

