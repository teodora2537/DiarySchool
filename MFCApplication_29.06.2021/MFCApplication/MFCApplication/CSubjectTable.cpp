#include "pch.h"
#include "MFCApplication.h"
#include "CSubjectTable.h"
#include "Subject.h"

IMPLEMENT_DYNAMIC(CSubjectTable, CRecordset)

CSubjectTable::CSubjectTable(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_nFields = 5;
	m_nParams = 5;
	m_nDefaultType = dynaset;
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
	RFX_Text(pFX, "[first_name_teacher]", m_strFNameTeacher);
	RFX_Text(pFX, "[last_name_teacher]", m_strLNameTeacher);
	RFX_Text(pFX, "[status]", m_strStatus);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[id]", m_iId);
	RFX_Text(pFX, "[subject]", m_strSubject);
	RFX_Text(pFX, "[first_name_teacher]", m_strFNameTeacher);
	RFX_Text(pFX, "[last_name_teacher]", m_strLNameTeacher);
	RFX_Text(pFX, "[status]", m_strStatus);
}

extern CDatabase g_dbConnection;

CString CSubjectTable::GetDefaultConnection() {
	return g_dbConnection.GetConnect();
}

CString CSubjectTable::GetDefaultSQL() {
	return "[Subject]";
}

void CSubjectTable::Add(CSubjectData& oSubject) 
{
	m_strSubject = oSubject.m_strSubject;
	m_strFNameTeacher = oSubject.m_strFNameTeacher;
	m_strLNameTeacher = oSubject.m_strLNameTeacher;
}

void CSubjectTable::EditSubject(CSubjectData& oSubject) 
{
	m_strSubject = oSubject.m_strSubject;
	m_strFNameTeacher = oSubject.m_strFNameTeacher;
	m_strLNameTeacher = oSubject.m_strLNameTeacher;
}

void CSubjectTable::DeleteSubject() {
	m_strStatus = "unactiv";
}

void CSubjectTable::Load(CSubjectData& oSubject) 
{
	oSubject.m_iId = m_iId;
	oSubject.m_strSubject = m_strSubject;
	oSubject.m_strFNameTeacher = m_strFNameTeacher;
	oSubject.m_strLNameTeacher = m_strLNameTeacher;
}

bool CSubjectTable::IsExist(CSubjectData& oSubject) 
{
		if (m_strSubject == oSubject.m_strSubject &&
			m_strFNameTeacher ==  oSubject.m_strFNameTeacher &&
			m_strLNameTeacher == oSubject.m_strLNameTeacher) {
				return true;
			}

	return false;
}