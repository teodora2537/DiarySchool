#include "pch.h"
#include "Student.h"
#include "CStudentTable.h"
#include <afxwin.h>
#include "CUpdateStudent.h"
#include "CScoreTable.h"
#include "CSubjectTable.h"
using namespace std;

CStudentData::CStudentData(int _iId, CString _strFirstName, CString _strLastName, COleDateTime _oleDTBirthday)
{
	m_iId = _iId;
	m_strFirstName = _strFirstName;
	m_strLastName = _strLastName;
	m_oleDT_Birthday = _oleDTBirthday;
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
			if (!g_dbConnection.IsOpen()) {
				MessageBox(NULL, "The database isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
				return false;
			}
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

bool CStudent::IsContainsStudent(CStudentData& oStudent) 
{
	CStudentTable oStudentTable(&g_dbConnection);
	oStudentTable.Open();
	
	while (!oStudentTable.IsEOF()) 
	{
		if (oStudentTable.m_str_First_name == oStudent.m_strFirstName &&
			oStudentTable.m_str_Last_name == oStudent.m_strLastName && 
			oStudentTable.m_oleDT_Birthday == oStudent.m_oleDT_Birthday)
		{
			return true;
		}

		oStudentTable.MoveNext();
	}
	return false;
}

bool CStudent::AddStudent(CStudentData& oStudent)
{	
	try 
	{
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!oStudentTable.CanAppend()) 
		{
			MessageBox(NULL, "The record can't append!", "Can't append", MB_OK | MB_ICONERROR);
			return false;
		}

		if (IsContainsStudent(oStudent)) 
		{
			MessageBox(NULL, "This student exist!", "Student exist", MB_RETRYCANCEL | MB_ICONERROR);
			return false;
		}
		
		oStudentTable.AddNew();
			
		oStudentTable.m_str_First_name = oStudent.m_strFirstName;
		oStudentTable.m_str_Last_name = oStudent.m_strLastName;
		oStudentTable.m_oleDT_Birthday = oStudent.m_oleDT_Birthday;
	
		if (!oStudentTable.Update()) 
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudentTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

bool CStudent::EditStudent(CStudentData& oStudent) 
{
	//Don't edit if record is not change
	try 
	{
		CString strWhere;
		strWhere.Format("id='%d'", oStudent.m_iId);
		
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter = strWhere;
		oStudentTable.Open();

		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudentTable.Edit();

		oStudentTable.m_str_First_name = oStudent.m_strFirstName;
		oStudentTable.m_str_Last_name = oStudent.m_strLastName;
		oStudentTable.m_oleDT_Birthday = oStudent.m_oleDT_Birthday;
		
		if (!oStudentTable.Update())
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			return false;
		}
	}
	catch (exception e) {
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return false;
	}

	return true;
	}

bool CStudent::DeleteStudent(const int nClassNumber) 
{
	try 
	{
		CString strWhere;
		strWhere.Format("id = '%d'", nClassNumber);
		
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter = strWhere;
		oStudentTable.Open(); 
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudentTable.Delete();
		
		if (!oStudentTable.IsDeleted()) 
		{
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
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

bool CStudent::LoadStudent(const int nClassNumber, CStudentData& oStudent)
{
	try
	{
		CString strWhere;
		strWhere.Format("id = '%d'", nClassNumber);
		
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter = strWhere;
		oStudentTable.Open();

		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudent.m_iId = nClassNumber;
		oStudent.m_strFirstName = oStudentTable.m_str_First_name;
		oStudent.m_strLastName = oStudentTable.m_str_Last_name;
		oStudent.m_oleDT_Birthday = oStudentTable.m_oleDT_Birthday;
	}
	catch (exception e)
	{
		AfxMessageBox("Error load student!", MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

void CStudent::PrintStudent_(list<STUDENT>& listStudent)
{
	Library oLib;

	try 
	{
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!oStudentTable.IsEOF())
		{
			STUDENT studentStruct;
			studentStruct.iId = oStudentTable.m_iId;
			sprintf(studentStruct.szName, "%s", oStudentTable.m_str_First_name + " " + oStudentTable.m_str_Last_name);
			sprintf(studentStruct.szDate, "%s", oLib.OleDTToCString(oStudentTable.m_oleDT_Birthday));

			listStudent.push_back(studentStruct);
			oStudentTable.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

//Reference
void CStudent::AvgScoreBySubject(list<REFERENCE>& listReference)
{
	listReference.clear();
	Library oLib;
	CString strSubject, strFN, strLN, strStudentId, strAvgScore;
	CString strSql =  "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id, AVG(Score.score) as avgScore "
							"FROM Student "
							"INNER JOIN Score ON Score.student_id = Student.id "
							"INNER JOIN Subject ON Score.subject_id = Subject.id "
							"GROUP BY first_name, last_name, subject, student_id";
	try 
	{	
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
	
		if (!recset.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", strFN);
			recset.GetFieldValue("last_name", strLN);
			recset.GetFieldValue("subject", strSubject);
			recset.GetFieldValue("student_id", strStudentId);
			recset.GetFieldValue("avgScore", strAvgScore);
	
			REFERENCE refStruct;
			refStruct.iId = atoi(strStudentId);
			sprintf(refStruct.szClm1, "%s", strFN + " " + strLN);
			sprintf(refStruct.szClm2, "%s", strSubject);
			sprintf(refStruct.szClm3, "%s", strAvgScore);

			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::AvgScoreByAllSubject(list<REFERENCE>& listReference) {

	listReference.clear();
	CString strFN, strLN, strStudentId, strAvgScore;
	CString strSql = "SELECT Score.student_id, Student.first_name, Student.last_name, AVG(Score.score) as avgScore "
					 "FROM Student "
					 "INNER JOIN Score ON Score.student_id = Student.id "
					 "GROUP BY first_name, last_name, student_id";

	try
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
	
		if (!recset.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("student_id", strStudentId);
			recset.GetFieldValue("first_name", strFN);
			recset.GetFieldValue("last_name", strLN);
			recset.GetFieldValue("avgScore", strAvgScore);
		
			REFERENCE refStruct;
			refStruct.iId = atoi(strStudentId);
			sprintf(refStruct.szClm1, "%s", strFN + " " + strLN);
			sprintf(refStruct.szClm2, "%s", strAvgScore);

			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error average score!", MB_ICONEXCLAMATION);
	}
}

void CStudent::ExcellentStud(list<REFERENCE>& listReference) {
	
	listReference.clear();
	CString strFN, strLN;
	CString strSql = "SELECT Student.first_name, Student.last_name "
					 "FROM Student "
					 "INNER JOIN Score ON Score.student_id = Student.id "
					 "GROUP BY first_name, last_name having AVG(Score.score) = 6";

	try
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);
		
		if (!recset.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", strFN);
			recset.GetFieldValue("last_name", strLN);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strFN + " " + strLN);
			
			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::PeopleHaveBirthday(list<REFERENCE>& listReference) 
{	
	listReference.clear();

	Library oLib;
	CString strFN, strLN;
	COleDateTime oleDate = COleDateTime::GetCurrentTime();	 
	
	try {
		CString strSql;
		strSql.Format("SELECT Student.first_name, Student.last_name FROM Student WHERE DATEPART(mm, birth_date) = '%s' AND DATEPART(dd, birth_date) = '%s'", 
																   			     oLib.IntToCString(oleDate.GetMonth()), oLib.IntToCString(oleDate.GetDay()));
		
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);

		if (!recset.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", strFN);
			recset.GetFieldValue("last_name", strLN);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strFN + " " + strLN);
			
			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::RemedialExaminationBySub(list<REFERENCE>& listReference) 
{
	listReference.clear();
	CString strFN, strLN, strSubject, strStudentId;
	CString strSql = "SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id "
					 "FROM Student INNER JOIN Score ON Score.student_id = Student.id "
					 "INNER JOIN Subject ON Score.subject_id = Subject.id "
					 "GROUP BY first_name, last_name, subject, student_id having FLOOR(AVG(Score.score)) = 2;";
	
	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);

		if (!recset.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", strFN);
			recset.GetFieldValue("last_name", strLN);
			recset.GetFieldValue("subject", strSubject);
			recset.GetFieldValue("student_id", strStudentId);

			REFERENCE refStruct;
			refStruct.iId = atoi(strStudentId);
			sprintf(refStruct.szClm1, "%s", strFN + " " + strLN);
			sprintf(refStruct.szClm2, "%s", strSubject);

			listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::RemedialExaminationByMoreSub(list<REFERENCE>& listReference) 
{
	listReference.clear();
	CString strFN, strLN;
	CString strSql = "SELECT first_name, last_name "
					 "FROM( SELECT Student.first_name, Student.last_name, Subject.subject, Score.student_id "
					 	  "FROM Student "
					 	  "INNER JOIN Score ON Score.student_id = Student.id "
					 	  "INNER JOIN Subject ON Score.subject_id = Subject.id "
					 	  "GROUP BY first_name, last_name, subject, student_id having AVG(Score.score) = 2 ) src "
					 "GROUP BY student_id, src.first_name, src.last_name HAVING count(student_id) >= 3;";
	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, strSql, CRecordset::readOnly);

		if (!recset.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("first_name", strFN);
			recset.GetFieldValue("last_name", strLN);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strFN + " " + strLN);
			
			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::GetLastId(CStudentData& oStudent) 
{
	try 
	{
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The student table isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}
		
		oStudentTable.MoveLast();
		oStudent.m_iId = oStudentTable.m_iId;
	}
	catch (exception e) {
		AfxMessageBox("Don't get last id of student!", MB_ICONEXCLAMATION);
	}
}