#include "pch.h"
#include "Score.h"
#include "CUpdateScore.h"
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

extern CDatabase g_dbConnection;

CScore::CScore()
{
}

CScore::~CScore()
{
}

bool CScore::AddScore(CScoreData& oScoreData)
{
	Library oLib;
	CString sqlString;
	CString isContains;
	
	CRecordset recset(&g_dbConnection);

	sqlString.Format("SELECT Count(id) as countStudent FROM Student WHERE id = '%d'", oScoreData.m_iClassNum);
	recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
	recset.GetFieldValue("countStudent", isContains);
	recset.Close();

	if (isContains == "0") {
		return false;
	}

	try 
	{
		CRecordset recset(&g_dbConnection);

		sqlString.Format("SELECT id FROM Subject WHERE subject = '%s';", oScoreData.m_strSubject);
		recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
		CString m_strIdSub;
		recset.GetFieldValue("id", m_strIdSub);

		sqlString.Format("INSERT INTO Score (student_id, subject_id, score, date_score) VALUES ('%d','%s','%d','%s');",
			oScoreData.m_iClassNum, m_strIdSub, oScoreData.m_iScore, oScoreData.m_strDate);

		g_dbConnection.ExecuteSQL(sqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}


	return true;
}

bool CScore::EditScore(const CScoreData& oScore) {
	Library oLib;
	CString sqlString;
	CString m_strIdSub;
	sqlString.Format( "SELECT Subject.id FROM Subject WHERE subject = '%s';", oScore.m_strSubject);

	try{
		CRecordset rs(&g_dbConnection);
		
		rs.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
		rs.GetFieldValue("id", m_strIdSub);

		sqlString.Format("UPDATE Score SET student_id ='%d', subject_id ='%s', score ='%d', date_score ='%s' WHERE id = '%d';", 
		oScore.m_iClassNum, m_strIdSub, oScore.m_iScore, oScore.m_strDate, oScore.m_iIdScore);

		g_dbConnection.ExecuteSQL(sqlString);
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
	CString sqlString;
	CString m_strIdStudent, m_strScore;
	CDBVariant varValueDate;
	CStudentData oStudent;

	sqlString.Format("SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id, Score.score, Score.date_score "
					"FROM Student "
					"INNER JOIN Score ON Score.student_id = Student.id "
					"INNER JOIN Subject ON Score.subject_id = Subject.id "
					"WHERE Score.id = '%d';", nIdScore);
	
	try{

		CRecordset recset(&g_dbConnection);
		
		recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);
	
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
	CString sqlString;

	sqlString.Format("DELETE FROM Score WHERE id = '%d';", nIdScore);

	try{

		CRecordset recset(&g_dbConnection);
		g_dbConnection.ExecuteSQL(sqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CScore::Print_Score(list<SCORE>& listScore)
{
	Library oLib;
	CString SqlString;
	CString m_strIdStudent, m_strSubject, m_strScore, m_strIdScore;
	CDBVariant varValueDate;
	CStudentData oStudent;
	
	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.id, Score.student_id, Score.score, Score.date_score "
				"FROM Student "
				"INNER JOIN Score ON Score.student_id = Student.id "
				"INNER JOIN Subject ON Score.subject_id = Subject.id;";
	
	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) {
			recset.GetFieldValue("first_name", oStudent.m_strFirstName);
			recset.GetFieldValue("last_name", oStudent.m_strLastName);
			recset.GetFieldValue("subject", m_strSubject);
			recset.GetFieldValue("id", m_strIdScore);
			recset.GetFieldValue("student_id", m_strIdStudent);
			recset.GetFieldValue("score", m_strScore);
			recset.GetFieldValue("date_score", varValueDate);

			SCORE scoreStruct;
			scoreStruct.iId = atoi(m_strIdScore);
			scoreStruct.iClassNum = atoi(m_strIdStudent);
			sprintf(scoreStruct.szName, "%s", oStudent.m_strFirstName + " " + oStudent.m_strLastName);
			sprintf(scoreStruct.szSubject, "%s", m_strSubject);
			scoreStruct.iScore = atoi(m_strScore);
			sprintf(scoreStruct.szDate, "%s", oLib.CDBVariantToCString(varValueDate));
			
			listScore.push_back(scoreStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}

//LOOK///
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

	//int test = (int)(GetItemData(nSelectedIndex));//защо го правим това
	
	return nSelectedIndex;
};