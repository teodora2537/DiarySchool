#include "pch.h"
#include "Student.h"
#include "CStudentTable.h"
#include "CUpdateStudent.h"
#include <afxwin.h>
using namespace std;

CStudentData::CStudentData(int _classNum, CString _fName, CString _lName, COleDateTime _birthday)
{
	m_iClassNumber = _classNum;
	m_strFirstName = _fName;
	m_strLastName = _lName;
	m_strBirthday = _birthday;
}

CStudentData::CStudentData()
{
}

CStudent::CStudent()
{
}

CDatabase g_dbConnection;

BOOL CWinApp::InitInstance()
{
		CString ConnectionString= "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";
		
		try 
		{
			g_dbConnection.Open(NULL, FALSE, FALSE, ConnectionString, TRUE);
		} 
		catch (CDBException* e)
		{
			AfxMessageBox(e->m_strError, MB_ICONEXCLAMATION);
			e->Delete();
		}
	
	 return TRUE;
}

	/*virtual*/
CStudent::~CStudent()
{
}

bool CStudent::AddStudent(CStudentData& oStudent)
{
	////////////////////////////////////
	Library oLib;
	
	try {
	CStudentTable recset(&g_dbConnection);
	recset.Open(CRecordset::dynaset, "SELECT * FROM Student", CRecordset::none);
	
	if (!recset.CanAppend())
		return false;

	if (!recset.CanUpdate())
		return false;

		recset.AddNew(); // ERROR
		recset.m_strFn = oStudent.m_strFirstName;
		recset.m_strFn = oStudent.m_strLastName;
		recset.time = oStudent.m_strBirthday;

		if (!recset.CanUpdate()) {
			AfxMessageBox("Record not added; no fiels values were set..");
			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	/////////////////////////////////
		/*
	CString sqlString;
	
	{
	sqlString.Format("INSERT INTO Student (first_name, last_name, birth_date) VALUES ('%s', '%s','%s')", 
								 oStudent.m_strFirstName, oStudent.m_strLastName, oStudent.m_strBirthday);
	}

	try
	{
		g_dbConnection.ExecuteSQL(sqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	*/
	return true;
}

bool CStudent::EditStudent(CStudentData& oStudent) {

	CStudentTable recset(&g_dbConnection);
	
	CString sqlString;
	
	try {
	sqlString.Format("SELECT * FROM Student WHERE id='%d'", oStudent.m_iClassNumber);
	recset.Open(CRecordset::dynaset, sqlString, CRecordset::none);
	
	recset.Edit();
	recset.m_strFn  = oStudent.m_strFirstName;
	recset.m_strLn = oStudent.m_strLastName;
	recset.time = oStudent.m_strBirthday;
	
	if (!recset.UpdateData()) {
		AfxMessageBox("Record not updated; no fiels values were set.");
	}
	}
	catch (exception e) {
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}

	return true;
	
	/*
	Library oLib;
	CString sqlString;
	sqlString.Format("UPDATE Student SET first_name = '%s', last_name = '%s', birth_date = '%s' WHERE id = %s;", 
		oStudent.m_strFirstName, oStudent.m_strLastName, oStudent.m_strBirthday, oLib.IntToCString(oStudent.m_iClassNumber));
	try
	 {
		g_dbConnection.ExecuteSQL(sqlString);
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	 }

	*/
}

bool CStudent::DeleteStudent(const int nClassNumber) {
	
	CString sqlString;
	try 
	{
		CRecordset recset(&g_dbConnection);
		sqlString.Format("SELECT * FROM Student WHERE id = '%d'", nClassNumber);
		
		recset.Open(CRecordset::dynaset, sqlString);
		recset.Delete();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete student!", MB_ICONEXCLAMATION);
	}

	/*
	Library oLib;
	CString SqlString = "DELETE FROM Student WHERE id = '" + oLib.IntToCString(nClassNumber) + "';";

	try
	{
		g_dbConnection.ExecuteSQL(SqlString);
	}
	catch(exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	*/
	
	return true;
}

bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	Library oLib;
	CString m_strClassNum;
	CDBVariant varValueBirthday;

	try
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, "SELECT * FROM Student WHERE id = '" + oLib.IntToCString(nClassNumber) + "';", CRecordset::readOnly);
	
		recset.GetFieldValue("id",m_strClassNum);
		oStudent.m_iClassNumber = atoi(m_strClassNum);
		recset.GetFieldValue("first_name", oStudent.m_strFirstName);
		recset.GetFieldValue("last_name", oStudent.m_strLastName);
		recset.GetFieldValue("birth_date", varValueBirthday);
		oStudent.m_strBirthday = oLib.CDBVariantToCOleDT(varValueBirthday);		
	}
	catch (exception e)
	{
		AfxMessageBox("Error load student!", MB_ICONEXCLAMATION);
	}

	return true;
}

void CStudent::PrintStudent_(list<STUDENT>& m_listStudent)
{
	//test 
/*
	CStudentTable rs(&g_dbConnection);
	
	rs.Open(CRecordset::forwardOnly,
		"select * from Student",
		CRecordset::readOnly);

	
	while (!rs.IsEOF())
	{
		CString strFieldValue;
		//int r = rs.GetODBCFieldCount();
		for (short nIndex = 0; nIndex < rs.GetODBCFieldCount(); nIndex++)
		{
			rs.GetFieldValue(nIndex, strFieldValue);
			// TO DO: Use field value string.
		}
		rs.MoveNext();
	}
	
	
	int n = rs.FlushResultSet();
	while (rs.FlushResultSet())
	{
		// must call MoveNext because cursor is invalid
		rs.MoveNext();

		while (!rs.IsEOF())
		{
			CString strFieldValue;
			for (short nIndex = 0; nIndex < rs.GetODBCFieldCount(); nIndex++)
			{
				rs.GetFieldValue(nIndex, strFieldValue);

				// TO DO: Use field value string.
			}
			rs.MoveNext();
		}
	}

	rs.Close();

*/

	Library oLib;
	CString m_strID, m_strFName, m_strLName;
	CString SqlString = "SELECT * FROM Student";
	CDBVariant varValueBirthday;

	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("id", m_strID);
			recset.GetFieldValue("first_name", m_strFName);
			recset.GetFieldValue("last_name", m_strLName);
			recset.GetFieldValue("birth_date", varValueBirthday);

			STUDENT studentStruct;
			studentStruct.iId = atoi(m_strID);
			sprintf(studentStruct.szName, "%s", m_strFName + " " + m_strLName);
			sprintf(studentStruct.szDate, "%s", oLib.CDBVariantToCString(varValueBirthday));
			m_listStudent.push_back(studentStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

//Reference
void CStudent::AvgScoreBySubject(list<REFERENCE>& m_listReference)
{
	m_listReference.clear();
	Library oLib;
	CString SqlString;
	CString m_strSubject, m_strFN, m_strLN, m_strStudentId, m_strAvgScore;
	
	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id, AVG(Score.score) as avgScore "
				"FROM Student "
				"INNER JOIN Score ON Score.student_id = Student.id "
				"INNER JOIN Subject ON Score.subject_id = Subject.id "
				"GROUP BY first_name, last_name, subject, student_id";
	
	try 
	{	
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);
			recset.GetFieldValue("subject", m_strSubject);
			recset.GetFieldValue("student_id", m_strStudentId);
			recset.GetFieldValue("avgScore", m_strAvgScore);
	
			REFERENCE refStruct;
			refStruct.iId = atoi(m_strStudentId);
			sprintf(refStruct.szClm1, "%s", m_strFN + " " + m_strLN);
			sprintf(refStruct.szClm2, "%s", m_strSubject);
			sprintf(refStruct.szClm3, "%s", m_strAvgScore);

			m_listReference.push_back(refStruct);
	
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::AvgScoreByAllSubject(list<REFERENCE>& m_listReference) {

	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN, m_strStudentId, m_strAvgScore;

	SqlString = "SELECT Score.student_id, Student.first_name, Student.last_name, AVG(Score.score) as avgScore "
				"FROM Student "
				"INNER JOIN Score ON Score.student_id = Student.id "
				"GROUP BY first_name, last_name, student_id";

	try
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("student_id", m_strStudentId);
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);
			recset.GetFieldValue("avgScore", m_strAvgScore);
		
			REFERENCE refStruct;
			refStruct.iId = atoi(m_strStudentId);
			sprintf(refStruct.szClm1, "%s", m_strFN + " " + m_strLN);
			sprintf(refStruct.szClm2, "%s", m_strAvgScore);

			m_listReference.push_back(refStruct);
		
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error average score!", MB_ICONEXCLAMATION);
	}
}

void CStudent::ExcellentStud(list<REFERENCE>& m_listReference) {
	
	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN;

	SqlString = "SELECT Student.first_name, Student.last_name "
				"FROM Student "
				"INNER JOIN Score ON Score.student_id = Student.id "
				"GROUP BY first_name, last_name having AVG(Score.score) = 6";

	try
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
		
		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", m_strFN + " " + m_strLN);
			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::PeopleHaveBirthday(list<REFERENCE>& m_listReference) {
	
	m_listReference.clear();
	Library oLib;
	CString sqlString;
	CString m_strFN, m_strLN;

	COleDateTime oleDate = COleDateTime::GetCurrentTime();
	 
	sqlString.Format("SELECT Student.first_name, Student.last_name FROM Student WHERE DATEPART(mm, birth_date) = '%s' AND DATEPART(dd, birth_date) = '%s'", 
					  oLib.IntToCString(oleDate.GetMonth()), oLib.IntToCString(oleDate.GetDay()));
	
	try {
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, sqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", m_strFN + " " + m_strLN);
			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::remedialExaminationBySub(list<REFERENCE>& m_listReference) {
	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN, m_strSubject, m_strStudentId;

	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id "
				"FROM Student INNER JOIN Score ON Score.student_id = Student.id "
				"INNER JOIN Subject ON Score.subject_id = Subject.id "
				"GROUP BY first_name, last_name, subject, student_id having FLOOR(AVG(Score.score)) = 2;";
	
	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);
			recset.GetFieldValue("subject", m_strSubject);
			recset.GetFieldValue("student_id", m_strStudentId);

			REFERENCE refStruct;
			refStruct.iId = atoi(m_strStudentId);
			sprintf(refStruct.szClm1, "%s", m_strFN + " " + m_strLN);
			sprintf(refStruct.szClm2, "%s", m_strSubject);

			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::remedialExaminationByMoreSub(list<REFERENCE>& m_listReference) {
	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN;

	SqlString = "SELECT first_name, last_name "
				"FROM( SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id "
					  "FROM Student "
					  "INNER JOIN Score ON Score.student_id = Student.id "
					  "INNER JOIN Subject ON Score.subject_id = Subject.id "
					  "GROUP BY first_name, last_name, subject, student_id having AVG(Score.score) = 2 ) src "
				"GROUP BY student_id, src.first_name, src.last_name HAVING count(student_id) >= 3;";
	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", m_strFN + " " + m_strLN);
			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}