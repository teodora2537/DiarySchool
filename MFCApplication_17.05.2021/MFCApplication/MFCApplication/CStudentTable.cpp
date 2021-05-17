#include "pch.h"
#include "MFCApplication.h"
#include "CStudentTable.h"
using namespace std;

IMPLEMENT_DYNAMIC(CStudentTable, CRecordset)

CStudentTable::CStudentTable(CDatabase* pdb)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT)
	,CRecordset(pdb)
{
	m_iCountStudent = 0;
	m_nFields = 4;
	m_nParams = 4;
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
	RFX_Text(pFX, "[id]", m_str_IdStudent);
	RFX_Text(pFX, "[first_name]", m_str_First_name);
	RFX_Text(pFX, "[last_name]", m_str_Last_name);
	RFX_Date(pFX, "[birth_date]", m_oleDT_Birthday);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Text(pFX, "[id]", m_str_IdStudent);
	RFX_Text(pFX, "[first_name]", m_str_First_name);
	RFX_Text(pFX, "[last_name]", m_str_Last_name);
	RFX_Date(pFX, "[birth_date]", m_oleDT_Birthday);
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