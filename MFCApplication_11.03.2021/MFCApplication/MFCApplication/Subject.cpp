#include "pch.h"
#include "Subject.h"
#include <fstream>
#include "Library.h"

CSubjectData::CSubjectData(int _roomNumber, CString _nameSubject, CString _fNameTeacher, CString _lNameTeacher)
{
    m_iRoomNumber=_roomNumber;
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
    ofstream outFile;
    outFile.open("Subject.txt", ios::app);
	int m_iRoomNumber = oSubjectData.m_iRoomNumber;
	CString m_cstrSubject = oSubjectData.m_strNameSubject;
	CString m_strFNTeacher = oSubjectData.m_strFNameTeacher;
	CString m_strLNTeacher = oSubjectData.m_strLNameTeacher;

	outFile << m_iRoomNumber << DEF_FILE_DATA_SEPARATOR 
			<< m_cstrSubject << DEF_FILE_DATA_SEPARATOR 
			<< m_strFNTeacher << DEF_FILE_DATA_SEPARATOR 
			<< m_strLNTeacher << "\n";
	 outFile.close();

    return true;
}

bool CSubject::EditSubject(const CSubjectData& oSubject) {
	fstream m_file;
	string m_strText;
	string m_strFileInfo;
	Library oLib;
	int m_sizeTPosition = 0;
	CString	m_strToken;
	m_file.open("Subject.txt", ios::in);
	while (getline(m_file, m_strText)) {

		m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
		m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
		//if id score is find => save changes else save line from file
		if (oSubject.m_iRoomNumber == atoi(m_strToken))
		{
			m_strFileInfo += to_string(oSubject.m_iRoomNumber) + DEF_FILE_DATA_SEPARATOR +
				oLib.ConvertToString(oSubject.m_strNameSubject,"") + DEF_FILE_DATA_SEPARATOR +
				oLib.ConvertToString(oSubject.m_strFNameTeacher, "") + DEF_FILE_DATA_SEPARATOR +
				oLib.ConvertToString(oSubject.m_strLNameTeacher,"") + DEF_FILE_DATA_SEPARATOR + "\n";
		}
		else {
			m_strFileInfo += m_strText + "\n";
		}
	}
	m_file.close();

	//save string in file
	ofstream outFile;
	outFile.open("Subject.txt", ios::out | ios::trunc);
	//Set score in the file.
	outFile << m_strFileInfo;
	outFile.close();

	return true;
}

/*
bool CSubject::EditSubject(const CSubjectData& oSubject)
{
	int m_iRoomNum;
	CString m_strFName;
	CString m_strLName;
	CString m_strSubject;

	int m_iCount = 0;
	string m_strText;
	CString m_strToken;
	size_t m_sizeTPosition;
	bool m_bIsFind = false;
	map<int, vector<CString>> m_mapSubjects;

	//Datas from edit boxes
	Library oLib;
	m_iRoomNum = oSubject.m_iRoomNumber;
	m_strFName = oSubject.m_strFNameTeacher;
	m_strLName = oSubject.m_strLNameTeacher;
	m_strSubject = oSubject.m_strNameSubject;

	fstream m_file;
	CSubjectData currentSubject;

	m_file.open("Subject.txt", ios::in);
	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		// set data's subject to class subject
		while (true)
		{
			m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
			m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
			m_iCount++;
			if (m_iCount == 1)currentSubject.m_iRoomNumber = atoi(m_strToken);
			if (m_iCount == 2)
			{
				currentSubject.m_strNameSubject = m_strToken;
			}
			else if (m_iCount == 3) currentSubject.m_strFNameTeacher = m_strToken;
			else if (m_iCount == 4) { currentSubject.m_strLNameTeacher = m_strToken; break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}
		//if subject exist (from edit box) save it and continue. 
		if (currentSubject.m_iRoomNumber == m_iRoomNum ||
			(currentSubject.m_strFNameTeacher == m_strFName &&  currentSubject.m_strLNameTeacher == m_strLName) ||
			 currentSubject.m_strNameSubject == m_strSubject)
		{
			m_mapSubjects[m_iRoomNum].push_back(m_strSubject);
			m_mapSubjects[m_iRoomNum].push_back(m_strFName);
			m_mapSubjects[m_iRoomNum].push_back(m_strLName);
			m_bIsFind = true;
			continue;
		}
		//save subject from file
		m_mapSubjects[currentSubject.m_iRoomNumber].push_back(currentSubject.m_strNameSubject);
		m_mapSubjects[currentSubject.m_iRoomNumber].push_back(currentSubject.m_strFNameTeacher);
		m_mapSubjects[currentSubject.m_iRoomNumber].push_back(currentSubject.m_strLNameTeacher);
	}
	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);
		//Set subject in the file.
		for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
		{
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[0] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[1] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}
*/

bool CSubject::LoadSubject(const int nRoomId, CSubjectData& oSubject)
{
	map<int, vector<CString>> m_mapSubjects;
	PrintSubject(m_mapSubjects);
	oSubject.m_iRoomNumber = nRoomId;
	oSubject.m_strNameSubject  = m_mapSubjects[nRoomId][0];
	oSubject.m_strFNameTeacher = m_mapSubjects[nRoomId][1];
	oSubject.m_strLNameTeacher = m_mapSubjects[nRoomId][2];
    return true;
}

bool CSubject::DeleteSubject(const int nClassNumber) {
	
	fstream m_file;
	string m_strText;
	string m_strFileInfo;
	Library oLib;
	int m_sizeTPosition = 0;
	CString	m_strToken;

	m_file.open("Subject.txt", ios::in);

	while (getline(m_file, m_strText)) {
		m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
		m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
		//if id score is find => save changes else save line from file
		if (nClassNumber == atoi(m_strToken))
			continue;
		else
			m_strFileInfo += m_strText + "\n";
	}
	m_file.close();

	//save string in file
	ofstream outFile;
	outFile.open("Subject.txt", ios::out | ios::trunc);
	//Set score in the file.
	outFile << m_strFileInfo;
	outFile.close();
	return true;
}

/*
bool CSubject::DeleteSubject(const int nClassNumber)
{
	int m_iRoomNum;
	CString m_strFName;
	CString m_strLName;
	CString m_strSubject;
	int m_iCount = 0;
	string m_strText;
	CString m_strToken;
	size_t m_sizeTPosition;
	bool m_bIsFind = false;
	map<int, vector<CString>> m_mapSubjects;

	Library oLib;
	fstream m_file;
	CSubjectData currentSubject;

	m_file.open("Subject.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		while (true)
		{
			m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
			m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
			m_iCount++;
			if (m_iCount == 1) currentSubject.m_iRoomNumber = atoi(m_strToken);
			else if (m_iCount == 2) currentSubject.m_strNameSubject = m_strToken;
			else if (m_iCount == 3) currentSubject.m_strFNameTeacher = m_strToken;
			else if (m_iCount == 4) { currentSubject.m_strLNameTeacher = m_strToken; break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		if (currentSubject.m_iRoomNumber == nClassNumber)
		{
			m_bIsFind = true;
			continue;
		}

		m_mapSubjects[currentSubject.m_iRoomNumber].push_back(currentSubject.m_strNameSubject);
		m_mapSubjects[currentSubject.m_iRoomNumber].push_back(currentSubject.m_strFNameTeacher);
		m_mapSubjects[currentSubject.m_iRoomNumber].push_back(currentSubject.m_strLNameTeacher);
	}
	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);

		for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
		{
			outFile << (*i).first << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[0] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[1] << DEF_FILE_DATA_SEPARATOR 
					<< (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}
*/

 void CSubject::PrintSubject(map<int, vector<CString>>& m_mapSubjects) {
	
	 Library oLib;
	fstream m_file;
	CSubjectData oCurrentSubject;

	int m_iRoomNum;
	CString m_strFName;
	CString m_strLName;
	CString m_strSubject;
	int m_iCount = 0;
	string m_strText;
	CString m_strToken;
	size_t m_sizeTPosition;
	bool m_bIsFind = false;

	m_file.open("Subject.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		while (true)
		{
			m_sizeTPosition = m_strText.find(DEF_FILE_DATA_SEPARATOR);
			m_strToken = (m_strText.substr(0, m_sizeTPosition)).c_str();
			m_iCount++;
			if (m_iCount == 1) oCurrentSubject.m_iRoomNumber = atoi(m_strToken);
			else if (m_iCount == 2) {
				CString cstr(m_strToken);
				oCurrentSubject.m_strNameSubject = cstr;
			}
			else if (m_iCount == 3) oCurrentSubject.m_strFNameTeacher = m_strToken;
			else if (m_iCount == 4) { oCurrentSubject.m_strLNameTeacher = m_strToken; break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		m_mapSubjects[oCurrentSubject.m_iRoomNumber].push_back(oCurrentSubject.m_strNameSubject);
		m_mapSubjects[oCurrentSubject.m_iRoomNumber].push_back(oCurrentSubject.m_strFNameTeacher);
		m_mapSubjects[oCurrentSubject.m_iRoomNumber].push_back(oCurrentSubject.m_strLNameTeacher);
	}
	m_file.close();
}