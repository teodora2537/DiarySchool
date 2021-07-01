#include "pch.h"
#include "MFCApplication.h"
#include "CScoreTable.h"
#include "Score.h"
#include "Library.h"

IMPLEMENT_DYNAMIC(CScoreTable, CRecordset)

CScoreTable::CScoreTable(CDatabase* pdb)
	:CRecordset(pdb)
{
	m_nFields = 5;
	m_nParams = 4;
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
	RFX_Text(pFX, "[date_score]", m_oleDateTime);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[student_id]", m_iIdStudent);
	RFX_Int(pFX, "[subject_id]", m_iIdSubject);
	RFX_Int(pFX, "[score]", m_iScore);
	RFX_Text(pFX, "[date_score]", m_oleDateTime);

}

extern CDatabase g_dbConnection;

CString CScoreTable::GetDefaultConnection() {
	return g_dbConnection.GetConnect();
}

CString CScoreTable::GetDefaultSQL() {
	return "[Score]";
}

void CScoreTable::Add_Edit_Score(SCORE& stScore) 
{
	m_iIdStudent = stScore.iIdStudent;
	m_iIdSubject = stScore.iIdSubject;
	m_iScore = stScore.iScore;
	m_oleDateTime = stScore.szDate;
}

void CScoreTable::Load(CScoreData& oScore) 
{
	Library oLib;
	oScore.m_iIdStudent = m_iIdStudent;
	oScore.m_iIdSubject = m_iIdSubject;
	oScore.m_iScore = m_iScore;
	oScore.m_oleDateTime = oLib.CStringToDate(m_oleDateTime);
}