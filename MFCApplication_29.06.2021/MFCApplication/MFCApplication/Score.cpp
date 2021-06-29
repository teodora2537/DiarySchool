#include "pch.h"
#include "Score.h"
#include "CUpdateScore.h"
#include "CScoreTable.h"
#include "CSubjectTable.h"
#include "CStudentTable.h"
using namespace std;

CScoreData::CScoreData(int _idScore, int _classNum, CString _subject, int _score, COleDateTime _date)
{
	m_iIdScore = _idScore;
	m_iIdStudent = _classNum;
	m_strSubject = _subject;
	m_iScore = _score;
	m_oleDateTime = _date;
}

CScoreData::CScoreData()
{}

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

			return false;
		}

		if (!oStudentTable.m_iId) 
		{
			MessageBox(NULL, "The student isn't exist!", "Isn't exist", MB_OK | MB_ICONERROR);
			oStudentTable.Close();
			
			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		
		return false;
	}

	return true;
}

//Get id subject
bool CScore::GetIdSubject(CString& strSubject, int& m_strIdSub)
{
	try 
	{
		//get id subject
		CString strWhere;
		strWhere.Format("subject = '%s';", strSubject);
		
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter = strWhere;
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen()) 
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			
			return false;
		}

		m_strIdSub = oSubjectTable.m_iId;
		oSubjectTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete subject!", MB_ICONEXCLAMATION);
		
		return false;
	}
	return true;
}

bool CScore::AddScore(CScoreData& oScoreData)
{
	// is valid id student
	if (!IsContainAStudent(oScoreData))	{
		return false;
	}
	
	try 
	{
		//Get id subject
		int nIdSub;
		if (!GetIdSubject(oScoreData.m_strSubject, nIdSub)) {
			return false;
		}

		//Add score
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.Open();

		if (!oScoreTable.IsOpen()) {
			MessageBox(NULL, "The table Score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oScoreTable.Close();
			return false;
		}

		if (!oScoreTable.CanAppend()) 
		{
			MessageBox(NULL, "The record can't append!", "Can't append", MB_OK | MB_ICONERROR);
			oScoreTable.Close();
			
			return false;
		}

		oScoreTable.AddNew();
		Library oLib;
		oScoreTable.m_iIdStudent = oScoreData.m_iIdStudent;
		oScoreTable.m_iIdSubject = nIdSub;
		oScoreTable.m_iScore = oScoreData.m_iScore;
		//oScoreTable.m_oleDateTime = oScoreData.m_oleDateTime;
		oScoreTable.m_oleDateTime = oLib.OleDTToCString(oScoreData.m_oleDateTime);
		
		if (!oScoreTable.Update()) 
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			oScoreTable.Close();
			
			return false;
		}

		 oScoreTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

bool CScore::EditScore(CScoreData& oScore) {
		
	try 
	{
		//get id subject
		int nIdSub;
		GetIdSubject(oScore.m_strSubject, nIdSub);

		CString strWhere;
		strWhere.Format("id = '%d'", oScore.m_iIdScore);
		
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.m_strFilter = strWhere;
		oScoreTable.Open();
	
		if (!oScoreTable.IsOpen()) 
		{
			MessageBox(NULL, "The table Score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return false;
		}

		oScoreTable.Edit();
		Library oLib;
		oScoreTable.m_iIdStudent = oScore.m_iIdStudent;
		oScoreTable.m_iIdSubject = nIdSub;
		oScoreTable.m_iScore = oScore.m_iScore;
		//oScoreTable.m_oleDateTime = oScore.m_oleDateTime;
		oScoreTable.m_oleDateTime = oLib.OleDTToCString(oScore.m_oleDateTime);

		if (!oScoreTable.Update())
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

bool CScore::DeleteScore(const int nIdScore)
{
	try
	{
		CString strWhere;
		strWhere.Format("id = '%d'", nIdScore);
		
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.m_strFilter = strWhere;
		oScoreTable.Open();
		
		if (!oScoreTable.IsOpen())
		{
			MessageBox(NULL, "The table Score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return false;
		}

		oScoreTable.Delete();
		
		if (!oScoreTable.IsDeleted())
		{
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete score!", MB_ICONEXCLAMATION);
		return false;
	}
	return true;
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
			return false;
		}
		while (!oScoreTable.IsEOF())
		{
			oScoreTable.Delete();
			oScoreTable.MoveNext();
		}

		if (!oScoreTable.IsDeleted())
		{
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			oScoreTable.Close();

			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete student!", MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

//get student name
void CScore::GetStudentName(CScoreData& oScore)
{
	try 
	{
		CString strWhere;
		strWhere.Format("id = '%d'", oScore.m_iIdStudent);
		
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter = strWhere;
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

//get subject
void CScore::GetSubject(CScoreData& oScore)
{

	try 
	{	
		CString strWhere;
		strWhere.Format("id = '%d'", oScore.m_iIdSubject);
		
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter = strWhere;
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
		//get score
		CString strWhere;
		strWhere.Format("id = '%d'", nIdScore);
		
		CScoreTable oScoreTable(&g_dbConnection);
		oScoreTable.m_strFilter = strWhere;
		oScoreTable.Open();

		if (!oScoreTable.IsOpen())
		{
			MessageBox(NULL, "The table Score isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oScoreTable.Close();
			
			return false;
		}
		Library oLib;
		oScore.m_iIdStudent = oScoreTable.m_iIdStudent;
		oScore.m_iIdSubject = oScoreTable.m_iIdSubject;
		oScore.m_iScore = oScoreTable.m_iScore;
		oScore.m_oleDateTime = oLib.CStringToDate(oScoreTable.m_oleDateTime);
		oScoreTable.Close();

		//get student name
		GetStudentName(oScore);

		//get subject
		GetSubject(oScore);
	}
	catch (exception e)
	{
		AfxMessageBox("Error load score!", MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

void CScore::Print_Score(list<SCORE>& listScore)
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
		
		while (!oScoreTable.IsEOF()) {
		
			oScoreData.m_iIdStudent = oScoreTable.m_iIdStudent;
			GetStudentName(oScoreData);
			oScoreData.m_iIdSubject = oScoreTable.m_iIdSubject;
			GetSubject(oScoreData);

			SCORE scoreStruct;
			scoreStruct.iId = oScoreTable.m_iIdScore;
			scoreStruct.iClassNum = oScoreTable.m_iIdStudent;
			sprintf(scoreStruct.szName, "%s", oScoreData.m_strNameStudent);
			sprintf(scoreStruct.szSubject, "%s", oScoreData.m_strSubject);
			scoreStruct.iScore = oScoreTable.m_iScore;
			sprintf(scoreStruct.szDate, "%s", oScoreTable.m_oleDateTime);

			listScore.push_back(scoreStruct);

			oScoreTable.MoveNext();
		}

		oScoreTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error load scors!", MB_ICONEXCLAMATION);
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

void CScore::GetLastId(CScoreData& oScore) {
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
	catch (exception e) {
		AfxMessageBox("Don't get last id of student!", MB_ICONEXCLAMATION);
	}
}