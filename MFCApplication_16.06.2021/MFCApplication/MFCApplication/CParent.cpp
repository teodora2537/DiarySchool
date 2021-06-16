#include "pch.h"
#include "CParent.h"
#include "Student.h"
#include "CParentTable.h"

extern CDatabase g_dbConnection;

bool CParent::AddParent(CParentData& oParent)
{
	CParentTable oParentTable(&g_dbConnection);
	oParentTable.Open();
	
	if(!oParentTable.IsOpen())
	{
		MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		return false;
	}
		//Parent is exist
		while (!oParentTable.IsEOF())
		{
			if (oParentTable.m_iIdStudent == oParent.m_iStudentId &&
				oParentTable.m_str_first_name == oParent.m_strFirstName &&
				oParentTable.m_str_last_name == oParent.m_strLastName)
			{
				MessageBox(NULL, "The parent is exist!", "IsExist", MB_OK | MB_ICONERROR);
				return true;
			}

			oParentTable.MoveNext();
		}

	if(!oParentTable.CanAppend())
	{
		MessageBox(NULL, "The table parent can't append!", "Can't append", MB_OK | MB_ICONERROR);
		return true;
	}

	oParentTable.AddNew();
	
	oParentTable.m_iIdStudent = oParent.m_iStudentId;
	oParentTable.m_str_first_name =	oParent.m_strFirstName;
	oParentTable.m_str_last_name =	oParent.m_strLastName;
	oParentTable.m_str_phone_number = oParent.m_strPhoneNumber;
	oParentTable.m_str_email = oParent.m_strEmail;
	oParentTable.m_str_city = oParent.m_strCity;
	oParentTable.m_str_post_code = oParent.m_strPostCode;
	oParentTable.m_str_neighborhood = oParent.m_strNeighborhood;
	oParentTable.m_str_address = oParent.m_strAddress;

	if(!oParentTable.Update())
	{
		MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
		return true;
	}

	oParentTable.Close();
	return false;
}

bool CParent::EditParent(CParentData& oParent)
{
   CParentTable oParentTable(&g_dbConnection);
   
   CString strWhere;
   strWhere.Format("id = '%d'", oParent.m_iParentId);

   oParentTable.m_strFilter = strWhere;

   oParentTable.Open();
   
   if (!oParentTable.IsOpen())
   {
   	MessageBox(NULL, "The table Parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
   	return false;
   }
   
   oParentTable.Edit();
   
   	if (oParentTable.m_iIdStudent == oParent.m_iStudentId &&
		oParentTable.m_str_first_name == oParent.m_strFirstName &&
   		oParentTable.m_str_last_name == oParent.m_strLastName &&
   		oParentTable.m_str_phone_number == oParent.m_strPhoneNumber &&
   		oParentTable.m_str_email == oParent.m_strEmail &&
   		oParentTable.m_str_city == oParent.m_strCity &&
   		oParentTable.m_str_post_code == oParent.m_strPostCode &&
   		oParentTable.m_str_neighborhood == oParent.m_strNeighborhood &&
   		oParentTable.m_str_address == oParent.m_strAddress)
   		return true;
   
   		oParentTable.m_iIdStudent = oParent.m_iStudentId;
   		oParentTable.m_str_first_name = oParent.m_strFirstName;
   		oParentTable.m_str_last_name = oParent.m_strLastName;
   		oParentTable.m_str_phone_number = oParent.m_strPhoneNumber;
   		oParentTable.m_str_email = oParent.m_strEmail;
   		oParentTable.m_str_city = oParent.m_strCity;
   		oParentTable.m_str_post_code = oParent.m_strPostCode;
   		oParentTable.m_str_neighborhood = oParent.m_strNeighborhood;
   		oParentTable.m_str_address = oParent.m_strAddress;

   if (!oParentTable.Update())
   {
   	MessageBox(NULL, "The record can't update!", "Can't update", MB_OK | MB_ICONERROR);
   	return false;
   }
   
   	return true;
}
 
//Ne Raboti -zaradi relationship with Student
 bool CParent::DeleteParent(const int nIdStudent)
 {
	 try
	 {
		 CString strWhere;
		 strWhere.Format("student_id = '%d'", nIdStudent);

		 CParentTable oParentTable(&g_dbConnection);
		 oParentTable.m_strFilter = strWhere;
		 oParentTable.Open();

		 if (!oParentTable.IsOpen())
		 {
			 MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			 return false;
		 }

			 oParentTable.Delete();
		
		 if (!oParentTable.IsDeleted())
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

 bool CParent::PrintParent(const int& nIdStudent, list<PARENT>& lParent)
 {
	 CParentTable oParentTable(&g_dbConnection);
	 oParentTable.Open();

	 if (!oParentTable.IsOpen())
	 {
		 MessageBox(NULL, "The table parent isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
		 return false;
	 }
	 //Parent is exist
	 while (!oParentTable.IsEOF())
	 {
		 if (oParentTable.m_iIdStudent != nIdStudent)
		 {
			 oParentTable.MoveNext();
			 continue;
		 }

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
 }

 bool CParent::LoadParent(const int nParentId, CParentData& oParent)
 {
	 try
	 {
		 CString strWhere;
		 strWhere.Format("id = '%d'", nParentId);

		 CParentTable oParentTable(&g_dbConnection);
		 oParentTable.m_strFilter = strWhere;
		 oParentTable.Open();

		 if (!oParentTable.IsOpen())
		 {
			 MessageBox(NULL, "The table Student isn't open!", "Isn't open", MB_OK | MB_ICONERROR);
			 return false;
		 }

		 oParent.m_iParentId = oParentTable.m_iId;
		 oParent.m_iStudentId = oParentTable.m_iIdStudent;
		 oParent.m_strFirstName = oParentTable.m_str_first_name;
		 oParent.m_strLastName = oParentTable.m_str_last_name;
		 oParent.m_strPhoneNumber = oParentTable.m_str_phone_number;
		 oParent.m_strEmail = oParentTable.m_str_email;
		 oParent.m_strCity = oParentTable.m_str_city;
		 oParent.m_strPostCode =  oParentTable.m_str_post_code;
		 oParent.m_strNeighborhood =  oParentTable.m_str_neighborhood;
		 oParent.m_strAddress = oParentTable.m_str_address;
	 }
	 catch (exception e)
	 {
		 AfxMessageBox("Error load student!", MB_ICONEXCLAMATION);
		 return false;
	 }
	 return true;
 }
 
 CParentData::CParentData()
 {
 }
 
 CParentData::CParentData(int iParentId, int iStudentId, CString strFirstName, CString strLastName, CString strPhoneNumber, CString strEmail, CString strCity, CString strPostCode, CString strNeighborhood, CString strAddress)
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