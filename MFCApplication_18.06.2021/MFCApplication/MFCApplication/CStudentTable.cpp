#include "pch.h"
#include "MFCApplication.h"
#include "CStudentTable.h"
using namespace std;

IMPLEMENT_DYNAMIC(CStudentTable, CRecordset)

CStudentTable::CStudentTable(CDatabase* pdb)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT)
	,CRecordset(pdb)
{
	//m_iCountStudent = 0;
	m_nFields = 11;
	m_nParams = 10;
	m_nDefaultType = dynaset;
}

/*virtual*/
CStudentTable::~CStudentTable()
{
}

BEGIN_MESSAGE_MAP(CStudentTable, CDialogEx)
END_MESSAGE_MAP()

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