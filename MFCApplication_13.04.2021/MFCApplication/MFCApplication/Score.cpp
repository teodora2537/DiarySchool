#include "pch.h"
#include "Score.h"
using namespace std;

CScoreData::CScoreData(int _idScore, int _classNum, CString _subject, int _score, CString _date)
{
	m_iIdScore = _idScore;
	m_iClassNum = _classNum;
	m_strSubject = _subject;
	m_iScore = _score;
	m_strDate = _date;
}

CScoreData::CScoreData()
{
}

extern CDatabase db;

CScore::CScore()
{
}

CScore::~CScore()
{
}

	
bool CScore::AddScore(CScoreData& oScoreData)
{
	Library oLib;
	CString SqlString;

	try 
	{
		// Allocate the recordset
		CRecordset recset(&db);

		SqlString = "SELECT id FROM Subject WHERE subject = '" + oScoreData.m_strSubject + "';";
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
		CString m_strIdSub;
		recset.GetFieldValue("id", m_strIdSub);

		SqlString = "INSERT INTO Score (student_id, subject_id, score, date_score) VALUES ('" + oLib.IntToCString(oScoreData.m_iClassNum) + "','" + m_strIdSub + "','" + oLib.IntToCString(oScoreData.m_iScore) + "','" + oScoreData.m_strDate + "');";

		db.ExecuteSQL(SqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}


	return true;
}

bool CScore::EditScore(const CScoreData& oScore) {
	Library oLib;
	CString SqlString = "SELECT Subject.id FROM Subject WHERE subject = '"+ oScore.m_strSubject+"';";
	CString m_strIdSub;

	try{
	CRecordset rs(&db);
	
	rs.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	rs.GetFieldValue("id", m_strIdSub);

	db.ExecuteSQL("UPDATE Score SET student_id ='" + oLib.IntToCString(oScore.m_iClassNum) + "' WHERE id = '" + oLib.IntToCString(oScore.m_iIdScore) + "';");
	db.ExecuteSQL("UPDATE Score SET subject_id ='" + m_strIdSub + "' WHERE id = '" + oLib.IntToCString(oScore.m_iIdScore) + "';");
	db.ExecuteSQL("UPDATE Score SET score ='" + oLib.IntToCString(oScore.m_iScore) + "' WHERE id = '" + oLib.IntToCString(oScore.m_iIdScore) + "';");
	db.ExecuteSQL("UPDATE Score SET date_score ='" + oScore.m_strDate + "' WHERE id = '" + oLib.IntToCString(oScore.m_iIdScore) + "';");
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	
	return true;
}

bool CScore::LoadScore(const int nIdScore, CScoreData& oScore)
{
	Library oLib;
	CString SqlString;
	CString m_strIdStudent, m_strScore;
	CDBVariant varValueDate;
	CStudentData oStudent;

		SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id, Score.score, Score.date_score FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id WHERE Score.id = '"+oLib.IntToCString(nIdScore)+"';";
	
		try{

			CRecordset recset(&db);
			
			recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
			recset.GetFieldValue("first_name", oStudent.m_strFirstName);
			recset.GetFieldValue("last_name", oStudent.m_strLastName);
			recset.GetFieldValue("subject", oScore.m_strSubject);
			recset.GetFieldValue("student_id", m_strIdStudent);
			recset.GetFieldValue("score", m_strScore);
			recset.GetFieldValue("date_score", varValueDate);
	
			oScore.m_strNameStudent = oStudent.m_strFirstName + " " + oStudent.m_strLastName;
			oScore.m_iClassNum = atoi(m_strIdStudent);
			oScore.m_iScore = atoi(m_strScore);
			oScore.m_strDate = oLib.CDBVariantToCString(varValueDate);
			oScore.m_iIdScore = nIdScore;
		}
		catch (exception e)
		{
			AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		}
	return true;
}

bool CScore::DeleteScore(const int nIdScore)
{
	Library oLib;

	try{

		CRecordset recset(&db);
		db.ExecuteSQL("DELETE FROM Score WHERE id = '" + oLib.IntToCString(nIdScore) + "';");
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CScore::Print_Score(list<ScoreStruct>& listScore)
{
	Library oLib;
	CString SqlString;
	CString m_strIdStudent, m_strSubject, m_strScore, m_strIdScore;
	CDBVariant varValueDate;
	CStudentData oStudent;
	
	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.id, Score.student_id, Score.score, Score.date_score FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id;";
	
	try {
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) {
			recset.GetFieldValue("first_name", oStudent.m_strFirstName);
			recset.GetFieldValue("last_name", oStudent.m_strLastName);
			recset.GetFieldValue("subject", m_strSubject);
			recset.GetFieldValue("id", m_strIdScore);
			recset.GetFieldValue("student_id", m_strIdStudent);
			recset.GetFieldValue("score", m_strScore);
			recset.GetFieldValue("date_score", varValueDate);

			ScoreStruct scoreStruct;
			scoreStruct.nIdStudent = atoi(m_strIdStudent);
			scoreStruct.strNameStudent = oStudent.m_strFirstName + " " + oStudent.m_strLastName;
			scoreStruct.strSubject = m_strSubject;
			scoreStruct.nIdScore = atoi(m_strIdScore);
			scoreStruct.strScore = m_strScore;
			scoreStruct.strDate = oLib.CDBVariantToCString(varValueDate);
			listScore.push_back(scoreStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}
