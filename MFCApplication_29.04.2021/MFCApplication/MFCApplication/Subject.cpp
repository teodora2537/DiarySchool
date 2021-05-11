#include "pch.h"
#include "Subject.h"
#include "Student.h"
#include <afxwin.h>
using namespace std;

CSubjectData::CSubjectData(int _roomNumber, CString _nameSubject, CString _fNameTeacher, CString _lNameTeacher)
{
	m_iRoomNumber = _roomNumber;
	m_strNameSubject = _nameSubject;
	m_strFNameTeacher = _fNameTeacher;
	m_strLNameTeacher = _lNameTeacher;
}

CSubjectData::CSubjectData()
{
}

CSubject::CSubject()
{
}

/*virtual*/
CSubject::~CSubject()
{
}

extern CDatabase g_dbConnection;

bool CSubject::AddSubject(const CSubjectData& oSubjectData)
{
	CString sqlString;
	sqlString.Format("INSERT INTO Student (first_name, last_name, birth_date) VALUES ('%s', '%s', '%s')", 
			  oSubjectData.m_strNameSubject, oSubjectData.m_strFNameTeacher, oSubjectData.m_strLNameTeacher);

	try{
		g_dbConnection.ExecuteSQL(sqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

bool CSubject::EditSubject(const CSubjectData& oSubject) {

	Library oLib;
	CString sqlString;
	
	sqlString.Format("UPDATE Subject SET subject ='%s' , first_name_teacher ='%s', last_name_teacher ='%s'  WHERE id = '%s'", 
	oSubject.m_strNameSubject, oSubject.m_strFNameTeacher, oSubject.m_strLNameTeacher, oLib.IntToCString(oSubject.m_iRoomNumber));
	
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

bool CSubject::LoadSubject(const int nRoomId, CSubjectData& oSubject)
{

	try{

	Library oLib;
	CRecordset recset(&g_dbConnection);

	recset.Open(CRecordset::forwardOnly, "SELECT * FROM Subject WHERE id = '" + oLib.IntToCString(nRoomId) + "';", CRecordset::readOnly);

	CString m_strIdRoom;
	recset.GetFieldValue("id",m_strIdRoom);
	oSubject.m_iRoomNumber = atoi(m_strIdRoom);
	recset.GetFieldValue("subject", oSubject.m_strNameSubject);
	recset.GetFieldValue("first_name_teacher", oSubject.m_strFNameTeacher);
	recset.GetFieldValue("last_name_teacher", oSubject.m_strLNameTeacher);
	}
	catch (exception e)
	{
		AfxMessageBox("Error load subject!", MB_ICONEXCLAMATION);
	}
	return true;
}

bool CSubject::DeleteSubject(const int nRoom) {
	CRecordset recset(&g_dbConnection);
	CString sqlString;
	sqlString.Format("SELECT * FROM Subject WHERE id = '%d'", nRoom);
	try
	{
		recset.Open(CRecordset::dynaset, sqlString);
		recset.Delete();
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete subject!", MB_ICONEXCLAMATION);
	}
	/*
	Library oLib;
	CString SqlString = "DELETE FROM Subject WHERE id = '" + oLib.IntToCString(nClassNumber) + "';";

	try{
	CRecordset recset(&g_dbConnection);

	g_dbConnection.ExecuteSQL(SqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	*/
	return true;
}

void CSubject::PrintSub(list<SUBJECT>& listSub)
{
	Library oLib;
	CString SqlString = "SELECT * FROM Subject";
	CString m_strID, m_strFName, m_strLName, m_strSub;

	try 
	{
		CRecordset recset(&g_dbConnection);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) 
		{
			recset.GetFieldValue("id", m_strID);
			recset.GetFieldValue("subject", m_strSub);
			recset.GetFieldValue("first_name_teacher", m_strFName);
			recset.GetFieldValue("last_name_teacher", m_strLName);

			SUBJECT subStruct;
			subStruct.iId = atoi(m_strID);
			sprintf(subStruct.szSubject, "%s", m_strSub);
			sprintf(subStruct.szTeacher, "%s", m_strFName + " " + m_strLName);

			listSub.push_back(subStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load sybjects!", MB_ICONEXCLAMATION);
	}
}