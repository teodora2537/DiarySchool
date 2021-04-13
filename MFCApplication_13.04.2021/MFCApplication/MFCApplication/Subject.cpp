#include "pch.h"
#include "Subject.h"
#include <fstream>
#include "Library.h"
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

bool CSubject::AddSubject(const CSubjectData& oSubjectData)
{
	CString ConnectionString;
	CDatabase db;

	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	CString SqlString;
	CString strID, strName;

	if (db.Open(NULL, FALSE, FALSE, ConnectionString, TRUE))
	{
		TRY{
			SqlString = "INSERT INTO Student (first_name, last_name, birth_date) VALUES ('" + oSubjectData.m_strNameSubject + "','" + oSubjectData.m_strFNameTeacher + "','" + oSubjectData.m_strLNameTeacher + "')";
			db.ExecuteSQL(SqlString);

			// Close the database
			db.Close();
		}CATCH(CDBException, e) {
			return false;
		}
		END_CATCH;
	}
	else return false;
	return true;
}

bool CSubject::EditSubject(const CSubjectData& oSubject) {
	
	Library oLib;
	CDatabase db;
	CString SqlString, ConnectionString;
	CString strID, strName;
	int iRec = 0;

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	TRY{
		// Open the database
	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	db.ExecuteSQL("UPDATE Subject SET subject ='" + oSubject.m_strNameSubject + "' WHERE id = '" + oLib.IntToCString(oSubject.m_iRoomNumber) + "';");
	db.ExecuteSQL("UPDATE Subject SET first_name_teacher ='" + oSubject.m_strFNameTeacher + "' WHERE id = '" + oLib.IntToCString(oSubject.m_iRoomNumber) + "';");
	db.ExecuteSQL("UPDATE Subject SET last_name_teacher ='" + oSubject.m_strLNameTeacher + "' WHERE id = '" + oLib.IntToCString(oSubject.m_iRoomNumber) + "';");

	// Close the database
	db.Close();
	}CATCH(CDBException, e) {
		return false;
	}
	END_CATCH;
	return true;
}

bool CSubject::LoadSubject(const int nRoomId, CSubjectData& oSubject)
{
	Library oLib;
	CDatabase db;
	CString SqlString, ConnectionString;
	CString m_strID, m_strFName, m_strLName, m_strfSubject;

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";
	TRY{
	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	// Allocate the recordset
	CRecordset recset(&db);

	// Execute the query
	recset.Open(CRecordset::forwardOnly, "SELECT * FROM Subject WHERE id = '" + oLib.IntToCString(nRoomId) + "';", CRecordset::readOnly);

	CString m_strIdRoom;
	recset.GetFieldValue("id",m_strIdRoom);
	oSubject.m_iRoomNumber = atoi(m_strIdRoom);
	recset.GetFieldValue("subject", oSubject.m_strNameSubject);
	recset.GetFieldValue("first_name_teacher", oSubject.m_strFNameTeacher);
	recset.GetFieldValue("last_name_teacher", oSubject.m_strLNameTeacher);

	db.Close();
	}CATCH(CDBException, e) {
		return false;
	}
	END_CATCH;
	return true;
}

bool CSubject::DeleteSubject(const int nClassNumber) {
	CString SqlString;
	CString ConnectionString;
	CDatabase db;
	Library oLib;
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	TRY{
		// Open the database
	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	// Allocate the recordset
	CRecordset recset(&db);

	SqlString = "DELETE FROM Subject WHERE id = '" + oLib.IntToCString(nClassNumber) + "';";

	db.ExecuteSQL(SqlString);
	}CATCH(CDBException, e) {
		return false;
	}
	END_CATCH;
	return true;
}

void CSubject::PrintSub(list<SubStruct>& listSub)
{
	CDatabase db;
	CString SqlString, ConnectionString;
	CString m_strID, m_strFName, m_strLName, m_strSub;
	CDBVariant varValueBirthday;
	// Allocate the recordset
	CRecordset recset(&db);

	// Build ODBC connection string
	ConnectionString = "Driver={SQL Server};Server=db-mp-vn01, 16333; Database=DiarySchool;";

	db.OpenEx(ConnectionString, CDatabase::noOdbcDialog);

	SqlString = "SELECT * FROM Subject";

	// Execute the query
	recset.Open(CRecordset::forwardOnly, SqlString, CRecordset::readOnly);
	Library oLib;

	while (!recset.IsEOF()) {
		// Copy each column into a variable
		recset.GetFieldValue("id", m_strID);
		recset.GetFieldValue("subject", m_strSub);
		recset.GetFieldValue("first_name_teacher", m_strFName);
		recset.GetFieldValue("last_name_teacher", m_strLName);

		SubStruct subStruct = {atoi(m_strID), m_strSub, m_strFName+" "+m_strLName};
		listSub.push_back(subStruct);
		recset.MoveNext();
	}

	db.Close();

}
