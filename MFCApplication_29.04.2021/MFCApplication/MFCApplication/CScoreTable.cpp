#include "pch.h"
#include "MFCApplication.h"
#include "CScoreTable.h"

// CScoreTable dialog

IMPLEMENT_DYNAMIC(CScoreTable, CRecordset)

CScoreTable::CScoreTable(CDatabase* pdb)
	: CDialogEx(IDD_DIALOG_UPDATE_SCORE)
	, CRecordset(pdb)
{
	m_iIdScore = 0;
	m_iIdStudent = 0;
	m_iIdSubject = 0;
	m_iScore = 0;

	m_nFields = 5;
	m_nParams = 5;
	m_nDefaultType = dynaset;
}

CScoreTable::~CScoreTable()
{
}

void CScoreTable::DoFieldExchange(CFieldExchange* pFX)
{
	__super::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, "[id]", m_iIdScore);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Int(pFX, "[subject_id]", m_iIdSubject);
	RFX_Int(pFX, "[score]", m_iScore);
	RFX_Date(pFX, "[date_score]", m_oleDateTime);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[id]", m_iIdScore);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Int(pFX, "[subject_id]", m_iIdSubject);
	RFX_Int(pFX, "[score]", m_iScore);
	RFX_Date(pFX, "[date_score]", m_oleDateTime);

}

extern CDatabase g_dbConnection;

CString CScoreTable::GetDefaultConnection()
{
	return g_dbConnection.GetConnect();
}

CString CScoreTable::GetDefaultSQL()
{
	return "[Score]";
}

BEGIN_MESSAGE_MAP(CScoreTable, CDialogEx)
END_MESSAGE_MAP()
