#include "pch.h"
#include "Student.h"
#include "CStudentTable.h"
#include <afxwin.h>
#include "CUpdateStudent.h"
#include "CScoreTable.h"
#include "CSubjectTable.h"
#include "CParentTable.h"
using namespace std;

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

bool CStudent::AddStudent(CStudentData& oStudent)
{	
	try
	{
		/*STUDENT*/
		CStudentTable oStudentTable(&g_dbConnection);
		CParentTable oParentTable(&g_dbConnection);
		
		oStudentTable.Open();
		oParentTable.Open();

		if (!oStudentTable.IsOpen() || !oParentTable.IsOpen())
		{
			MessageBox(NULL, "The table student or parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!oStudentTable.CanAppend() || !oParentTable.CanAppend())
		{
			MessageBox(NULL, "The record can't append!", "Can't append", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudentTable.AddNew();
		oParentTable.AddNew();
		
		int i = 0;
		CString strEGN;
		CString strParentFirstName;
		CString strParentLastName;

		for (const auto& student : oStudent.m_objList)
		{
			if (i == 0)
			{
				strEGN = student.m_strStudent_Egn;
				i++;
				continue;
			}
			else if (i == 1)
			{
				strParentFirstName = student.m_strStudent_FirstName;
				strParentLastName = student.m_strStudent_LastName;
			}
		}


		bool isStudentExist = false;
		while (true)
		{
			//student: exist	parent: exist
			if (oStudentTable.m_str_egn == strEGN &&
				oParentTable.m_str_first_name == strParentFirstName &&
				oParentTable.m_str_last_name == strParentLastName)
			{
				isStudentExist = true;
				MessageBox(NULL, "This student and parent exist!", "Student exist", MB_RETRYCANCEL | MB_ICONERROR);
				return false;
			}
					//student: exist	parent: not exist
			else if (oStudentTable.m_str_egn == strEGN &&
				(oParentTable.m_str_first_name != strParentFirstName ||
				 oParentTable.m_str_last_name != strParentLastName))
				{
				int i = 0;
					//for (list<CStudentData>::iterator parent = oStudent.m_objList.begin(); parent != oStudent.m_objList.end(); ++parent) {
				for (const auto& parent : oStudent.m_objList){
				if (i == 0) {
							oParentTable.m_iIdStudent = oStudentTable.m_iId; i++;
						}
						else {
						oParentTable.m_str_first_name = parent.m_strStudent_FirstName;
						oParentTable.m_str_last_name = parent.m_strStudent_LastName;
						oParentTable.m_str_email = parent.m_strStudent_Email;
						oParentTable.m_str_phone_number = parent.m_strStudent_PhoneNumber;
						oParentTable.m_str_city = parent.m_strStudent_City;
						oParentTable.m_str_post_code = parent.m_strStudent_PostCode;
						oParentTable.m_str_neighborhood = parent.m_strStudent_Neighborhood;
						oParentTable.m_str_address = parent.m_strStudent_Address;
						break;
						}
					}
					isStudentExist = true;
					
					if (!oParentTable.Update())
					{
						MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
						return false;
					}
					break;
				}

			oStudentTable.MoveNext();
		}

		//student: not exist	parent: not exist
		if (!isStudentExist) 
		{
			FillTables(oStudentTable, oParentTable, oStudent.m_objList);
			
			if (!oStudentTable.Update() || !oParentTable.Update())
			{
				MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
				return false;
			}
		}
	
		oStudentTable.Close();
		oParentTable.Close();
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
		strWhereStudent.Format("id='%d'", oStudent.m_iId);
		CString strWhereParent;
		strWhereParent.Format("student_id='%d'", oStudent.m_iId);
		
		CStudentTable oStudentTable(&g_dbConnection);
		CParentTable oParentTable(&g_dbConnection);

		oStudentTable.m_strFilter = strWhereStudent;
		oParentTable.m_strFilter = strWhereParent;

		oStudentTable.Open();
		oParentTable.Open();

		if (!oStudentTable.IsOpen() || !oParentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student ot Parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		oStudentTable.Edit();
		//oParentTable.Edit();

		FillTables(oStudentTable, oParentTable, oStudent.m_objList);

		if (!oStudentTable.Update() || !oParentTable.Update())
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
/*OPRAVI GO*/
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
		oStudent.m_strStudent_FirstName = oStudentTable.m_str_First_name;
		oStudent.m_strStudent_LastName = oStudentTable.m_str_Last_name;
		oStudent.m_oleDT_Birthday = oStudentTable.m_oleDT_Birthday;
		oStudent.m_strStudent_Email= oStudentTable.m_str_email;
		oStudent.m_strStudent_PhoneNumber = oStudentTable.m_str_phone_number;
		oStudent.m_strStudent_Egn = oStudentTable.m_str_egn;
		oStudent.m_strStudent_City = oStudentTable.m_str_city;
		oStudent.m_strStudent_PostCode = oStudentTable.m_str_post_code;
		oStudent.m_strStudent_Neighborhood = oStudentTable.m_str_neighborhood;
		oStudent.m_strStudent_Address = oStudentTable.m_str_address;
		oStudent.m_objList.push_back(oStudent);
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
			sprintf(studentStruct.szEmail, "%s",		oStudentTable.m_str_email);
			sprintf(studentStruct.szPhoneNumber, "%s",	oStudentTable.m_str_phone_number);
			sprintf(studentStruct.szEGN, "%s", oStudentTable.m_str_egn);
			sprintf(studentStruct.szCity, "%s", oStudentTable.m_str_city);
			sprintf(studentStruct.szPostCode, "%s", oStudentTable.m_str_post_code);
			sprintf(studentStruct.szNeighborhood, "%s", oStudentTable.m_str_neighborhood);
			sprintf(studentStruct.szAddress, "%s", oStudentTable.m_str_address);

			listStudent.push_back(studentStruct);
			oStudentTable.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load students!", MB_ICONEXCLAMATION);
	}
}

void CStudent::FillTables(CStudentTable& oStudentTable, CParentTable& oParentTable, list<CStudentData>& objList)
{
	int i = 0;
	
	for (const auto& obj : objList)
	{
		if (i == 0) 
		{
			oStudentTable.m_str_First_name = obj.m_strStudent_FirstName;
			oStudentTable.m_str_Last_name = obj.m_strStudent_LastName;
			oStudentTable.m_oleDT_Birthday = obj.m_oleDT_Birthday;
			oStudentTable.m_str_email = obj.m_strStudent_Email;
			oStudentTable.m_str_phone_number = obj.m_strStudent_PhoneNumber;
			oStudentTable.m_str_egn = obj.m_strStudent_Egn;
			oStudentTable.m_str_city = obj.m_strStudent_City;
			oStudentTable.m_str_post_code = obj.m_strStudent_PostCode;
			oStudentTable.m_str_neighborhood = obj.m_strStudent_Neighborhood;
			oStudentTable.m_str_address = obj.m_strStudent_Address;
			i++;
		}
		else if (i == 1)
		{
			oParentTable.m_iIdStudent = obj.m_iId;
			oParentTable.m_str_first_name = obj.m_strStudent_FirstName;
			oParentTable.m_str_last_name = obj.m_strStudent_LastName;
			oParentTable.m_str_email = obj.m_strStudent_Email;
			oParentTable.m_str_phone_number = obj.m_strStudent_PhoneNumber;
			oParentTable.m_str_city = obj.m_strStudent_City;
			oParentTable.m_str_post_code = obj.m_strStudent_PostCode;
			oParentTable.m_str_neighborhood = obj.m_strStudent_Neighborhood;
			oParentTable.m_str_address = obj.m_strStudent_Address;
		}
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