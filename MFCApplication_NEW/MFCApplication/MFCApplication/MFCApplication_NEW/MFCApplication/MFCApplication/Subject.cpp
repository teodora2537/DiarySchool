#include "pch.h"
#include "Subject.h"
#include "CSubjectTable.h"

CSubjectData::CSubjectData(int _idSubject, CString _subject, CString _firstNameTeacher, CString _lastNameTeacher)
{
	m_iId = _idSubject;
	m_strSubject = _subject;
	m_strFirstNameTeacher = _firstNameTeacher;
	m_strLastNameTeacher = _lastNameTeacher;
}

CSubjectData::CSubjectData()
{
	m_iId = 0;
}

CSubject::CSubject()
{
}

/*virtual*/
CSubject::~CSubject()
{
}

extern CDatabase g_dbConnection;

void FillStructWithObjectData(SUBJECT& stSubject, CSubjectData& oSubjectData)
{
	strcpy_s(stSubject.szSubject, CStringA(oSubjectData.m_strSubject).GetString());
	strcpy_s(stSubject.sz_First_Name, CStringA(oSubjectData.m_strFirstNameTeacher).GetString());
	strcpy_s(stSubject.sz_Last_Name, CStringA(oSubjectData.m_strLastNameTeacher).GetString());
}

bool CSubject::AddSubject(CSubjectData& oSubjectData)
{
	CSubjectTable oSubjectTable(&g_dbConnection);
	SUBJECT stSubject;

	FillStructWithObjectData(stSubject, oSubjectData);

	if (!oSubjectTable.AddRec(stSubject))
	{
		MessageBox(NULL, "The record can't added!", "Can't added", MB_OK | MB_ICONERROR);
		oSubjectTable.Close();

		return FALSE;
	}

	oSubjectTable.Close();
	
	return TRUE;
}

bool CSubject::EditSubject(CSubjectData& oSubjectData) 
{	
	CSubjectTable oSubjectTable(&g_dbConnection);

	SUBJECT stSubject;
	stSubject.iId = oSubjectData.m_iId;

	FillStructWithObjectData(stSubject, oSubjectData);

	if (!oSubjectTable.EditRec(stSubject))
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		oSubjectTable.Close();
		return FALSE;
	}

	oSubjectTable.Close();

	return TRUE;
}

bool CSubject::DeleteSubject(const int nRoom) 
{
		CSubjectTable oSubjectTable(&g_dbConnection);

		SUBJECT stSubject;
		stSubject.iId = nRoom;

		if (!oSubjectTable.DeleteRec(stSubject))
		{
			MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
			oSubjectTable.Close();
			return FALSE;
		}

		oSubjectTable.Close();

	return TRUE;
}

bool CSubject::LoadSubject(const int nRoomId, CSubjectData& oSubject)
{
		CSubjectTable oSubjectTable(&g_dbConnection);

		SUBJECT recSubject;
		recSubject.iId = nRoomId;
		oSubjectTable.LoadSubject(recSubject);

		oSubject.m_iId = recSubject.iId;
		oSubject.m_strSubject = recSubject.szSubject;
		oSubject.m_strFirstNameTeacher = recSubject.sz_First_Name;
		oSubject.m_strLastNameTeacher = recSubject.sz_Last_Name;
		
	return TRUE;
}

void CSubject::PrintSubject(list<CSubjectData>& listSub)
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
		
		SUBJECT stSubject;
		CSubjectData oSubject;

		while (!oSubjectTable.IsEOF())
		{
			oSubjectTable.GetRecStruct(stSubject);

			oSubject.m_iId = stSubject.iId;
			oSubject.m_strSubject = stSubject.szSubject;
			oSubject.m_strFirstNameTeacher = stSubject.sz_First_Name;
			oSubject.m_strLastNameTeacher = stSubject.sz_Last_Name;
			listSub.push_back(oSubject);

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