#pragma once
#include <afxdb.h>
class CDatabase :
    public CRecordset, public CDatabse
{
public: 
	CString m_strClassNum;
	CString m_strFn;
	CString m_strLn;
	CString m_strBirthday;

public:

};

