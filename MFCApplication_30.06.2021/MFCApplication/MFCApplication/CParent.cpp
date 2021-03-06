#include "pch.h"
#include "CParent.h"
#include "Student.h"
#include "CParentTable.h"


 CParentData::CParentData()
 {
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
					return false;
				}
				
				break;
			case eRecordMode_Edit:
			
				if (!EditParent(*it)) {
					return false;
				}
				
				break;
			case eRecordMode_Delete:
				
				if (!DeleteOneParent(it->m_iParentId)) {
					return false;
				}
			
				break;
			case eRecordMode_View:
				
				if (!LoadParent(*it)) {
					return false;
				}
				
				break;
			default:
				break;
			}
		}
		return true;
}

void FillStructWithObjectData(PARENT& stParent, CParentData& oParent)
{
	stParent.iId = oParent.m_iParentId;
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

bool CParent::AddParent(CParentData & oParent)
{
	CParentTable oParentTable(&g_dbConnection);
	oParentTable.Open();
	
	if(!oParentTable.IsOpen())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		oParentTable.Close();

		return false;
	}

	if(!oParentTable.CanAppend())
	{
		MessageBox(NULL, "The table parent can't append!", "Can't append", MB_OK | MB_ICONERROR);
		oParentTable.Close();
		
		return false;
	}

	if (oParentTable.IsExist(oParent)) {
		return true;
	}

	oParentTable.AddNew();
	
	PARENT stParent;
	FillStructWithObjectData(stParent, oParent);

	oParentTable.Add_Edit_Parent(stParent);

	if (!oParentTable.Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		
		g_dbConnection.Rollback();
		oParentTable.Close();
		
		return false;
	}

	oParentTable.Close();
	
	return true;
}

bool CParent::EditParent(CParentData& oParent)
{
   CParentTable oParentTable(&g_dbConnection);

	oParentTable.m_strFilter.Format("id = '%d'", oParent.m_iParentId);

	oParentTable.Open();
	
	if (!oParentTable.IsOpen())
	{
		MessageBox(NULL, "The table Parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		oParentTable.Close();
		
		return false;
	}
	
	oParentTable.Edit();
	
	if (!oParent.m_strFirstName.IsEmpty()) {
		return true;
	}

	PARENT stParent;
	FillStructWithObjectData(stParent, oParent);

	oParentTable.Add_Edit_Parent(stParent);

	if (!oParentTable.Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		
		g_dbConnection.Rollback();
		oParentTable.Close();
		
		return false;
	}

	oParentTable.Close();
   
   	return true;
}

 bool CParent::DeleteParent(const int nIdStudent)
 {
	 try
	 {
		 CParentTable oParentTable(&g_dbConnection);
		 oParentTable.m_strFilter.Format("student_id = '%d'", nIdStudent);
		 oParentTable.Open();

		 if (!oParentTable.IsOpen())
		 {
			 MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			 oParentTable.Close();

			 return false;
		 }

		 if (oParentTable.m_str_first_name.IsEmpty())
		 {
			 oParentTable.Close();
			 
			 return true;
		 }

		 while (!oParentTable.IsEOF())
		 {
			oParentTable.Delete();
			oParentTable.MoveNext();
		 }
		
		 if (!oParentTable.IsDeleted())
		 {
			 MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			 oParentTable.Close();
			 
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

 bool CParent::DeleteOneParent(const int nIdParent)
 {
	 try
	 {
		CParentTable oParentTable(&g_dbConnection);
		oParentTable.m_strFilter.Format("id = '%d'", nIdParent);

		oParentTable.Open();

		if (!oParentTable.IsOpen())
		{
			MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			oParentTable.Close();
		
			return false;
		}

		oParentTable.Delete();
		
		if (!oParentTable.IsDeleted())
		 {
			 MessageBox(NULL, "The record isn't deleted!", "Isn't deleted", MB_OK | MB_ICONERROR);
			 oParentTable.Close();
			
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

 bool CParent::PrintParentByStudent(const int& nIdStudent, list<CParentData>& lParent)
 {
	 CParentTable oParentTable(&g_dbConnection);
	 oParentTable.m_strFilter.Format("student_id = %d", nIdStudent);

	 oParentTable.Open();

	 if (!oParentTable.IsOpen())
	 {
		 MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		 oParentTable.Close();

		 return false;
	 }

	 while (!oParentTable.IsEOF())
	 {
		 CParentData oParent;
	 
		 oParentTable.LoadParent(oParent);
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
		 oParentTable.m_strFilter.Format("id = '%d'", oParent.m_iParentId);

		 oParentTable.Open();

		 if (!oParentTable.IsOpen())
		 {
			 MessageBox(NULL, "The table Parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			 oParentTable.Close();
		
			 return false;
		 }

		 oParentTable.LoadParent(oParent);
	
		 oParentTable.Close();
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error load parent!", MB_ICONEXCLAMATION);
		 return false;
	 }
	 return true;
 }