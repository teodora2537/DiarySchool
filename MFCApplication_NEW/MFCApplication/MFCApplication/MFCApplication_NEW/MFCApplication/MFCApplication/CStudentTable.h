#pragma once
#include "afxdb.h"
#include "Student.h"

#define DEF_SCORE_NAME_LEN 100

struct STUDENT {
	int iId;
	char szName[DEF_SCORE_NAME_LEN + 1]; // sz- char array ->name student
	char sz_First_Name[50 + 1];
	char sz_Last_Name[50 + 1];
	char szDate[10 + 1];//DBTIMESTAMP ->date of score
	char szEmail[50 + 1];
	char szPhoneNumber[20 + 1];
	char szEGN[50 + 1];
	char szCity[70 + 1];
	char szPostCode[10 + 1];
	char szNeighborhood[70 + 1];
	char szAddress[1000 + 1]; //max size

	STUDENT()
	{
		SecureZeroMemory(this, sizeof(*this));
	}
};

class CStudentTable :  public CRecordset
{
public:
	CStudentTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CStudentTable)

public:
	virtual ~CStudentTable();

protected: //methods
	virtual void DoFieldExchange(CFieldExchange* pFX);
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();


public: //member
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


public: // methods
    void Add_Edit_Student(STUDENT& stStudent);
	BOOL LoadStudent(STUDENT& oStudent);
	bool IsExist(const STUDENT& recStudent, bool& bExists);
	BOOL AddRec(STUDENT& recStudent);
	BOOL IsEquals(STUDENT& obj1, STUDENT& obj2);
	BOOL EditRec(STUDENT& recStudent);
	BOOL DeleteRec(STUDENT& recStudent);
void GetRecStruct(STUDENT& oStudent);
};