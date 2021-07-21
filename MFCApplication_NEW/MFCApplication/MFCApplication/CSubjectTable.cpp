#include "pch.h"
#include "MFCApplication.h"
#include "CSubjectTable.h"

IMPLEMENT_DYNAMIC(CSubjectTable, CRecordset)

CSubjectTable::CSubjectTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 5;
	m_nParams = 5;
	m_nDefaultType = dynaset;

	m_iId = 0;
}

CSubjectTable::~CSubjectTable()
{
}

void CSubjectTable::DoFieldExchange(CFieldExchange* pFX)
{
	__super::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, "[id]", m_iId);
	RFX_Text(pFX, "[subject]", m_strSubject);
	RFX_Text(pFX, "[first_name_teacher]", m_strFirstNameTeacher);
	RFX_Text(pFX, "[last_name_teacher]", m_strLastNameTeacher);
	RFX_Text(pFX, "[status]", m_strStatus);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[id]", m_iId);
	RFX_Text(pFX, "[subject]", m_strSubject);
	RFX_Text(pFX, "[first_name_teacher]", m_strFirstNameTeacher);
	RFX_Text(pFX, "[last_name_teacher]", m_strLastNameTeacher);
	RFX_Text(pFX, "[status]", m_strStatus);
}

extern CDatabase g_dbConnection;

CString CSubjectTable::GetDefaultConnection() {
	return g_dbConnection.GetConnect();
}

CString CSubjectTable::GetDefaultSQL() {
	return "[Subject]";
}

void CSubjectTable::GetRecStruct(SUBJECT& stSubject)
{
	stSubject.iId = m_iId;
	strcpy_s(stSubject.szSubject, CStringA(m_strSubject).GetString());
	strcpy_s(stSubject.sz_First_Name, CStringA(m_strFirstNameTeacher).GetString());
	strcpy_s(stSubject.sz_Last_Name, CStringA(m_strLastNameTeacher).GetString());
}

void CSubjectTable::Add_Edit(SUBJECT& stSubject) 
{
	m_strSubject = stSubject.szSubject;
	m_strFirstNameTeacher = stSubject.sz_First_Name;
	m_strLastNameTeacher = stSubject.sz_Last_Name;
}

BOOL CSubjectTable::Load(SUBJECT& recSubject) 
{
	m_strFilter.Format("id = '%d'", recSubject.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	GetRecStruct(recSubject);

	Close();

	return TRUE;
}

bool CSubjectTable::IsExist(const SUBJECT& recSubject, bool& bExists)
{
	bExists = false;

	m_strFilter.Format("subject = '%s' ", recSubject.szSubject);

	if (!Open())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}


	bExists = GetRecordCount() > 0;

	Close();

	return TRUE;
}

/*TO DOS*/
bool CSubjectTable::IsEquals(const SUBJECT& recSubject, bool& bEquals) 
{
	return FALSE;
}

BOOL CSubjectTable::AddRec(SUBJECT& recSubject)
{
	bool bExists = false;

	if (!IsExist(recSubject, bExists))
		return FALSE;

	if (bExists)
	{
		MessageBox(NULL, "The record is exist!", "Isn't Add", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (!Open())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	if (!CanAppend())
	{
		MessageBox(NULL, "The table subject can't append!", "Can't append", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	AddNew();

	Add_Edit(recSubject);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	Close();

	return TRUE;
}

BOOL CSubjectTable::EditRec(SUBJECT& recSubject)
{
	bool bExists = false;
	if (IsEquals(recSubject, bExists))
	return FALSE;

	m_strFilter.Format("id = '%d'", recSubject.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	if (!CanUpdate())
	{
		MessageBox(NULL, "The table subject can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	Edit();

	SUBJECT recordSubject;

	GetRecStruct(recordSubject);

	SUBJECT stSubject;

	if (memcmp(&recordSubject, &stSubject, sizeof(recordSubject)))
	{
		Close();
		return true;
	}

	stSubject = recSubject;

	Add_Edit(stSubject);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);

		g_dbConnection.Rollback();
		Close();

		return false;
	}

	Close();

	return TRUE;
}

BOOL CSubjectTable::DeleteRec(SUBJECT& recSubject)
{
	try
	{
		m_strFilter.Format("id = '%d'", recSubject.iId);

		if (!Open())
		{
			MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		if (!IsOpen())
		{
			MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		Edit();

		m_strStatus = "unactiv";

		if (!Update()) {
			MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
			Close();

			return FALSE;
		}

		Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete subject!", MB_ICONEXCLAMATION);

		return FALSE;
	}

	return TRUE;
}

BOOL CSubjectTable::LoadSubject(SUBJECT& recSubject)
{
	m_strFilter.Format("id = '%d'", recSubject.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	GetRecStruct(recSubject);

	Close();

	return true;
}