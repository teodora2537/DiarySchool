#include "pch.h"
#include "Subject.h"
#include "Student.h"
#include <afxwin.h>
#include "CSubjectTable.h"
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
	try
	{
		CSubjectTable recset(&g_dbConnection);
		recset.Open();

		recset.AddNew();

		recset.m_strNameSubject = oSubjectData.m_strNameSubject;
		recset.m_strFNameTeacher = oSubjectData.m_strFNameTeacher;
		recset.m_strLNameTeacher = oSubjectData.m_strLNameTeacher;
	
		if (!recset.Update())
			return false;

		recset.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	
	return true;
}

bool CSubject::EditSubject(const CSubjectData& oSubjectData) {
	
	CSubjectTable recset(&g_dbConnection);
	CString whereClause;

	try
	{
		whereClause.Format("id='%d'", oSubjectData.m_iRoomNumber);
		recset.m_strFilter = whereClause;
		recset.Open();
		recset.Edit();

		recset.m_strNameSubject = oSubjectData.m_strNameSubject;
		recset.m_strFNameTeacher = oSubjectData.m_strFNameTeacher;
		recset.m_strLNameTeacher = oSubjectData.m_strLNameTeacher;
		
		if (!recset.Update()) {
			AfxMessageBox("Record not updated; no fiels values were set.");
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
	}
	
	return true;
}

bool CSubject::DeleteSubject(const int nRoom) {
	
	try
	{
		CSubjectTable recset(&g_dbConnection);
		CString whereClause;

			whereClause.Format("id='%d'", nRoom);
			recset.m_strFilter = whereClause;
			recset.Open();
			recset.Edit();

			recset.m_strNameSubject;
			recset.m_strFNameTeacher;
			recset.m_strLNameTeacher;
			recset.m_strStatus = "unactiv";

			if (!recset.Update()) {
				AfxMessageBox("Record not updated; no fiels values were set.");
			}
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete subject!", MB_ICONEXCLAMATION);
	}

	return true;
}

bool CSubject::LoadSubject(const int nRoomId, CSubjectData& oSubject)
{
	try{

		CSubjectTable recset(&g_dbConnection);
		CString whereClause;
		whereClause.Format("id = '%d'", nRoomId);
		recset.m_strFilter = whereClause;
		recset.Open();

		oSubject.m_iRoomNumber = recset.m_iRoomNumber;
		oSubject.m_strNameSubject = recset.m_strNameSubject;
		oSubject.m_strFNameTeacher = recset.m_strFNameTeacher;
		oSubject.m_strLNameTeacher = recset.m_strLNameTeacher;
	}
	catch (exception e)
	{
		AfxMessageBox("Error load subject!", MB_ICONEXCLAMATION);
	}
	return true;
}

void CSubject::PrintSub(list<SUBJECT>& listSub)
{
	Library oLib;
	CString SqlString = "SELECT * FROM Subject";
	CString m_strID, m_strFName, m_strLName, m_strSub;

	try 
	{
		CSubjectTable recset(&g_dbConnection);
		CString whereClause;
		whereClause.Format("status = '%s'", "active");
		recset.m_strFilter = whereClause;
		recset.Open();

		while (!recset.IsEOF()) 
		{
			SUBJECT subStruct;
			subStruct.iId = recset.m_iRoomNumber;
			sprintf(subStruct.szSubject, "%s", recset.m_strNameSubject);
			sprintf(subStruct.szTeacher, "%s", recset.m_strFNameTeacher + " " + recset.m_strLNameTeacher);

			listSub.push_back(subStruct);

			recset.MoveNext();
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error load sybjects!", MB_ICONEXCLAMATION);
	}
}