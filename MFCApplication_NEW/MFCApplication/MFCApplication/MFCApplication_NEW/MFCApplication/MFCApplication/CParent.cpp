#include "pch.h"
#include "CParent.h"
#include "Student.h"
#include "CParentTable.h"

 CParentData::CParentData()
 {
	 m_iParentId = 0;
	 m_iStudentId = 0;
	 m_eRecordMode = eRecordMode_None;
 }

CParentData::CParentData(int iParentId, int iStudentId, CString strFirstName, CString strLastName, CString strPhoneNumber, 
					CString strEmail, CString strCity, CString strPostCode, CString strNeighborhood, CString strAddress)
 {
 	m_iParentId = iParentId;
 	m_iStudentId = iStudentId;
 	m_strFirstName = strFirstName;
 	m_strLastName = strLastName;
 	m_strEmail = strEmail;
 	m_strPhoneNumber = strPhoneNumber;
 	m_strCity = strCity;
 	m_strPostCode = strPostCode;
 	m_strNeighborhood = strNeighborhood;
 	m_strAddress = strAddress;
 }

extern CDatabase g_dbConnection;

bool CParent::Func(int nIdStudent, list<CParentData>& arrParents)
{
	for (auto& it = arrParents.begin(); it != arrParents.end(); it++)
	{
		switch (it->m_eRecordMode)
		{
		case eRecordMode_Add:
			
			it->m_iStudentId = nIdStudent;
			
			if (!AddParent(*it)) {
				return FALSE;
			}
			
			break;
		case eRecordMode_Edit:
		
			if (!EditParent(*it)) {
				return FALSE;
			}
			
			break;
		case eRecordMode_Delete:
			
			if (!DeleteOneParent(it->m_iParentId)) {
				return FALSE;
			}
		
			break;
		case eRecordMode_View:
			
			if (!LoadParent(*it)) {
				return FALSE;
			}
			
			break;
		default:
			break;
		}
	}
	return TRUE;
}

void FillDataFromObjectToStruct(PARENT& stParent, CParentData& oParent)
{
	stParent.iStudentID = oParent.m_iStudentId;
	strcpy_s(stParent.sz_First_Name, CStringA(oParent.m_strFirstName).GetString());
	strcpy_s(stParent.sz_Last_Name, CStringA(oParent.m_strLastName).GetString());
	strcpy_s(stParent.szEmail, CStringA(oParent.m_strEmail).GetString());
	strcpy_s(stParent.szPhoneNumber, CStringA(oParent.m_strPhoneNumber).GetString());
	strcpy_s(stParent.szCity, CStringA(oParent.m_strCity).GetString());
	strcpy_s(stParent.szPostCode, CStringA(oParent.m_strPostCode).GetString());
	strcpy_s(stParent.szNeighborhood, CStringA(oParent.m_strNeighborhood).GetString());
	strcpy_s(stParent.szAddress, CStringA(oParent.m_strAddress).GetString());
}

bool CParent::AddParent(CParentData& oParent)
{
	CParentTable oParentTable(&g_dbConnection);
	
	PARENT stParent;

	FillDataFromObjectToStruct(stParent, oParent);

	if (!oParentTable.AddRec(stParent))
	{
		MessageBox(NULL, "The record can't added!", "Can't added", MB_OK | MB_ICONERROR);
		oParentTable.Close();
		
		return FALSE;
	}

	oParentTable.Close();
	
	return TRUE;
}

bool CParent::EditParent(CParentData& oParent)
{
	CParentTable oParentTable(&g_dbConnection);

	PARENT stParent;
	stParent.iId = oParent.m_iParentId;
	FillDataFromObjectToStruct(stParent, oParent);

	if (!oParentTable.EditRec(stParent))
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		oParentTable.Close();
		return FALSE;
	}

	oParentTable.Close();
   	return TRUE;
}

 bool CParent::DeleteParents(const int nIdStudent)
 {
	 try
	 {
		 CParentTable oParentTable(&g_dbConnection);

		 PARENT stParent;
		 stParent.iStudentID = nIdStudent;

		 if (!oParentTable.DeleteRecords(stParent))
		 {
			 MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
			 oParentTable.Close();
			 return FALSE;
		 }

		 oParentTable.Close();
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error delete student!", MB_ICONEXCLAMATION);
		 return FALSE;
	 }

	 return TRUE;
 }

 bool CParent::DeleteOneParent(const int nIdParent)
 {
	 try
	 {
		CParentTable oParentTable(&g_dbConnection);

		PARENT stParent;
		stParent.iId = nIdParent;

		if (!oParentTable.DeleteRec(stParent))
		{
			MessageBox(NULL, "The record can't delete!", "Can't delete", MB_OK | MB_ICONERROR);
			oParentTable.Close();

			return FALSE;
		}

		oParentTable.Close();
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error delete student!", MB_ICONEXCLAMATION);
		 return FALSE;
	 }

	 return TRUE;
 }

 void FillDataFromStructToObject(CParentData& oParent, PARENT& recParent)
 {
	 oParent.m_iParentId = recParent.iId;
	 oParent.m_iStudentId = recParent.iStudentID;
	 oParent.m_strFirstName = recParent.sz_First_Name;
	 oParent.m_strLastName = recParent.sz_Last_Name;
	 oParent.m_strPhoneNumber = recParent.szPhoneNumber;
	 oParent.m_strEmail = recParent.szEmail;
	 oParent.m_strCity = recParent.szCity;
	 oParent.m_strPostCode = recParent.szPostCode;
	 oParent.m_strNeighborhood = recParent.szNeighborhood;
	 oParent.m_strAddress = recParent.szAddress;
 }

 bool CParent::PrintParentByStudent(const int& nIdStudent, list<CParentData>& lParent)
 {
	 CParentTable oParentTable(&g_dbConnection);
	 oParentTable.m_strFilter.Format("student_id = %d", nIdStudent);

	 oParentTable.Open();

	 if (!oParentTable.IsOpen())
	 {
		 MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		 oParentTable.Close();

		 return FALSE;
	 }

		 PARENT stParent;
		 CParentData oParent;

	 while (!oParentTable.IsEOF())
	 {
		oParentTable.GetRecStruct(stParent);
		FillDataFromStructToObject(oParent, stParent);
		oParent.m_eRecordMode = eRecordMode_None;
		lParent.push_back(oParent);

		 oParentTable.MoveNext();
	 }

	 oParentTable.Close();
 }

 bool CParent::LoadParent(CParentData& oParent)
 {
	 try
	 {
		 CParentTable oParentTable(&g_dbConnection);
		 PARENT recParent;
		 recParent.iId = oParent.m_iParentId;
		 oParentTable.LoadParent(recParent);

		 FillDataFromStructToObject(oParent, recParent);
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error load parent!", MB_ICONEXCLAMATION);
		 return FALSE;
	 }
	 return TRUE;
 }