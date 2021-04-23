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

CDatabase db;

BOOL CWinApp::InitInstance()
{
		CString ConnectionString= "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";
		
		try 
		{
			db.Open(NULL, FALSE, FALSE, ConnectionString, TRUE);
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
	CString SqlString = "INSERT INTO Student (first_name, last_name, birth_date) VALUES ('" + oStudent.m_strFirstName + "','" + oStudent.m_strLastName + "','" + oStudent.m_strBirthday + "')";

	try
	{
		db.ExecuteSQL(SqlString);

	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}

	return true;
}

bool CStudent::EditStudent(const CStudentData& oStudent) {

	Library oLib;

	 try
	 {
		db.ExecuteSQL("UPDATE Student SET first_name ='" + oStudent.m_strFirstName + "' WHERE id = '" + oLib.IntToCString(oStudent.m_iClassNumber) + "';");
		db.ExecuteSQL("UPDATE Student SET last_name ='" + oStudent.m_strLastName + "' WHERE id = '" + oLib.IntToCString(oStudent.m_iClassNumber) + "';");
		db.ExecuteSQL("UPDATE Student SET birth_date ='" + oStudent.m_strBirthday + "' WHERE id = '" + oLib.IntToCString(oStudent.m_iClassNumber) + "';");
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

	CRecordset recset(&db);
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

	db.ExecuteSQL(SqlString);
	
	}catch(exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CStudent::PrintStudent_(list<StudentStruct>& m_listStudent)
{
	Library oLib;
	CString m_strID, m_strFName, m_strLName;
	CDBVariant varValueBirthday;
	CString SqlString = "SELECT * FROM Student";

	try 
	{
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
			recset.GetFieldValue("id", m_strID);
			recset.GetFieldValue("first_name", m_strFName);
			recset.GetFieldValue("last_name", m_strLName);
			recset.GetFieldValue("birth_date", varValueBirthday);

			StudentStruct studentStruct = { atoi(m_strID), m_strFName + " " + m_strLName, oLib.CDBVariantToCString(varValueBirthday)};
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
void CStudent::AvgScoreBySubject(list<ReferenceStruct>& m_listReference)
{
	m_listReference.clear();
	Library oLib;
	CString SqlString;
	CString m_strSubject, m_strFN, m_strLN, m_strStudentId, m_strAvgScore;

	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id, AVG(Score.score) as avgScore FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id GROUP BY first_name, last_name, subject, student_id";
	
	try 
	{	
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) {
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);
			recset.GetFieldValue("subject", m_strSubject);
			recset.GetFieldValue("student_id", m_strStudentId);
			recset.GetFieldValue("avgScore", m_strAvgScore);
	
			ReferenceStruct refStruct = { atoi(m_strStudentId), "",m_strFN + " " + m_strLN, m_strSubject , m_strAvgScore};
			m_listReference.push_back(refStruct);
	
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}

void CStudent::AvgScoreByAllSubject(list<ReferenceStruct>& m_listReference) {

	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN, m_strStudentId, m_strAvgScore;

	SqlString = "SELECT Score.student_id, Student.first_name, Student.last_name, AVG(Score.score) as avgScore FROM Student INNER JOIN Score ON Score.student_id = Student.id GROUP BY first_name, last_name, student_id";

	try{
	
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
		while (!recset.IsEOF()) {
			recset.GetFieldValue("student_id", m_strStudentId);
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);
			recset.GetFieldValue("avgScore", m_strAvgScore);
			
			ReferenceStruct refStruct = {atoi(m_strStudentId), "",m_strFN + " " + m_strLN, m_strAvgScore};
			m_listReference.push_back(refStruct);
		
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}

void CStudent::ExcellentStud(list<ReferenceStruct>& m_listReference) {
	
	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN;
	ReferenceStruct refStruct;

	SqlString = "SELECT Student.first_name, Student.last_name FROM Student INNER JOIN Score ON Score.student_id = Student.id group by first_name, last_name having AVG(Score.score) = 6";

	try{

		CRecordset recset(&db); 
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
		
		while (!recset.IsEOF()) {
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);

			refStruct.strClm0 = m_strFN+" "+m_strLN;
			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}

void CStudent::PeopleHaveBirthday(list<ReferenceStruct>& m_listReference) {
	
	m_listReference.clear();
	Library oLib;
	CString SqlString;
	CString m_strFN, m_strLN;
	ReferenceStruct refStruct;

	COleDateTime oleDate = COleDateTime::GetCurrentTime();
	 
	SqlString = "SELECT Student.first_name, Student.last_name FROM Student WHERE DATEPART(mm, birth_date) = '"+oLib.IntToCString(oleDate.GetMonth())+"' and DATEPART(dd, birth_date) = '" + oLib.IntToCString(oleDate.GetDay()) + "'";
	
		try {
			CRecordset recset(&db);
			recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

			while (!recset.IsEOF()) {
				recset.GetFieldValue("first_name", m_strFN);
				recset.GetFieldValue("last_name", m_strLN);

				refStruct.strClm0 = m_strFN + " " + m_strLN;
				m_listReference.push_back(refStruct);

				recset.MoveNext();
			}
		}
		catch (exception e)
		{
			AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		}
	}

void CStudent::remedialExaminationBySub(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN, m_strSubject, m_strStudentId;
	ReferenceStruct refStruct;

	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id GROUP BY first_name, last_name, subject, student_id having AVG(Score.score) = 2";
	
	try {
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);
			recset.GetFieldValue("subject", m_strSubject);
			recset.GetFieldValue("student_id", m_strStudentId);

			refStruct.nIdStudent = atoi(m_strStudentId);
			refStruct.strClm1 = m_strFN + " " + m_strLN;
			refStruct.strClm2 = m_strSubject;
			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}

void CStudent::remedialExaminationByMoreSub(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CString SqlString;
	CString m_strFN, m_strLN;
	ReferenceStruct refStruct;
	SqlString = "select first_name, last_name from( SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id GROUP BY first_name, last_name, subject, student_id having AVG(Score.score) = 2 ) src group by student_id, src.first_name, src.last_name having count(student_id) >= 3;";
	try 
	{
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
			recset.GetFieldValue("first_name", m_strFN);
			recset.GetFieldValue("last_name", m_strLN);

			refStruct.strClm0 = m_strFN + " " + m_strLN;
			m_listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}