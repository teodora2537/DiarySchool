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
			if (!EditParent(*it)){
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

bool CParent::AddParent(CParentData& oParent)
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
	
	oParentTable.AddParent(oParent);

	//oParentTable.m_iIdStudent = nIdStudent;
	//oParentTable.m_str_first_name = arrParents.m_strFirstName;
	//oParentTable.m_str_last_name = arrParents.m_strLastName;
	//oParentTable.m_str_phone_number = arrParents.m_strPhoneNumber;
	//oParentTable.m_str_email = arrParents.m_strEmail;
	//oParentTable.m_str_city = arrParents.m_strCity;
	//oParentTable.m_str_post_code = arrParents.m_strPostCode;
	//oParentTable.m_str_neighborhood = arrParents.m_strNeighborhood;
	//oParentTable.m_str_address = arrParents.m_strAddress;

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
	
	if (oParentTable.IsExist(oParent)) {
		return true;
	}

	oParentTable.EditParent(oParent);

	//if datas is not change
	//if (oParentTable.m_iIdStudent == oParent.m_iStudentId &&
	//	oParentTable.m_str_first_name == oParent.m_strFirstName &&
	//	oParentTable.m_str_last_name == oParent.m_strLastName &&
	//	oParentTable.m_str_phone_number == oParent.m_strPhoneNumber &&
	//	oParentTable.m_str_email == oParent.m_strEmail &&
	//	oParentTable.m_str_city == oParent.m_strCity &&
	//	oParentTable.m_str_post_code == oParent.m_strPostCode &&
	//	oParentTable.m_str_neighborhood == oParent.m_strNeighborhood &&
	//	oParentTable.m_str_address == oParent.m_strAddress)
	//{
	//	oParentTable.Close();
	//
	//	return false;
	//}
	//save changes datas
	//oParentTable.m_iIdStudent = oParent.m_iStudentId;
	//oParentTable.m_str_first_name = oParent.m_strFirstName;
	//oParentTable.m_str_last_name = oParent.m_strLastName;
	//oParentTable.m_str_phone_number = oParent.m_strPhoneNumber;
	//oParentTable.m_str_email = oParent.m_strEmail;
	//oParentTable.m_str_city = oParent.m_strCity;
	//oParentTable.m_str_post_code = oParent.m_strPostCode;
	//oParentTable.m_str_neighborhood = oParent.m_strNeighborhood;
	//oParentTable.m_str_address = oParent.m_strAddress;

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

 //Print by struct
 bool CParent::PrintParent(const int& nIdStudent, list<PARENT>& lParent)
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
		 PARENT stParent;
		 stParent.iId = oParentTable.m_iId;
		 stParent.iStudentID = oParentTable.m_iIdStudent;
		 sprintf(stParent.szName, "%s", oParentTable.m_str_first_name + " " + oParentTable.m_str_last_name);
		 sprintf(stParent.szEmail, "%s", oParentTable.m_str_email);
		 sprintf(stParent.szPhoneNumber, "%s", oParentTable.m_str_phone_number);
		 sprintf(stParent.szCity, "%s", oParentTable.m_str_city);
		 sprintf(stParent.szPostCode, "%s", oParentTable.m_str_post_code);
		 sprintf(stParent.szNeighborhood, "%s", oParentTable.m_str_neighborhood);
		 sprintf(stParent.szAddress, "%s", oParentTable.m_str_address);
		 lParent.push_back(stParent);

		 oParentTable.MoveNext();
	 }

	 oParentTable.Close();
 }

 //Print by class
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
		 //oParent.m_iParentId = oParentTable.m_iId;
		 //oParent.m_iStudentId = oParentTable.m_iIdStudent;
		 //oParent.m_strFirstName = oParentTable.m_str_first_name;
		 //oParent.m_strLastName = oParentTable.m_str_last_name;
		 //oParent.m_strEmail = oParentTable.m_str_email;
		 //oParent.m_strPhoneNumber = oParentTable.m_str_phone_number;
		 //oParent.m_strCity = oParentTable.m_str_city;
		 //oParent.m_strPostCode = oParentTable.m_str_post_code;
		 //oParent.m_strNeighborhood = oParentTable.m_str_neighborhood;
		 //oParent.m_strAddress = oParentTable.m_str_address;
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

		 //oParent.m_iParentId = oParentTable.m_iId;
		 //oParent.m_iStudentId = oParentTable.m_iIdStudent;
		 //oParent.m_strFirstName = oParentTable.m_str_first_name;
		 //oParent.m_strLastName = oParentTable.m_str_last_name;
		 //oParent.m_strPhoneNumber = oParentTable.m_str_phone_number;
		 //oParent.m_strEmail = oParentTable.m_str_email;
		 //oParent.m_strCity = oParentTable.m_str_city;
		 //oParent.m_strPostCode =  oParentTable.m_str_post_code;
		 //oParent.m_strNeighborhood =  oParentTable.m_str_neighborhood;
		 //oParent.m_strAddress = oParentTable.m_str_address;
	
		 oParentTable.Close();
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error load parent!", MB_ICONEXCLAMATION);
		 
		 return false;
	 }
	 return true;
 }
 