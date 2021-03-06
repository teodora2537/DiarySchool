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

void CSubjectTable::Add_Edit(SUBJECT& stSubject) 
{
	m_strSubject = stSubject.szSubject;
	m_strFirstNameTeacher = stSubject.sz_First_Name;
	m_strLastNameTeacher = stSubject.sz_Last_Name;
}

void CSubjectTable::DeleteSubject() {
	m_strStatus = "unactiv";
}

void CSubjectTable::Load(CSubjectData& oSubject) 
{
	oSubject.m_iId = m_iId;
	oSubject.m_strSubject = m_strSubject;
	oSubject.m_strFirstNameTeacher = m_strFirstNameTeacher;
	oSubject.m_strLastNameTeacher = m_strLastNameTeacher;
}

bool CSubjectTable::IsExist(CSubjectData& oSubject) 
{
		if (m_strSubject == oSubject.m_strSubject &&
			m_strFirstNameTeacher ==  oSubject.m_strFirstNameTeacher &&
			m_strLastNameTeacher == oSubject.m_strLastNameTeacher) {
				return true;
			}

	return false;
}