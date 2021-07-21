#include "pch.h"
#include "MFCApplication.h"
#include "CParentTable.h"

IMPLEMENT_DYNAMIC(CParentTable, CRecordset)

CParentTable::CParentTable(CDatabase* pdb) 
	:CRecordset(pdb)
{
	m_nFields = 10;
	m_nParams = 9;
	m_nDefaultType = dynaset;
	m_iId = 0;
	m_iIdStudent = 0;
}

/*virtual*/
CParentTable::~CParentTable()
{
}

/*virtual*/
void CParentTable::DoFieldExchange(CFieldExchange* pFX)
{
	__super::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, "[id]", m_iId);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Text(pFX, "[first_name]", m_str_first_name);
	RFX_Text(pFX, "[last_name]", m_str_last_name);
	RFX_Text(pFX, "[email]", m_str_email);
	RFX_Text(pFX, "[phone_number]", m_str_phone_number);
	RFX_Text(pFX, "[city]", m_str_city);
	RFX_Text(pFX, "[post_code]", m_str_post_code);
	RFX_Text(pFX, "[neighborhood]", m_str_neighborhood);
	RFX_Text(pFX, "[address]", m_str_address);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Text(pFX, "[first_name]", m_str_first_name);
	RFX_Text(pFX, "[last_name]", m_str_last_name);
	RFX_Text(pFX, "[email]", m_str_email);
	RFX_Text(pFX, "[phone_number]", m_str_phone_number);
	RFX_Text(pFX, "[city]", m_str_city);
	RFX_Text(pFX, "[post_code]", m_str_post_code);
	RFX_Text(pFX, "[neighborhood]", m_str_neighborhood);
	RFX_Text(pFX, "[address]", m_str_address);
}

extern CDatabase g_dbConnection;

/*virtual*/
CString CParentTable::GetDefaultConnection() {
	return g_dbConnection.GetConnect();
}

/*virtual*/
CString CParentTable::GetDefaultSQL() {
	return "[Parent]";
}

void CParentTable::GetRecStruct(PARENT& oParent)
{
	oParent.iId = m_iId;
	oParent.iStudentID = m_iIdStudent;
	strcpy_s(oParent.sz_First_Name, CStringA(m_str_first_name).GetString());
	strcpy_s(oParent.sz_Last_Name, CStringA(m_str_last_name).GetString());
	strcpy_s(oParent.szPhoneNumber, CStringA(m_str_phone_number).GetString());
	strcpy_s(oParent.szEmail, CStringA(m_str_email).GetString());
	strcpy_s(oParent.szCity, CStringA(m_str_city).GetString());
	strcpy_s(oParent.szPostCode, CStringA(m_str_post_code).GetString());
	strcpy_s(oParent.szNeighborhood, CStringA(m_str_neighborhood).GetString());
	strcpy_s(oParent.szAddress, CStringA(m_str_address).GetString());
}

void CParentTable::Add_Edit_Parent(PARENT& stParent)
{
	m_iIdStudent =	stParent.iStudentID;
	m_str_first_name = stParent.sz_First_Name;
	m_str_last_name = stParent.sz_Last_Name;
	m_str_phone_number = stParent.szPhoneNumber;
	m_str_email = stParent.szEmail;
	m_str_city = stParent.szCity;
	m_str_post_code = stParent.szPostCode;
	m_str_neighborhood = stParent.szNeighborhood;
	m_str_address =	stParent.szAddress;
}

BOOL CParentTable::IsExist(const PARENT& recParent, bool& bExists)
{
	bExists = false;

	m_strFilter.Format(" phone_number = '%s' ", recParent.szPhoneNumber);

	if (recParent.iId)
		m_strFilter.AppendFormat(" and id <> %d ", recParent.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}
	
	bExists = GetRecordCount() > 0;

	Close();

	return TRUE;
}

BOOL CParentTable::AddRec(PARENT& recParent)
{
	bool bExists = false;

	if (!IsExist(recParent, bExists))
		return FALSE;

	if (bExists)
	{
		MessageBox(NULL, "The record is exist!", "Isn't Add", MB_OK | MB_ICONERROR);
		return FALSE;
	}

	if (!Open())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	if (!CanAppend())
	{
		MessageBox(NULL, "The table parent can't append!", "Can't append", MB_OK | MB_ICONERROR);
		Close();
	
		return false;
	}

	AddNew();

	Add_Edit_Parent(recParent);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	Close();

	return TRUE;
}

BOOL CParentTable::IsEquals(PARENT& obj1, PARENT& obj2) 
{
	if (obj1.sz_First_Name != obj2.sz_First_Name) 
		return FALSE;
	if (obj1.sz_Last_Name != obj2.sz_Last_Name)
		return FALSE;
	if (obj1.szPhoneNumber != obj2.szPhoneNumber)
		return FALSE;	
	if (obj1.szEmail != obj2.szEmail)
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

BOOL CParentTable::EditRec(PARENT& recParent) 
{
	m_strFilter.Format("id = '%d'", recParent.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table Parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	if (!CanUpdate())
	{
		MessageBox(NULL, "The table Parent can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	Edit();

	PARENT recordParent;

	GetRecStruct(recordParent);

	if (IsEquals(recordParent, recParent)) 
	{
		Close();
		return true;
	}

	PARENT stParent;
	stParent = recParent;
	//
	//if (memcmp(&recordParent, &stParent, sizeof(recordParent)))
	//{
	//	Close();
	//	return true;
	//}


	Add_Edit_Parent(stParent);

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

BOOL CParentTable::DeleteRecords(PARENT& recParent)
{
	try 
	{
		m_strFilter.Format("student_id = '%d'", recParent.iStudentID);

		if (!Open())
		{
			MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		if (!IsOpen())
		{
			MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		if (GetRecordCount() < 1)
			return TRUE;

		while (!IsEOF())
		{
			Delete();
			MoveNext();
		}

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
		AfxMessageBox("Error delete student!", MB_ICONEXCLAMATION);

		return FALSE;
	}

	return TRUE;
}

BOOL CParentTable::DeleteRec(PARENT& recParent)
{
	try
	{
		m_strFilter.Format("id = '%d'", recParent.iId);

		if (!Open())
		{
			MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		if (!IsOpen())
		{
			MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
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

BOOL CParentTable::LoadParent(PARENT& recParent) 
{
	m_strFilter.Format("id = '%d'", recParent.iId);

	if (!Open())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table Parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	GetRecStruct(recParent);

	Close();

	return true;
}