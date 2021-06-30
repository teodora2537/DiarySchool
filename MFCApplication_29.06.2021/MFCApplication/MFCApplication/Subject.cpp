#include "pch.h"
#include "Subject.h"
#include "Student.h"
#include <afxwin.h>
#include "CSubjectTable.h"
using namespace std;

CSubjectData::CSubjectData(int _idSubject, CString _subject, CString _fNameTeacher, CString _lNameTeacher)
{
	m_iId = _idSubject;
	m_strSubject = _subject;
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

bool CSubject::IsContainsSubject(CSubjectData& oSubject) 
{	
	CSubjectTable oSubjectTable(&g_dbConnection);
	oSubjectTable.Open();

	while (!oSubjectTable.IsEOF())
	{
		if (oSubjectTable.IsExist(oSubject)) {
			return true;
	}

		oSubjectTable.MoveNext();
	}

	oSubjectTable.Close();

	return false;
}

bool CSubject::AddSubject(CSubjectData& oSubjectData)
{
	try
	{
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen()) 
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			return false;
		}

		if (!oSubjectTable.CanAppend())
		{
			MessageBox(NULL, "The record can't append!", "Can't append", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return false;
		}

		if (IsContainsSubject(oSubjectData)) 
		{
			MessageBox(NULL, "This subject exist!", "Student exist", MB_RETRYCANCEL | MB_ICONERROR);
		}

		oSubjectTable.AddNew();

		oSubjectTable.Add(oSubjectData);
	
		if (!oSubjectTable.Update())
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return false;
		}

		oSubjectTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return false;
	}
	
	return true;
}

bool CSubject::EditSubject(CSubjectData& oSubjectData) 
{	
	try
	{
		
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter.Format("id='%d'", oSubjectData.m_iId);
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen())
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return false;
		}

		oSubjectTable.Edit();

		oSubjectTable.EditSubject(oSubjectData);
		
		if (!oSubjectTable.Update())
		{
			MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error!", MB_ICONEXCLAMATION);
		return false;
	}
	
	return true;
}

bool CSubject::DeleteSubject(const int nRoom) 
{
	try
	{

		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter.Format("id='%d'", nRoom);
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen())
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();

			return false;
		}

		oSubjectTable.Edit();

		oSubjectTable.DeleteSubject();

		if (!oSubjectTable.Update()) {
			MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();

			return false;
		}
	}
	catch (exception e)
	{
		AfxMessageBox("Error delete subject!", MB_ICONEXCLAMATION);
		return false;
	}

	return true;
}

bool CSubject::LoadSubject(const int nRoomId, CSubjectData& oSubject)
{
	try{

		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter.Format("id = '%d'", nRoomId);
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen())
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			
			return false;
		}

		oSubjectTable.Load(oSubject);

		oSubjectTable.Close();
	}
	catch (exception e)
	{
		AfxMessageBox("Error load subject!", MB_ICONEXCLAMATION);
		return false;
	}
	return true;
}

void CSubject::PrintSubject(list<SUBJECT>& listSub)
{
	try 
	{
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.m_strFilter.Format("status = '%s'", "active");
		oSubjectTable.Open();
		
		if (!oSubjectTable.IsOpen())
		{
			MessageBox(NULL, "The table Subject isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
		
			return;
		}
		
		while (!oSubjectTable.IsEOF())
		{
			SUBJECT subStruct;
			subStruct.iId = oSubjectTable.m_iId;
			sprintf(subStruct.szSubject, "%s", oSubjectTable.m_strSubject);
			sprintf(subStruct.szTeacher, "%s", oSubjectTable.m_strFNameTeacher + " " + oSubjectTable.m_strLNameTeacher);

			listSub.push_back(subStruct);

			oSubjectTable.MoveNext();
		}

		oSubjectTable.Close();

	}
	catch (exception e)
	{
		AfxMessageBox("Error load sybjects!", MB_ICONEXCLAMATION);
	}
}

void CSubject::GetLastId(CSubjectData& oSubject) 
{
	try
	{
		CSubjectTable oSubjectTable(&g_dbConnection);
		oSubjectTable.Open();

		if (!oSubjectTable.IsOpen())
		{
			MessageBox(NULL, "The recordset isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();

			return;
		}

		oSubjectTable.MoveLast();
		oSubject.m_iId = oSubjectTable.m_iId;

		oSubjectTable.Close();
	}
	catch (exception e) {
		AfxMessageBox("Don't get last id of student!", MB_ICONEXCLAMATION);
	}
}