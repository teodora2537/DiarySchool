// CSubjectTable.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CSubjectTable.h"
#include "afxdialogex.h"


// CSubjectTable dialog

IMPLEMENT_DYNAMIC(CSubjectTable, CRecordset)

CSubjectTable::CSubjectTable(CDatabase* pdb)
	: CDialogEx(IDD_DIALOG_UPDATE_SUBJECT)
	,CRecordset(pdb)
{
	m_nFields = 4;
	m_nParams = 4;
	m_nDefaultType = dynaset;
}

CSubjectTable::~CSubjectTable()
{
}

BEGIN_MESSAGE_MAP(CSubjectTable, CDialogEx)
END_MESSAGE_MAP()
void CSubjectTable::DoFieldExchange(CFieldExchange* pFX)
{
	__super::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Int(pFX, "[id]", m_iRoomNumber);
	RFX_Text(pFX, "[subject]", m_strNameSubject);
	RFX_Text(pFX, "[first_name_teacher]", m_strFNameTeacher);
	RFX_Text(pFX, "[last_name_teacher]", m_strLNameTeacher);

	pFX->SetFieldType(CFieldExchange::inputParam);
	RFX_Int(pFX, "[id]", m_iRoomNumber);
	RFX_Text(pFX, "[subject]", m_strNameSubject);
	RFX_Text(pFX, "[first_name_teacher]", m_strFNameTeacher);
	RFX_Text(pFX, "[last_name_teacher]", m_strLNameTeacher);
}

extern CDatabase g_dbConnection;

CString CSubjectTable::GetDefaultConnection()
{
	return g_dbConnection.GetConnect();
}

CString CSubjectTable::GetDefaultSQL()
{
	return "[Subject]";
}