#include "pch.h"
#include "MFCApplication.h"
#include "CScoreTable.h"


IMPLEMENT_DYNAMIC(CScoreTable, CRecordset)

CScoreTable::CScoreTable(CDatabase* pdb)
	:CRecordset(pdb)
{
	m_nFields = 5;
	m_nParams = 4;
	m_nDefaultType = dynaset;

	m_iIdScore = 0;
	m_iIdStudent = 0;
	m_iIdSubject = 0;
	m_iScore = 0;
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

void CScoreTable::GetRecStruct(SCORE& oScore)
{
	Library oLib;
	oScore.iIdScore = m_iIdScore;
	oScore.iIdStudent = m_iIdStudent;
	oScore.iIdSubject = m_iIdSubject;
	oScore.iScore = m_iScore;	
	strcpy_s(oScore.szDate, CStringA(m_oleDateTime).GetString());
}

void CScoreTable::Add_Edit_Score(SCORE& stScore) 
{
	m_iIdStudent = stScore.iIdStudent;
	m_iIdSubject = stScore.iIdSubject;
	m_iScore = stScore.iScore;
	m_oleDateTime = stScore.szDate;
}

BOOL CScoreTable::AddRec(SCORE& recScore)
{
	if (!Open())
	{
		MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	if (!CanAppend())
	{
		MessageBox(NULL, "The table score can't append!", "Can't append", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	AddNew();

	Add_Edit_Score(recScore);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return FALSE;
	}

	Close();

	return TRUE;
}

BOOL CScoreTable::IsEquals(SCORE& obj1, SCORE& obj2)
{
	if (obj1.iIdSubject != obj2.iIdSubject)
		return FALSE;
	if (obj1.iScore != obj2.iScore)
		return FALSE;
	if (obj1.szDate != obj2.szDate)
		return FALSE;


	return TRUE;
}


BOOL CScoreTable::EditRec(SCORE& recScore)
{
	m_strFilter.Format("id = '%d'", recScore.iIdScore);

	if (!Open())
	{
		MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	if (!CanUpdate())
	{
		MessageBox(NULL, "The table score can't update!", "Can't update", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	Edit();

	SCORE recordScore;

	GetRecStruct(recordScore);

	if (IsEquals(recordScore, recScore))
	{
		Close();
		return true;
	}

	SCORE stScore;

	stScore = recScore;

	//if (memcmp(&recordScore, &stScore, sizeof(recordScore)))
	//{
	//	Close();
	//	return true;
	//}

	//stParent = recParent;

	Add_Edit_Score(stScore);

	if (!Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);

		g_dbConnection.Rollback();
		Close();

		return false;
	}

	Close();

	return TRUE;
}

BOOL CScoreTable::DeleteRec(SCORE& recScore)
{
	try
	{
		m_strFilter.Format("id = '%d'", recScore.iIdScore);

		if (!Open())
		{
			MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		if (!IsOpen())
		{
			MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			Close();
			return FALSE;
		}

		Delete();

		if (!IsDeleted())
		{
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			Close();

			return FALSE;
		}

		Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete score!", MB_ICONEXCLAMATION);

		return FALSE;
	}

	return TRUE;
}

BOOL CScoreTable::LoadScore(SCORE& recScore) 
{
	m_strFilter.Format("id = '%d'", recScore.iIdScore);

	if (!Open())
	{
		MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();
		return FALSE;
	}

	if (!IsOpen())
	{
		MessageBox(NULL, "The table score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		Close();

		return false;
	}

	GetRecStruct(recScore);

	Close();

	return true;
}