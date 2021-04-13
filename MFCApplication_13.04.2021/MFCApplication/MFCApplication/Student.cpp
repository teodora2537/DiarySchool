#include "pch.h"
#include "Student.h"
#include "CUpdateStudent.h"
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

/*virtual*/
CStudent::~CStudent()
{
}

bool CStudent::AddStudent(CStudentData& oStudent)
{
	CString ConnectionString;
	CDatabase db;

	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	CString SqlString;
	CString strID, strName;

	if (db.Open(NULL, FALSE, FALSE, ConnectionString, TRUE))
	{
		TRY{
			SqlString = "INSERT INTO Student (first_name, last_name, birth_date) VALUES ('"+oStudent.m_strFirstName+"','"+oStudent.m_strLastName+"','"+oStudent.m_strBirthday+"')";
			db.ExecuteSQL(SqlString);

			// Close the database
			db.Close();
		}CATCH(CDBException, e) {
			return false;
		}
		END_CATCH;
	}else return false;
	return true;
}

bool CStudent::EditStudent(const CStudentData& oStudent) {
	Library oLib;
	CDatabase db;
	CString SqlString, ConnectionString;
	CString strID, strName;
	int iRec = 0;

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	TRY{
		// Open the database
	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	db.ExecuteSQL("UPDATE Student SET first_name ='" + oStudent.m_strFirstName + "' WHERE id = '" + oLib.IntToCString(oStudent.m_iClassNumber) + "';");
	db.ExecuteSQL("UPDATE Student SET last_name ='" + oStudent.m_strLastName + "' WHERE id = '" + oLib.IntToCString(oStudent.m_iClassNumber) + "';");
	db.ExecuteSQL("UPDATE Student SET birth_date ='" + oStudent.m_strBirthday + "' WHERE id = '" + oLib.IntToCString(oStudent.m_iClassNumber) + "';");

	// Close the database
	db.Close();
	}CATCH(CDBException, e) {
		return false;
	}
	END_CATCH;
	return true;
}

bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	Library oLib;
	CDatabase db;
	CString SqlString, ConnectionString;
	CString m_strID, m_strFName, m_strLName, m_strBirthday;
	CDBVariant varValueBirthday;

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";
	TRY {
	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);
	
	// Allocate the recordset
	CRecordset recset(&db);

	// Execute the query
	recset.Open(CRecordset::forwardOnly, "SELECT * FROM Student WHERE id = '"+oLib.IntToCString(nClassNumber)+"';", CRecordset::readOnly);

	CString m_strClassNum;
	recset.GetFieldValue("id",m_strClassNum);
	oStudent.m_iClassNumber = atoi(m_strClassNum);
	recset.GetFieldValue("first_name", oStudent.m_strFirstName);
	recset.GetFieldValue("last_name", oStudent.m_strLastName);
	recset.GetFieldValue("birth_date", varValueBirthday);
	oStudent.m_strBirthday = oLib.CDBVariantToCString(varValueBirthday);
	db.Close();
	}CATCH(CDBException, e) {
		AfxMessageBox("Database error");
	}
	END_CATCH;
	return true;
}

bool CStudent::DeleteStudent(const int nClassNumber) {
	CString SqlString;
	CString ConnectionString;
	CDatabase db;
	Library oLib;
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	TRY{
		// Open the database
	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	// Allocate the recordset
	CRecordset recset(&db);

	SqlString = "DELETE FROM Student WHERE id = '" + oLib.IntToCString(nClassNumber) + "';";

	db.ExecuteSQL(SqlString);
	}CATCH(CDBException, e) {
		return false;
	}
	END_CATCH;
	return true;
}

void CStudent::PrintStudent_(list<StudentStruct>& m_listStudent)
{
	CDatabase db;
	CString SqlString, ConnectionString;
	CString m_strID, m_strFName, m_strLName;
	CDBVariant varValueBirthday;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);
	
	SqlString = "SELECT * FROM Student";

	// Execute the query
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	Library oLib;

	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue("id", m_strID);
		recset.GetFieldValue("first_name", m_strFName);
		recset.GetFieldValue("last_name", m_strLName);
		recset.GetFieldValue("birth_date", varValueBirthday);

		StudentStruct studentStruct = { atoi(m_strID), m_strFName + " " + m_strLName, oLib.CDBVariantToCString(varValueBirthday)};
		m_listStudent.push_back(studentStruct);

		// goto next record
		recset.MoveNext();
	}

	// Close the database
	db.Close();

}

//Reference
void CStudent::AvgScoreBySubject(list<ReferenceStruct>& m_listReference)
{
	m_listReference.clear();
	CDatabase db;
	CDatabase dbTest;
	CString SqlString, ConnectionString;
	CString m_strSubject, m_strFN, m_strLN, m_strStudentId, m_strSubjectId, m_strAvgScore;
	CDBVariant vtval;
	ReferenceStruct refStruct;
	// Allocate the recordset
	CRecordset recset(&db);
	CRecordset recsetTest(&dbTest);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);
	dbTest.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	Library oLib;
	int avgScore = 0;

	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id, AVG(Score.score) as avgScore FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id GROUP BY first_name, last_name, subject, student_id";
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	while (!recset.IsEOF()) {
		recset.GetFieldValue("first_name", m_strFN);
		recset.GetFieldValue("last_name", m_strLN);
		recset.GetFieldValue("subject", m_strSubject);
		recset.GetFieldValue("student_id", m_strStudentId);
		recset.GetFieldValue("avgScore", m_strAvgScore);

		refStruct = { atoi(m_strStudentId), "",m_strFN + " " + m_strLN, m_strSubject , m_strAvgScore};
		m_listReference.push_back(refStruct);

		recset.MoveNext();
	}
	db.Close();
}

void CStudent::AvgScoreByAllSubject(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CDatabase db;
	CDatabase dbTest;
	CString SqlString, ConnectionString;
	CString m_strSubject, m_strFN, m_strLN, m_strStudentId, m_strSubjectId, m_strAvgScore;
	CDBVariant vtval;
	ReferenceStruct refStruct;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	Library oLib;
	int avgScore = 0;

	//sql string for all
	SqlString = "SELECT Score.student_id, Student.first_name, Student.last_name, AVG(Score.score) as avgScore FROM Student INNER JOIN Score ON Score.student_id = Student.id GROUP BY first_name, last_name, student_id";
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	while (!recset.IsEOF()) {
		recset.GetFieldValue("student_id", m_strStudentId);
		recset.GetFieldValue("first_name", m_strFN);
		recset.GetFieldValue("last_name", m_strLN);
		recset.GetFieldValue("avgScore", m_strAvgScore);
		refStruct = {atoi(m_strStudentId), "",m_strFN + " " + m_strLN, m_strAvgScore};
		m_listReference.push_back(refStruct);
	
		recset.MoveNext();
	}

	db.Close();
}

void CStudent::ExcellentStud(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CDatabase db;
	CDatabase dbTest;
	CString SqlString, ConnectionString;
	CString m_strFN, m_strLN;
	CDBVariant vtval;
	ReferenceStruct refStruct;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	Library oLib;
	int avgScore = 0;

	//sql string for all
	SqlString = "SELECT Student.first_name, Student.last_name FROM Student INNER JOIN Score ON Score.student_id = Student.id group by first_name, last_name having AVG(Score.score) = 6";
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	
	while (!recset.IsEOF()) {
		recset.GetFieldValue("first_name", m_strFN);
		recset.GetFieldValue("last_name", m_strLN);

		refStruct.strClm0 = m_strFN+" "+m_strLN;
		m_listReference.push_back(refStruct);

		recset.MoveNext();
	}
	db.Close();
}

void CStudent::PeopleHaveBirthday(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CDatabase db;
	CDatabase dbTest;
	CString SqlString, ConnectionString;
	CString m_strFN, m_strLN;
	CDBVariant vtval;
	ReferenceStruct refStruct;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	Library oLib;

	COleDateTime oleDate = COleDateTime::GetCurrentTime();

	//sql string for all
	SqlString = "SELECT Student.first_name, Student.last_name FROM Student WHERE DATEPART(mm, birth_date) = '"+oLib.IntToCString(oleDate.GetMonth())+"' and DATEPART(dd, birth_date) = '" + oLib.IntToCString(oleDate.GetDay()) + "'";
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	while (!recset.IsEOF()) {
		recset.GetFieldValue("first_name", m_strFN);
		recset.GetFieldValue("last_name", m_strLN);

		refStruct.strClm0 = m_strFN + " " + m_strLN;
		m_listReference.push_back(refStruct);

		recset.MoveNext();
	}
	db.Close();
}

void CStudent::remedialExaminationBySub(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CDatabase db;
	CDatabase dbTest;
	CString SqlString, ConnectionString;
	CString m_strFN, m_strLN, m_strSubject, m_strStudentId;
	CDBVariant vtval;
	ReferenceStruct refStruct;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	Library oLib;

	COleDateTime oleDate = COleDateTime::GetCurrentTime();

	//sql string for all
	SqlString = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id GROUP BY first_name, last_name, subject, student_id having AVG(Score.score) = 2";
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
	db.Close();
}

void CStudent::remedialExaminationByMoreSub(list<ReferenceStruct>& m_listReference) {
	m_listReference.clear();
	CDatabase db;
	CDatabase dbTest;
	CString SqlString, ConnectionString;
	CString m_strFN, m_strLN, m_strSubject, m_strStudentId;
	CDBVariant vtval;
	ReferenceStruct refStruct;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	Library oLib;

	COleDateTime oleDate = COleDateTime::GetCurrentTime();

	//sql string for all
	SqlString = "select first_name, last_name from( SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id FROM Student INNER JOIN Score ON Score.student_id = Student.id INNER JOIN Subject ON Score.subject_id = Subject.id GROUP BY first_name, last_name, subject, student_id having AVG(Score.score) = 2 ) src group by student_id, src.first_name, src.last_name having count(student_id) >= 3;";
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

	while (!recset.IsEOF()) {
		recset.GetFieldValue("first_name", m_strFN);
		recset.GetFieldValue("last_name", m_strLN);

		refStruct.strClm0 = m_strFN + " " + m_strLN;
		m_listReference.push_back(refStruct);

		recset.MoveNext();
	}
	db.Close();
}