#pragma once
#include "afxdb.h"
#include "Student.h"
using namespace std;

class CStudentTable :  public CRecordset
{
public:
	CStudentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentTable)

public:
	virtual ~CStudentTable();

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);

public:
	int m_iId;
	CString m_str_First_name;
	CString m_str_Last_name;
	CString m_oleDT_Birthday;
	CString m_str_email; 
	CString m_str_phone_number;
	CString m_str_egn;
	CString m_str_city;
	CString m_str_post_code;
	CString m_str_neighborhood;
	CString m_str_address;
    void Add_Edit_Student(CStudentData& oStudent);
	void LoadStudent(CStudentData& oStudent);
	bool IsExist(CStudentData& oStudent);
};

