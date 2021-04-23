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

extern CDatabase db;

bool CSubject::AddSubject(const CSubjectData& oSubjectData)
{
	CString SqlString = "INSERT INTO Student (first_name, last_name, birth_date) VALUES ('" + oSubjectData.m_strNameSubject + "','" + oSubjectData.m_strFNameTeacher + "','" + oSubjectData.m_strLNameTeacher + "')";

		try{
			db.ExecuteSQL(SqlString);
		}
		catch (exception e)
		{
			AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		}
	return true;
}

bool CSubject::EditSubject(const CSubjectData& oSubject) {

	Library oLib;

	try{
		db.ExecuteSQL("UPDATE Subject SET subject ='" + oSubject.m_strNameSubject + "' WHERE id = '" + oLib.IntToCString(oSubject.m_iRoomNumber) + "';");
		db.ExecuteSQL("UPDATE Subject SET first_name_teacher ='" + oSubject.m_strFNameTeacher + "' WHERE id = '" + oLib.IntToCString(oSubject.m_iRoomNumber) + "';");
		db.ExecuteSQL("UPDATE Subject SET last_name_teacher ='" + oSubject.m_strLNameTeacher + "' WHERE id = '" + oLib.IntToCString(oSubject.m_iRoomNumber) + "';");
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
	CRecordset recset(&db);

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
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

bool CSubject::DeleteSubject(const int nClassNumber) {

	Library oLib;
	CString SqlString = "DELETE FROM Subject WHERE id = '" + oLib.IntToCString(nClassNumber) + "';";

	try{
	CRecordset recset(&db);

	db.ExecuteSQL(SqlString);
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CSubject::PrintSub(list<SubStruct>& listSub)
{
	Library oLib;
	CString SqlString = "SELECT * FROM Subject";
	CString m_strID, m_strFName, m_strLName, m_strSub;

	try {
		CRecordset recset(&db);
		recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);

		while (!recset.IsEOF()) {
			recset.GetFieldValue("id", m_strID);
			recset.GetFieldValue("subject", m_strSub);
			recset.GetFieldValue("first_name_teacher", m_strFName);
			recset.GetFieldValue("last_name_teacher", m_strLName);

			SubStruct subStruct = { atoi(m_strID), m_strSub, m_strFName + " " + m_strLName };
			listSub.push_back(subStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
}