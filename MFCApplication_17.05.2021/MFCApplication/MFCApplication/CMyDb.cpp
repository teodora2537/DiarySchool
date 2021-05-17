#include "pch.h"
#include "CMyDb.h"
#include "Library.h"
using namespace std;

IMPLEMENT_DYNAMIC(CMyDb, CRecordset)

CMyDb::CMyDb(CDatabase* pdb)
	:CRecordset(pdb)
{
	m_strClassNum = "";
	m_strFn = "";
	m_strLn = "";
	m_strClassNum = "";
	m_strBirthday = ""; 
}
void CMyDb::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
	Library oLib;
	RFX_Text(pFX, "[first_name]", m_strFn);
	RFX_Text(pFX, "[last_name]", m_strLn);
	RFX_Date(pFX, "[birth_date]", oLib.CStringToDate(m_strBirthday));
}
