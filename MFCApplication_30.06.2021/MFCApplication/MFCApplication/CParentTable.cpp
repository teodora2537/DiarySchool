#include "pch.h"
#include "MFCApplication.h"
#include "CParentTable.h"
using namespace std;

IMPLEMENT_DYNAMIC(CParentTable, CRecordset)

CParentTable::CParentTable(CDatabase* pdb) 
	:CRecordset(pdb)
{
	m_nFields = 10;
	m_nParams = 9;
	m_nDefaultType = dynaset;
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

void CParentTable::LoadParent(CParentData& oParent)
{
	oParent.m_iParentId = m_iId;
	oParent.m_iStudentId = m_iIdStudent;
	oParent.m_strFirstName = m_str_first_name;
	oParent.m_strLastName = m_str_last_name;
	oParent.m_strPhoneNumber = m_str_phone_number;
	oParent.m_strEmail = m_str_email;
	oParent.m_strCity = m_str_city;
	oParent.m_strPostCode = m_str_post_code;
	oParent.m_strNeighborhood = m_str_neighborhood;
	oParent.m_strAddress = m_str_address;
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

bool CParentTable::IsExist(CParentData& oParent)
{
	if (m_iIdStudent == oParent.m_iStudentId &&
		m_str_first_name == oParent.m_strFirstName &&
		m_str_last_name == oParent.m_strLastName &&
		m_str_phone_number == oParent.m_strPhoneNumber &&
		m_str_email == oParent.m_strEmail &&
		m_str_city == oParent.m_strCity &&
		m_str_post_code == oParent.m_strPostCode &&
		m_str_neighborhood == oParent.m_strNeighborhood &&
		m_str_address == oParent.m_strAddress) {
		return true;
	}
	
	return false;
}