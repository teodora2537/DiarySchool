#include "pch.h"
#include "MFCApplication.h"
#include "CStudentTable.h"
#include "Student.h"
using namespace std;

IMPLEMENT_DYNAMIC(CStudentTable, CRecordset)

CStudentTable::CStudentTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 11;
	m_nParams = 10;
	m_nDefaultType = dynaset;
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

void CStudentTable::LoadStudent(CStudentData& oStudent) 
{		
	Library oLib;
	oStudent.m_strFirstName = m_str_First_name;
	oStudent.m_strLastName = m_str_Last_name;
	oStudent.m_oleDTBirthday = oLib.CStringToDate(m_oleDT_Birthday);
	oStudent.m_strEmail= m_str_email;
	oStudent.m_strPhoneNumber = m_str_phone_number;
	oStudent.m_strEgn = m_str_egn;
	oStudent.m_strCity = m_str_city;
	oStudent.m_strPostCode = m_str_post_code;
	oStudent.m_strNeighborhood = m_str_neighborhood;
	oStudent.m_strAddress = m_str_address;
}

bool CStudentTable::IsExist(CStudentData& oStudent) 
{
		Library oLib;
		if (m_str_First_name == oStudent.m_strFirstName &&
			m_str_Last_name == oStudent.m_strLastName &&
			m_oleDT_Birthday == oLib.OleDTToCString(oStudent.m_oleDTBirthday) &&
			m_str_email == oStudent.m_strEmail &&
			m_str_phone_number == oStudent.m_strPhoneNumber &&
			m_str_egn == oStudent.m_strEgn &&
			m_str_city == oStudent.m_strCity &&
			m_str_post_code == oStudent.m_strPostCode &&
			m_str_neighborhood == oStudent.m_strNeighborhood &&
			m_str_address == oStudent.m_strAddress) { 
			return true;
			}
		
		return false;
}