#include "pch.h"
#include "Student.h"
#include "CParent.h"
#include "CStudentTable.h"
#include <afxwin.h>
#include "CUpdateStudent.h"
#include "CScoreTable.h"
#include "CSubjectTable.h"
using namespace std;

CStudentData::CStudentData()
{
}

CStudentData::CStudentData(int iParentId, int iStudentId, CString strFirstName, CString strLastName, COleDateTime oleDTBirthday,
						CString strEmail, CString strPhoneNumber, CString strEgn, CString strCity, 
						CString strPostCode, CString strNeighborhood, CString strAddress)
{
	m_iParentId = iParentId;
	m_iStudentId = iStudentId;
	m_strFirstName = strFirstName;
	m_strLastName = strLastName;
	m_oleDTBirthday = oleDTBirthday;
	m_strEmail = strEmail;
	m_strPhoneNumber = strPhoneNumber;
	m_strEgn = strEgn;
	m_strCity = strCity;
	m_strPostCode = strPostCode;
	m_strNeighborhood = strNeighborhood;
	m_strAddress = strAddress;
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

bool CStudent::isStudentExist(CString strEgn) 
{
	CStudentTable oStudentTable(&g_dbConnection);

	oStudentTable.m_strFilter.Format("egn = '%s'", strEgn);

	oStudentTable.Open();

	if (!oStudentTable.IsOpen())
	{
		MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		return false;
	}
	bool isStudentExist = !oStudentTable.m_str_First_name.IsEmpty();
	oStudentTable.Close();
	return isStudentExist;
}

bool CStudent::AddStudent(CStudentData& oStudent)
{	
	try
	{

		g_dbConnection.BeginTrans();
		CStudentTable oStudentTable(&g_dbConnection);

		oStudentTable.Open();
		
		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			g_dbConnection.Rollback(); 
			return false;
		}

		if (!oStudentTable.CanAppend())
		{
			MessageBox(NULL, "The table student can't append!", "Can't append", MB_OK | MB_ICONERROR);
			g_dbConnection.Rollback();
			oStudentTable.Close();
			return false;
		}

		oStudentTable.AddNew();

		bool isExist = isStudentExist(oStudent.m_strEgn);

		// save student if not exist
		Library oLib;
		if (!isExist)
		{
			oStudentTable.m_str_First_name = oStudent.m_strFirstName;
			oStudentTable.m_str_Last_name = oStudent.m_strLastName;
			//oStudentTable.m_oleDT_Birthday = oStudent.m_oleDTBirthday;
			oStudentTable.m_oleDT_Birthday = oLib.OleDTToCString(oStudent.m_oleDTBirthday);
			oStudentTable.m_str_email = oStudent.m_strEmail;
			oStudentTable.m_str_phone_number = oStudent.m_strPhoneNumber;
			oStudentTable.m_str_egn = oStudent.m_strEgn;
			oStudentTable.m_str_city = oStudent.m_strCity;
			oStudentTable.m_str_post_code = oStudent.m_strPostCode;
			oStudentTable.m_str_neighborhood = oStudent.m_strNeighborhood;
			oStudentTable.m_str_address = oStudent.m_strAddress;

			if (!oStudentTable.Update())
			{
				MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
				g_dbConnection.Rollback();
				oStudentTable.Close();
				return false;
			}
		}

		CParent oParent;
		if (oStudent.m_arrParents.size() == 0) {
			g_dbConnection.CommitTrans();
			oStudentTable.Close();
			return true;
		}

		//////////////////////////////////////
		/*CParentTable oParentTable(&g_dbConnection);
		oParentTable.Open();

		if (!oParentTable.IsOpen())
		{
			MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!oParentTable.CanAppend())
		{
			MessageBox(NULL, "The table parent can't append!", "Can't append", MB_OK | MB_ICONERROR);
			oParentTable.Close();
			return true;
		}

		oParentTable.AddNew();

		auto it = oStudent.m_arrParents.begin();

		while (oStudent.m_arrParents.size() != 0)
		{
			it = oStudent.m_arrParents.begin();
			oParentTable.m_iId;
			oParentTable.m_iIdStudent = it->m_iStudentId;
			oParentTable.m_str_first_name = it->m_strFirstName;
			oParentTable.m_str_last_name = it->m_strLastName;
			oParentTable.m_str_phone_number = it->m_strPhoneNumber;
			oParentTable.m_str_email = it->m_strEmail;
			oParentTable.m_str_city = it->m_strCity;
			oParentTable.m_str_post_code = it->m_strPostCode;
			oParentTable.m_str_neighborhood = it->m_strNeighborhood;
			oParentTable.m_str_address = it->m_strAddress;

			if (!oParentTable.Update())
			{
				MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
				g_dbConnection.Rollback();
				oParentTable.Close();
				return true;
			}
			oStudent.m_arrParents.erase(it);
		}


		oParentTable.Close();
		g_dbConnection.CommitTrans();
		*///////////////////////////////////////

		if (oParent.AddParent(oStudent.m_arrParents) && !isExist){
			g_dbConnection.Rollback();
		}
		else{
			g_dbConnection.CommitTrans();
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
		CString strWhereStudent;
		strWhereStudent.Format("id='%d'", oStudent.m_iStudentId);


		CStudentTable oStudentTable(&g_dbConnection);


		oStudentTable.m_strFilter = strWhereStudent;


		oStudentTable.Open();


		if (!oStudentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudentTable.Edit();
		g_dbConnection.BeginTrans();

		bool bIsChange = true;
		Library oLib;
		if (oStudentTable.m_str_First_name == oStudent.m_strFirstName &&
			oStudentTable.m_str_Last_name == oStudent.m_strLastName &&
			//oStudentTable.m_oleDT_Birthday == oStudent.m_oleDTBirthday &&
			oStudentTable.m_oleDT_Birthday == oLib.OleDTToCString(oStudent.m_oleDTBirthday) &&
			oStudentTable.m_str_email == oStudent.m_strEmail &&
			oStudentTable.m_str_phone_number == oStudent.m_strPhoneNumber &&
			oStudentTable.m_str_egn == oStudent.m_strEgn &&
			oStudentTable.m_str_city == oStudent.m_strCity &&
			oStudentTable.m_str_post_code == oStudent.m_strPostCode &&
			oStudentTable.m_str_neighborhood == oStudent.m_strNeighborhood &&
			oStudentTable.m_str_address == oStudent.m_strAddress)
			{ 
				bIsChange = false;
			}

			if(bIsChange)
			{
				oStudentTable.m_str_First_name = oStudent.m_strFirstName;
				oStudentTable.m_str_Last_name = oStudent.m_strLastName;
				oStudentTable.m_oleDT_Birthday = oLib.OleDTToCString(oStudent.m_oleDTBirthday);
				oStudentTable.m_str_email = oStudent.m_strEmail;
				oStudentTable.m_str_phone_number = oStudent.m_strPhoneNumber;
				oStudentTable.m_str_egn = oStudent.m_strEgn;
				oStudentTable.m_str_city = oStudent.m_strCity;
				oStudentTable.m_str_post_code = oStudent.m_strPostCode;
				oStudentTable.m_str_neighborhood = oStudent.m_strNeighborhood;
				oStudentTable.m_str_address = oStudent.m_strAddress;
		
				if (!oStudentTable.Update())
				{
					MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
					oStudentTable.Close();
					return false;
				}
			}

		if (oStudent.m_arrParents.size() == 0) 
		{
			g_dbConnection.CommitTrans();
			oStudentTable.Close();
			return true;
		}

		CParent oParent;
		if (!oParent.EditParent(oStudent.m_arrParents)){
			g_dbConnection.Rollback();
		}
		else {
			g_dbConnection.CommitTrans();
		}

		oStudentTable.Close();

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
		g_dbConnection.BeginTrans();

		CScore oScore;
		if (!oScore.DeleteScoreByStudent(nClassNumber))
		{
			g_dbConnection.Rollback();
			return false;
		}

		CParent oParent;
		if (!oParent.DeleteParent(nClassNumber)) {
			g_dbConnection.Rollback();
			return false;
		}

		CString strWhere;
		strWhere.Format("id = %d", nClassNumber);

		CStudentTable oStudentTable(&g_dbConnection);
		oStudentTable.m_strFilter = strWhere;
		oStudentTable.Open();

		if (!oStudentTable.IsOpen())
		{
			g_dbConnection.Rollback();
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oStudentTable.Close();
			return false;
		}

		oStudentTable.Delete();
		
		if (!oStudentTable.IsDeleted()) 
		{
			g_dbConnection.Rollback();
			MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			oStudentTable.Close();
			return false;
		}

			g_dbConnection.CommitTrans();
			oStudentTable.Close();
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

		Library oLib;
		oStudent.m_iStudentId = nClassNumber;
		oStudent.m_strFirstName = oStudentTable.m_str_First_name;
		oStudent.m_strLastName = oStudentTable.m_str_Last_name;
		//oStudent.m_oleDTBirthday = oStudentTable.m_oleDT_Birthday;
		oStudent.m_oleDTBirthday = oLib.CStringToDate(oStudentTable.m_oleDT_Birthday);
		oStudent.m_strEmail= oStudentTable.m_str_email;
		oStudent.m_strPhoneNumber = oStudentTable.m_str_phone_number;
		oStudent.m_strEgn = oStudentTable.m_str_egn;
		oStudent.m_strCity = oStudentTable.m_str_city;
		oStudent.m_strPostCode = oStudentTable.m_str_post_code;
		oStudent.m_strNeighborhood = oStudentTable.m_str_neighborhood;
		oStudent.m_strAddress = oStudentTable.m_str_address;

		CParent oParent;
		oParent.PrintParent_(nClassNumber, oStudent.m_arrParents);

		oStudentTable.Close();

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
			sprintf(studentStruct.szDate, "%s", oStudentTable.m_oleDT_Birthday);
			sprintf(studentStruct.szEmail, "%s", oStudentTable.m_str_email);
			sprintf(studentStruct.szPhoneNumber, "%s",	oStudentTable.m_str_phone_number);
			sprintf(studentStruct.szEGN, "%s", oStudentTable.m_str_egn);
			sprintf(studentStruct.szCity, "%s", oStudentTable.m_str_city);
			sprintf(studentStruct.szPostCode, "%s", oStudentTable.m_str_post_code);
			sprintf(studentStruct.szNeighborhood, "%s", oStudentTable.m_str_neighborhood);
			sprintf(studentStruct.szAddress, "%s", oStudentTable.m_str_address);

			listStudent.push_back(studentStruct);

			oStudentTable.MoveNext();
		}

		oStudentTable.Close();
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

//void CStudent::GetLastId(CStudentData& oStudent) 
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
		//oStudent.m_iId = oStudentTable.m_iId;
		lastID = oStudentTable.m_iId+1;
		oStudentTable.Close();
	}
	catch (exception e) {
		AfxMessageBox("Don't get last id of student!", MB_ICONEXCLAMATION);
	}
}