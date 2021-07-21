#include "pch.h"
#include "MFCApplication.h"
#include "CStudentTable.h"


IMPLEMENT_DYNAMIC(CStudentTable, CRecordset)

CStudentTable::CStudentTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 11;
	m_nParams = 10;
	m_nDefaultType = dynaset;

	m_iId = 0;
}

/*virtual*/
CStudentTable::~CStudentTable()
{
}

/*virtual*/
void CStudentTable::DoFieldExchange(CFieldExchange* pFX)
{
	__super::DoFieldExchange(pFX);
	
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, "[id]", m_iId);
	RFX_Text(pFX, "[first_name]", m_str_First_name);
	RFX_Text(pFX, "[last_name]", m_str_Last_name);
	RFX_Text(pFX, "[birth_date]", m_oleDT_Birthday);
	RFX_Text(pFX, "[email]", m_str_email);
	RFX_Text(pFX, "[phone_number]", m_str_phone_number);
	RFX_Text(pFX, "[egn]", m_str_egn);
	RFX_Text(pFX, "[city]", m_str_city);
	RFX_Text(pFX, "[post_code]", m_str_post_code);
	RFX_Text(pFX, "[neighborhood]", m_str_neighborhood);
	RFX_Text(pFX, "[address]", m_str_address);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Text(pFX, "[first_name]", m_str_First_name);
	RFX_Text(pFX, "[last_name]", m_str_Last_name);
	RFX_Text(pFX, "[birth_date]", m_oleDT_Birthday);
	RFX_Text(pFX, "[email]", m_str_email);
	RFX_Text(pFX, "[phone_number]", m_str_phone_number);
	RFX_Text(pFX, "[egn]", m_str_egn);
	RFX_Text(pFX, "[city]", m_str_city);
	RFX_Text(pFX, "[post_code]", m_str_post_code);
	RFX_Text(pFX, "[neighborhood]", m_str_neighborhood);
	RFX_Text(pFX, "[address]", m_str_address);
}

extern CDatabase g_dbConnection;

/*virtual*/
CString CStudentTable::GetDefaultConnection() {
	return g_dbConnection.GetConnect();
}

/*virtual*/
CString CStudentTable::GetDefaultSQL() {
	return "[Student]";
}

void CStudentTable::GetRecStruct(STUDENT& oStudent)
{
	oStudent.iId = m_iId;
	strcpy_s(oStudent.sz_First_Name, CStringA(m_str_First_name).GetString());
	strcpy_s(oStudent.sz_Last_Name, CStringA(m_str_Last_name).GetString());
	strcpy_s(oStudent.szDate, CStringA(m_oleDT_Birthday).GetString());
	strcpy_s(oStudent.szEmail, CStringA(m_str_email).GetString());
	strcpy_s(oStudent.szPhoneNumber, CStringA(m_str_phone_number).GetString());
	strcpy_s(oStudent.szEGN, CStringA(m_str_egn).GetString());
	strcpy_s(oStudent.szCity, CStringA(m_str_city).GetString());
	strcpy_s(oStudent.szPostCode, CStringA(m_str_post_code).GetString());
	strcpy_s(oStudent.szNeighborhood, CStringA(m_str_neighborhood).GetString());
	strcpy_s(oStudent.szAddress, CStringA(m_str_address).GetString());
}

void CStudentTable::Add_Edit_Student(STUDENT& stStudent)
{
	Library oLib;
	m_str_First_name = stStudent.sz_First_Name;
	m_str_Last_name = stStudent.sz_Last_Name;
	m_oleDT_Birthday = stStudent.szDate;
	m_str_email = stStudent.szEmail;
	m_str_phone_number = stStudent.szPhoneNumber;
	m_str_egn = stStudent.szEGN;
	m_str_city = stStudent.szCity;
	m_str_post_code = stStudent.szPostCode;
	m_str_neighborhood = stStudent.szNeighborhood;
	m_str_address = stStudent.szAddress;
}

BOOL CStudentTable::LoadStudent(STUDENT& recStudent) 
{		
	m_strFilter.Format("id = '%d'", recStudent.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	GetRecStruct(recStudent);

	Close();

	return TRUE;		
}

bool CStudentTable::IsExist(const STUDENT& recStudent, bool& bExists) 
{
	bExists = false;

	m_strFilter.Format(" email = '%s' ", recStudent.szEmail);

	if (!Open())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	bExists = GetRecordCount() > 0;

	Close();

	return TRUE;
}

BOOL CStudentTable::AddRec(STUDENT& recStudent)
{
	bool bExists = false;

	if (!IsExist(recStudent, bExists))
		return FALSE;

	if (bExists)
	{
		MessageBox(NULL, "The record is exist!", "Isn't Add", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (!Open())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	if (!CanAppend())
	{
		MessageBox(NULL, "The table student can't append!", "Can't append", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	AddNew();

	Add_Edit_Student(recStudent);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	Close();

	return TRUE;
}

BOOL CStudentTable::IsEquals(STUDENT& obj1, STUDENT& obj2)
{
	if (obj1.sz_First_Name != obj2.sz_First_Name)
		return FALSE;
	if (obj1.sz_Last_Name != obj2.sz_Last_Name)
		return FALSE;
	if (obj1.szDate != obj2.szDate)
		return FALSE;
	if (obj1.szEmail != obj2.szEmail)
		return FALSE;
	if (obj1.szPhoneNumber != obj2.szPhoneNumber)
		return FALSE;
	if (obj1.szEGN != obj2.szEGN)
		return FALSE;
	if (obj1.szCity != obj2.szCity)
		return FALSE;
	if (obj1.szPostCode != obj2.szPostCode)
		return FALSE;
	if (obj1.szNeighborhood != obj2.szNeighborhood)
		return FALSE;
	if (obj1.szAddress != obj2.szAddress)
		return FALSE;

	return TRUE;
}

BOOL CStudentTable::EditRec(STUDENT& recStudent)
{
	m_strFilter.Format("id = '%d'", recStudent.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	if (!CanUpdate())
	{
		MessageBox(NULL, "The table student can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	Edit();

	STUDENT recordStudent;

	GetRecStruct(recordStudent);

	if (IsEquals(recordStudent, recStudent))
	{
		Close();
		return true;
	}

	STUDENT stStudent = recStudent;

	//if (memcmp(&recordStudent, &stStudent, sizeof(recordStudent)))
	//{
	//	Close();
	//	return TRUE;
	//}

	Add_Edit_Student(stStudent);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);

		g_dbConnection.Rollback();
		Close();

		return FALSE;
	}

	Close();

	return TRUE;
}

BOOL CStudentTable::DeleteRec(STUDENT& recStudent)
{
	try
	{
		m_strFilter.Format("id = '%d'", recStudent.iId);

		if (!Open())
		{
			MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		if (!IsOpen())
		{
			MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		Delete();

		if (!IsDeleted())
		{
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			Close();

			return FALSE;
		}

		Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete parent!", MB_ICONEXCLAMATION);

		return FALSE;
	}

	return TRUE;
}