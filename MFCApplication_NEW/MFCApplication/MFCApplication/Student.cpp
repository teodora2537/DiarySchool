#include "pch.h"
#include "Student.h"
#include "CParent.h"
#include "CStudentTable.h"
#include <afxwin.h>
#include "CUpdateStudent.h"
#include "CScoreTable.h"
#include "CSubjectTable.h"
#include "CTabScore.h"

CStudentData::CStudentData()
{
	m_iStudentId = 0;
	m_iParentId = 0;
	m_oleDTBirthday = COleDateTime::GetCurrentTime();
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
			
			if (!g_dbConnection.IsOpen()) 
			{
				MessageBox(NULL, "The database isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
				return FALSE;
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

void FillDataFromObjectToStruct(STUDENT& stStudent, CStudentData& oStudent)
{
	Library oLib;
	strcpy_s(stStudent.sz_First_Name, CStringA(oStudent.m_strFirstName).GetString());
	strcpy_s(stStudent.sz_Last_Name, CStringA(oStudent.m_strLastName).GetString());
	strcpy_s(stStudent.szDate, CStringA(oLib.ChangeSingleDate(oStudent.m_oleDTBirthday)).GetString());
	strcpy_s(stStudent.szEmail, CStringA(oStudent.m_strEmail).GetString());
	strcpy_s(stStudent.szPhoneNumber, CStringA(oStudent.m_strPhoneNumber).GetString());
	strcpy_s(stStudent.szEGN, CStringA(oStudent.m_strEgn).GetString());
	strcpy_s(stStudent.szCity, CStringA(oStudent.m_strCity).GetString());
	strcpy_s(stStudent.szPostCode, CStringA(oStudent.m_strPostCode).GetString());
	strcpy_s(stStudent.szNeighborhood, CStringA(oStudent.m_strNeighborhood).GetString());
	strcpy_s(stStudent.szAddress, CStringA(oStudent.m_strAddress).GetString());
}

bool CStudent::AddStudent(CStudentData& oStudent)
{	
	try
	{
		g_dbConnection.BeginTrans();
		
		CStudentTable oStudentTable(&g_dbConnection);
		
		STUDENT stStudent;
		FillDataFromObjectToStruct(stStudent, oStudent);

		if (!oStudentTable.AddRec(stStudent))
		{
			MessageBox(NULL, "The record can't added!", "Can't added", MB_OK | MB_ICONERROR);
			oStudentTable.Close();

			return FALSE;
		}
		oStudentTable.Close();

		//List 'Parents' is empty
		if (oStudent.m_arrParents.size() == 0) 
		{
			g_dbConnection.CommitTrans();
			oStudentTable.Close();
			return TRUE;
		}
		
		//Get last id
		CString strIdStudent;
		GetLastAddedID(strIdStudent);
		
		CParent oParent;

		if (!oParent.Func(atoi(strIdStudent), oStudent.m_arrParents)) {
			g_dbConnection.Rollback();
		}

		g_dbConnection.CommitTrans();

		oStudentTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return FALSE;
	}

	return TRUE;
}

bool CStudent::EditStudent(CStudentData& oStudent)
{
		g_dbConnection.BeginTrans();
		CStudentTable oStudentTable(&g_dbConnection);
	try
	{
		STUDENT stStudent;
		stStudent.iId = oStudent.m_iStudentId;
		FillDataFromObjectToStruct(stStudent, oStudent);

		if (!oStudentTable.EditRec(stStudent))
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			oStudentTable.Close();
			return FALSE;
		}

		oStudentTable.Close();

		// List 'Parent' is Empty
		if (oStudent.m_arrParents.size() == 0) 
		{
			g_dbConnection.CommitTrans();
			oStudentTable.Close();
			
			return TRUE;
		}

		CParent oParent;
		if (!oParent.Func(oStudent.m_iStudentId, oStudent.m_arrParents)) {
			g_dbConnection.Rollback();
		}
		else {
			g_dbConnection.CommitTrans();
		}

		oStudentTable.Close();

	}
	catch (exception e) 
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return FALSE;
	}
	return TRUE;
	}

bool CStudent::DeleteStudent(const int nIdStudent) 
{	
	g_dbConnection.BeginTrans();

	CScore oScore;
	if (!oScore.DeleteScoreByStudent(nIdStudent))
	{
		g_dbConnection.Rollback();
		return FALSE;
	}

	CParent oParent;
	if (!oParent.DeleteParents(nIdStudent)) 
	{
		g_dbConnection.Rollback();
		return FALSE;
	}

	CStudentTable oStudentTable(&g_dbConnection);

	STUDENT stStudent;
	stStudent.iId = nIdStudent;

	if (!oStudentTable.DeleteRec(stStudent))
	{
		MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
		oStudentTable.Close();
		return FALSE;
	}
	
	g_dbConnection.CommitTrans();
	oStudentTable.Close();			

	return TRUE;
}

void FillDataFromStructToObj(STUDENT& recStudent, CStudentData& oStudent) 
{
	Library oLib;
	oStudent.m_iStudentId =	recStudent.iId;
	oStudent.m_strFirstName = recStudent.sz_First_Name;
	oStudent.m_strLastName = recStudent.sz_Last_Name;
	oStudent.m_oleDTBirthday = oLib.CStringToDate(recStudent.szDate);
	oStudent.m_strEmail = recStudent.szEmail;
	oStudent.m_strPhoneNumber = recStudent.szPhoneNumber;
	oStudent.m_strEgn =	recStudent.szEGN;
	oStudent.m_strCity = recStudent.szCity;
	oStudent.m_strPostCode = recStudent.szPostCode;
	oStudent.m_strNeighborhood = recStudent.szNeighborhood;
	oStudent.m_strAddress =	recStudent.szAddress;
	
	oStudent.m_strName = oStudent.m_strFirstName + " " + oStudent.m_strLastName;
}

bool CStudent::LoadStudent(const int nIdStudent, CStudentData& oStudent)
{
	CStudentTable oStudentTable(&g_dbConnection);
	STUDENT recStudent;

	recStudent.iId =nIdStudent;
	oStudentTable.LoadStudent(recStudent);

	FillDataFromStructToObj(recStudent, oStudent);

	CParent oParent;
	//Print by class
	oParent.PrintParentByStudent(nIdStudent, oStudent.m_arrParents);
	oStudentTable.Close();

	return TRUE;
}

void CStudent::PrintStudent(list<CStudentData>& listStudent)
{
	try 
	{
		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return;
		}

		STUDENT stStudent;
		CStudentData oStudent;

		while (!oStudentTable.IsEOF())
		{
			oStudentTable.GetRecStruct(stStudent);
			FillDataFromStructToObj(stStudent, oStudent);
			listStudent.push_back(oStudent);

			oStudentTable.MoveNext();
		}

		oStudentTable.Close();
	}
	catch (exception e) 
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
		return;
	}
}

bool CStudent::GetLastAddedID(CString& nIdStudent) 
{
	CRecordset oRecord(&g_dbConnection);

	oRecord.Open(CRecordset::forwardOnly, "select @@IDENTITY as idStudent", CRecordset::readOnly);

	if (!oRecord.IsOpen())
	{
		MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		oRecord.Close();

		return FALSE;
	}

	oRecord.GetFieldValue("idStudent", nIdStudent);
}

//Reference
void CStudent::AvgScoreBySubject(list<REFERENCE>& listReference)
{
	listReference.clear();

	CString strFirst_Name;
	CString strLast_Name;
	CString strSubject;
	CString strStudentId;
	CString strAvgScore;
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
			recset.GetFieldValue("first_name", strFirst_Name);
			recset.GetFieldValue("last_name", strLast_Name);
			recset.GetFieldValue("subject", strSubject);
			recset.GetFieldValue("student_id", strStudentId);
			recset.GetFieldValue("avgScore", strAvgScore);
	
			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strStudentId);
			sprintf(refStruct.szClm1, "%s", strFirst_Name + " " + strLast_Name);
			sprintf(refStruct.szClm2, "%s", strSubject);
			sprintf(refStruct.szClm3, "%s", strAvgScore);

			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
		return;
	}
}

void CStudent::AvgScoreByAllSubject(list<REFERENCE>& listReference) 
{
	listReference.clear();

	CString strStudentId;
	CString strFirst_Name;
	CString strLast_Name;
	CString strAvgScore;
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
			recset.GetFieldValue("first_name", strFirst_Name);
			recset.GetFieldValue("last_name", strLast_Name);
			recset.GetFieldValue("avgScore", strAvgScore);
		
			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strStudentId);
			sprintf(refStruct.szClm1, "%s", strFirst_Name + " " + strLast_Name);
			sprintf(refStruct.szClm2, "%s", strAvgScore);

			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error average score!", MB_ICONEXCLAMATION);
		return;
	}
}

void CStudent::ExcellentStud(list<REFERENCE>& listReference) 
{	
	listReference.clear();
	CString strFirst_Name;
	CString strLast_Name;
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
			recset.GetFieldValue("first_name", strFirst_Name);
			recset.GetFieldValue("last_name", strLast_Name);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strFirst_Name + " " + strLast_Name);
			
			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
		return;
	}
}

void CStudent::PeopleHaveBirthday(list<REFERENCE>& listReference) 
{	
	listReference.clear();

	Library oLib;
	CString strFirst_Name;
	CString strLast_Name;
	COleDateTime oleDate = COleDateTime::GetCurrentTime();	 
	
	try 
	{
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
			recset.GetFieldValue("first_name", strFirst_Name);
			recset.GetFieldValue("last_name", strLast_Name);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strFirst_Name + " " + strLast_Name);
			
			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
		return;
	}
}

void CStudent::RemedialExaminationBySub(list<REFERENCE>& listReference) 
{
	listReference.clear();

	CString strFirst_Name;
	CString strLast_Name;
	CString strSubject;
	CString strStudentId;
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
			recset.GetFieldValue("first_name", strFirst_Name);
			recset.GetFieldValue("last_name", strLast_Name);
			recset.GetFieldValue("subject", strSubject);
			recset.GetFieldValue("student_id", strStudentId);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strStudentId);
			sprintf(refStruct.szClm1, "%s", strFirst_Name + " " + strLast_Name);
			sprintf(refStruct.szClm2, "%s", strSubject);

			listReference.push_back(refStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
		return;
	}
}

void CStudent::RemedialExaminationByMoreSub(list<REFERENCE>& listReference) 
{
	listReference.clear();
	CString strFirst_Name;
	CString strLast_Name;
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
			recset.GetFieldValue("first_name", strFirst_Name);
			recset.GetFieldValue("last_name", strLast_Name);

			REFERENCE refStruct;
			sprintf(refStruct.szClm0, "%s", strFirst_Name + " " + strLast_Name);
			
			listReference.push_back(refStruct);
			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
		return;
	}
}

void CStudent::GetLastId(int& lastID) 
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
		lastID = oStudentTable.m_iId+1;
		oStudentTable.Close();
	}
	catch (exception e) 
	{
		AfxMessageBox("Don't get last id of student!", MB_ICONEXCLAMATION);
		return;
	}
}