#include "pch.h"
#include "Student.h"
#include "CUpdateStudent.h"
#include <afxwin.h>
using namespace std;

CStudentData::CStudentData(int _classNum, CString _fName, CString _lName, CString _birthday)
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
	CString sqlString;
	sqlString.Format("INSERT INTO Student (first_name, last_name, birth_date) VALUES ('%s', '%s','%s')", 
								 oStudent.m_strFirstName, oStudent.m_strLastName, oStudent.m_strBirthday);

	try
	{
		g_dbConnection.ExecuteSQL(sqlString);

	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}

	return true;
}

bool CStudent::EditStudent(const CStudentData& oStudent) {

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

	return true;
}

bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	Library oLib;
	CString m_strClassNum;
	CDBVariant varValueBirthday;

	try{

	CRecordset recset(&g_dbConnection);
	recset.Open(CRecordset::forwardOnly, "SELECT * FROM Student WHERE id = '" + oLib.IntToCString(nClassNumber) + "';", CRecordset::readOnly);

	recset.GetFieldValue("id",m_strClassNum);
	oStudent.m_iClassNumber = atoi(m_strClassNum);
	recset.GetFieldValue("first_name", oStudent.m_strFirstName);
	recset.GetFieldValue("last_name", oStudent.m_strLastName);
	recset.GetFieldValue("birth_date", varValueBirthday);
	oStudent.m_strBirthday = oLib.CDBVariantToCString(varValueBirthday);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}

	return true;
}

bool CStudent::DeleteStudent(const int nClassNumber) {
	
	Library oLib;
	CString SqlString = "DELETE FROM Student WHERE id = '" + oLib.IntToCString(nClassNumber) + "';";

	try{

		g_dbConnection.ExecuteSQL(SqlString);
	
	}catch(exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CStudent::PrintStudent_(list<STUDENT>& m_listStudent)
{
	Library oLib;
	CString m_strID, m_strFName, m_strLName;
	CDBVariant varValueBirthday;
	CString SqlString = "SELECT * FROM Student";

	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
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
	
		while (!recset.IsEOF()) {
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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
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

	try{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) {
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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
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

	try{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
		
		while (!recset.IsEOF()) {
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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
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

			while (!recset.IsEOF()) {
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
			AfxMessageBox("Error!", MB_ICONEXCLAMATION);
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
	
	try {
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
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

		while (!recset.IsEOF()) {
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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}