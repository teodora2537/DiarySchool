#include "pch.h"
#include "MFCApplication.h"
#include "CParentTable.h"
using namespace std;

IMPLEMENT_DYNAMIC(CParentTable, CRecordset)

CParentTable::CParentTable(CDatabase* pdb)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT)
	, CRecordset(pdb)
{
	m_nFields = 10;
	m_nParams = 9;
	m_nDefaultType = dynaset;
}

/*virtual*/
CParentTable::~CParentTable()
{
}

BEGIN_MESSAGE_MAP(CParentTable, CDialogEx)
END_MESSAGE_MAP()

/*virtual*/
void CParentTable::DoFieldExchange(CFieldExchange* pFX)
{
	__super::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, "[id]", m_iId);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Text(pFX, "[first_name]", m_str_first_name);
	RFX_Text(pFX, "[last_name]", m_str_last_name);
	RFX_Text(pFX, "[phone_number]", m_str_phone_number);
	RFX_Text(pFX, "[email]", m_str_email);
	RFX_Text(pFX, "[city]", m_str_city);
	RFX_Text(pFX, "[post_code]", m_str_post_code);
	RFX_Text(pFX, "[neighborhood]", m_str_neighborhood);
	RFX_Text(pFX, "[address]", m_str_address);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Text(pFX, "[first_name]", m_str_first_name);
	RFX_Text(pFX, "[last_name]", m_str_last_name);
	RFX_Text(pFX, "[phone_number]", m_str_phone_number);
	RFX_Text(pFX, "[email]", m_str_email);
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