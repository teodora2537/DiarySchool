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
{
}

extern CDatabase g_dbConnection;

CScore::CScore()
{
}

CScore::~CScore()
{
}

	// is valid id student
bool IsContainAStudent(CScoreData& oScoreData)
{	
	CString sqlString;
	CString isContains;
	CRecordset recset(&g_dbConnection);
	sqlString.Format("SELECT Count(id) as countStudent FROM Student WHERE id = '%d'", oScoreData.m_iIdStudent);
	recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
	recset.GetFieldValue("countStudent", isContains);
	recset.Close();

	if (isContains == "0")
		return false;
	return true;
}

//Get id subject
void GetIdSubject(CString& strSubject, int& m_strIdSub)
{
	//get id subject
	CString whereClause;
	CSubjectTable recsetSub(&g_dbConnection);
	whereClause.Format("subject = '%s';", strSubject);
	recsetSub.m_strFilter = whereClause;
	recsetSub.Open();
	m_strIdSub = recsetSub.m_iRoomNumber;
	recsetSub.Close();
}

bool CScore::AddScore(CScoreData& oScoreData)
{
	// is valid id student
	if (!IsContainAStudent(oScoreData)) {
		return false;
	}

	try 
	{
		//Get id subject
		int nIdSub;
		GetIdSubject(oScoreData.m_strSubject, nIdSub);

		//Add score
		CScoreTable recsetScore(&g_dbConnection);
		recsetScore.Open();
		recsetScore.AddNew();

		recsetScore.m_iIdStudent = oScoreData.m_iIdStudent;
		recsetScore.m_iIdSubject = nIdSub;
		recsetScore.m_iScore = oScoreData.m_iScore;
		recsetScore.m_oleDateTime = oScoreData.m_oleDateTime;
		
	if (!recsetScore.Update())
			return false;

		recsetScore.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}

	return true;
}

bool CScore::EditScore(CScoreData& oScore) {
	

	try {
		CString whereClause;
		CScoreTable recset(&g_dbConnection);
		
		//get id subject
		int nIdSub;
		GetIdSubject(oScore.m_strSubject, nIdSub);

		whereClause.Format("id = '%d'", oScore.m_iIdScore);
		recset.m_strFilter = whereClause;
		recset.Open();
		recset.Edit();

		recset.m_iIdStudent = oScore.m_iIdStudent;
		recset.m_iIdSubject = nIdSub;
		recset.m_iScore = oScore.m_iScore;
		recset.m_oleDateTime = oScore.m_oleDateTime;

		if (!recset.Update()) {
			AfxMessageBox("Record not updated; no fiels values were set.");
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

bool CScore::DeleteScore(const int nIdScore)
{
	CScoreTable recset(&g_dbConnection);
	CString whereClause;
	whereClause.Format("id = '%d'", nIdScore);
	recset.m_strFilter = whereClause;
	try
	{
		recset.Open();
		recset.Delete();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete score!", MB_ICONEXCLAMATION);
	}
	return true;
}

//get student name
void GetStudentName(CScoreData& oScore)
{
	CString whereClause;
	whereClause.Format("id = '%d'", oScore.m_iIdStudent);
	CStudentTable recsetStudent(&g_dbConnection);
	recsetStudent.m_strFilter = whereClause;
	recsetStudent.Open();
	oScore.m_strNameStudent = recsetStudent.m_str_First_name + " " + recsetStudent.m_str_Last_name;
	recsetStudent.Close();
}

//get subject
void GetSubject(CScoreData& oScore)
{
	CString whereClause;
	whereClause.Format("id = '%d'", oScore.m_iIdSubject);
	CSubjectTable recsetSubject(&g_dbConnection);
	recsetSubject.m_strFilter = whereClause;
	recsetSubject.Open();
	oScore.m_strSubject = recsetSubject.m_strNameSubject;
	recsetSubject.Close();
}

bool CScore::LoadScore(const int nIdScore, CScoreData& oScore)
{
	try {
		//get score
		CString whereClause;
		whereClause.Format("id = '%d'", nIdScore);
		CScoreTable recsetScore(&g_dbConnection);
		recsetScore.m_strFilter = whereClause;
		recsetScore.Open();

		oScore.m_iIdStudent = recsetScore.m_iIdStudent;
		oScore.m_iIdSubject = recsetScore.m_iIdSubject;
		oScore.m_iScore = recsetScore.m_iScore;
		oScore.m_oleDateTime = recsetScore.m_oleDateTime;
		recsetScore.Close();

		//get student name
		GetStudentName(oScore);

		//get subject
		GetSubject(oScore);
	}
	catch (exception e)
	{
		AfxMessageBox("Error load score!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CScore::Print_Score(list<SCORE>& listScore)
{
	Library oLib;
	CScoreData oScoreData;

	try 
	{
		CScoreTable recset(&g_dbConnection);
		recset.Open();

	
		while (!recset.IsEOF()) {
		
			oScoreData.m_iIdStudent = recset.m_iIdStudent;
			GetStudentName(oScoreData);
			oScoreData.m_iIdSubject = recset.m_iIdSubject;
			GetSubject(oScoreData);

			SCORE scoreStruct;
			scoreStruct.iId = recset.m_iIdScore;
			scoreStruct.iClassNum = recset.m_iIdStudent;
			sprintf(scoreStruct.szName, "%s", oScoreData.m_strNameStudent);
			sprintf(scoreStruct.szSubject, "%s", oScoreData.m_strSubject);
			scoreStruct.iScore = recset.m_iScore;
			sprintf(scoreStruct.szDate, "%s", oLib.OleDTToCString(recset.m_oleDateTime));

			listScore.push_back(scoreStruct);

			recset.MoveNext();
		}
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