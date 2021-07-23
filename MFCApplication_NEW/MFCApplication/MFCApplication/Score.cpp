#include "pch.h"
#include "Score.h"
#include "CUpdateScore.h"
#include "CScoreTable.h"
#include "CSubjectTable.h"
#include "CStudentTable.h"

CScoreData::CScoreData()
{
	m_iIdScore = 0;
	m_iIdStudent = 0;
	m_iIdSubject = 0;
	m_iScore = 0;
	m_oleDateTime = COleDateTime::GetCurrentTime();
}

extern CDatabase g_dbConnection;

CScore::CScore()
{
}

CScore::~CScore()
{
}

// is valid id student
bool CScore::IsContainAStudent(CScoreData& oScoreData)
{	
	try 
	{
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter.Format("id = '%d'", oScoreData.m_iIdStudent);
		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen()) 
		{
			MessageBox(NULL, "The table Score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oStudentTable.Close();

			return FALSE;
		}

		if (oStudentTable.GetRecordCount() < 1)
		{
			MessageBox(NULL, "The student isn't exist!", "Isn't exist", MB_OK | MB_ICONERROR);
			oStudentTable.Close();
			
			return FALSE;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

//Get id subject
bool CScore::GetIdSubject(CScoreData& oScore)
{
	try 
	{
		//get id subject
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter.Format("subject = '%s';", oScore.m_strSubject);
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen()) 
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return FALSE;
		}

		oScore.m_iIdSubject = oSubjectTable.m_iId;
		oSubjectTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete subject!", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

void FillStructWithObjectData(SCORE& stScore, CScoreData& oScore)
{
	Library oLib;
	stScore.iIdStudent = oScore.m_iIdStudent;
	stScore.iIdSubject = oScore.m_iIdSubject;
	stScore.iScore = oScore.m_iScore;
	strcpy_s(stScore.szDate, CStringA(oLib.ChangeSingleDate(oScore.m_oleDateTime)).GetString());
}


bool CScore::AddScore(CScoreData& oScoreData)
{
	// is valid id student
	if (!IsContainAStudent(oScoreData))	{
		return FALSE;
	}
	
	try 
	{
		//Get id subject
		if (!GetIdSubject(oScoreData)) {
			return FALSE;
		}

		//Add score
		CScoreTable oScoreTable(&g_dbConnection);
		
		SCORE stScore;
		FillStructWithObjectData(stScore, oScoreData);

		if (!oScoreTable.AddRec(stScore))
		{
			MessageBox(NULL, "The record can't added!", "Can't added", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return FALSE;
		}
		 oScoreTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

bool CScore::EditScore(CScoreData& oScore) 
{		
	try 
	{
		//get id subject
		GetIdSubject(oScore);
		CScoreTable oScoreTable(&g_dbConnection);

		SCORE stScore;
		stScore.iIdScore = oScore.m_iIdScore;

		FillStructWithObjectData(stScore, oScore);

		if (!oScoreTable.EditRec(stScore))
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			oScoreTable.Close();
			return FALSE;
		}
			oScoreTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

bool CScore::DeleteScore(const int nIdScore)
{
	try
	{
		CScoreTable oScoreTable(&g_dbConnection);

		SCORE stScore;
		stScore.iIdScore = nIdScore;

		if (!oScoreTable.DeleteRec(stScore))
		{
			MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
			oScoreTable.Close();
			return FALSE;
		}

		oScoreTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete score!", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

bool CScore::DeleteScoreByStudent(int nIdStudent) 
{
	try
	{
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.m_strFilter.Format("student_id = '%d'", nIdStudent);
		
		oScoreTable.Open();

		if (!oScoreTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return FALSE;
		}

		if (oScoreTable.GetRecordCount() == 0)
			return TRUE;
		
		while (!oScoreTable.IsEOF())
		{
			oScoreTable.Delete();
			oScoreTable.MoveNext();
		}

		if (!oScoreTable.IsDeleted())
		{
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return FALSE;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete student!", MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

//get student name
void CScore::GetStudentName(CScoreData& oScore)
{
	try 
	{
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter.Format("id = '%d'", oScore.m_iIdStudent);
	
		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oStudentTable.Close();
			return;
		}

		oScore.m_strNameStudent = oStudentTable.m_str_First_name + " " + oStudentTable.m_str_Last_name;
		oStudentTable.Close();
	}
	catch (exception e) 
	{
		AfxMessageBox("Error get student!", MB_ICONERROR);
		return;
	}
}

//get subject name
void CScore::GetSubject(CScoreData& oScore)
{
	try 
	{	
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter.Format("id = '%d'", oScore.m_iIdSubject);
		
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen())
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return;
		}
		oScore.m_strSubject = oSubjectTable.m_strSubject;
		oSubjectTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error get subject!", MB_ICONEXCLAMATION);
		return;
	}
}

bool CScore::LoadScore(const int nIdScore, CScoreData& oScore)
{
	try {
		CScoreTable oScoreTable(&g_dbConnection);

		SCORE recScore;
		recScore.iIdScore = nIdScore;
		oScoreTable.LoadScore(recScore);

		Library oLib;
		oScore.m_iIdScore =	recScore.iIdScore;
		oScore.m_iIdStudent = recScore.iIdStudent;
		oScore.m_iIdSubject = recScore.iIdSubject;
		oScore.m_iScore = recScore.iScore;
		oScore.m_oleDateTime = oLib.CStringToDate(recScore.szDate);

		oScoreTable.Close();

		//get student name
		GetStudentName(oScore);

		//get subject
		GetSubject(oScore);
	}
	catch (exception e)
	{
		AfxMessageBox("Error load score!", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
}

void CScore::Print_Score(list<CScoreData>& listScore)
{
	try 
	{
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.Open();

		if (!oScoreTable.IsOpen())
		{
			MessageBox(NULL, "The table Score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		Library oLib;
		CScoreData oScoreData;
		
		while (!oScoreTable.IsEOF()) 
		{
			oScoreData.m_iIdStudent = oScoreTable.m_iIdStudent;
			GetStudentName(oScoreData);
			oScoreData.m_iIdSubject = oScoreTable.m_iIdSubject;
			GetSubject(oScoreData);

			CScoreData oScore;
			oScore.m_iIdScore = oScoreTable.m_iIdScore;
			oScore.m_iIdStudent = oScoreTable.m_iIdStudent;
			oScore.m_iIdSubject = oScoreTable.m_iIdSubject;
			oScore.m_iScore = oScoreTable.m_iScore;
			oScore.m_oleDateTime = oLib.CStringToDate(oScoreTable.m_oleDateTime);
			GetStudentName(oScore);
			GetSubject(oScore);

			listScore.push_back(oScore);

			oScoreTable.MoveNext();
		}

		oScoreTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error load scors!", MB_ICONEXCLAMATION);
		return;
	}
}

void CMyComboBox::LoadData(const CArray<COMBO_DATA>& arrData, CComboBox& m_combo)
{
	m_combo.ResetContent();

	for (int i = 0; i < arrData.GetSize(); i++)
	{
		int nItenmIndex = m_combo.AddString(arrData[i].szName);
		m_combo.SetItemData(nItenmIndex, arrData[i].nID);
	}
}

int CMyComboBox::GetSelectedValue(CComboBox& m_combo) const
{
	int nSelectedIndex = m_combo.GetCurSel();

	if (nSelectedIndex == CB_ERR)
		return CB_ERR;

	return (int)(m_combo.GetItemData(nSelectedIndex));
};

void CScore::GetLastId(CScoreData& oScore) 
{
	try
	{
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.Open();

		if (!oScoreTable.IsOpen())
		{
			MessageBox(NULL, "The Score table isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return;
		}

		oScoreTable.MoveLast();
		oScore.m_iIdScore = oScoreTable.m_iIdScore + 1;
		
		oScoreTable.Close();
	}
	catch (exception e) 
	{
		AfxMessageBox("Don't get last id of student!", MB_ICONEXCLAMATION);
		return;
	}
}