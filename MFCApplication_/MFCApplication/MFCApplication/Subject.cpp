#include "pch.h"
#include "Subject.h"
#include <fstream>
#include "Library.h"
#include "CAddSubject.h"

CSubjectData::CSubjectData(int _roomNumber, CString _nameSubject, string _fNameTeacher, string _lNameTeacher)
{
    m_iRoomNumber=_roomNumber;
    m_cstrNameSubject = _nameSubject;
    m_strFNameTeacher = _fNameTeacher;
    m_strLNameTeacher = _lNameTeacher;
}

CSubjectData::CSubjectData()
{
}

string CSubjectData::GetFirstNameTeacher()
{
    return m_strFNameTeacher;
}

void CSubjectData::SetFirstNameTeacher(string _firstNameTeacher)
{
	m_strFNameTeacher = _firstNameTeacher;
}

string CSubjectData::GetLastNameTeacher()
{
    return m_strLNameTeacher;
}

void CSubjectData::SetLastNameTeacher(string _lastNameTeacher)
{
	m_strLNameTeacher = _lastNameTeacher;
}

CString CSubjectData::GetNameSubject()
{
    return m_cstrNameSubject;
}

void CSubjectData::SetNameSubject(CString _nameSubject)
{
    m_cstrNameSubject = _nameSubject;
}

int CSubjectData::GetRoomNumber()
{
    return m_iRoomNumber;
}

void CSubjectData::SetRoomNumber(int _roomNumber)
{
    m_iRoomNumber = _roomNumber;
}

CString CSubjectData::GetFullNameTeacher()
{
    return m_cstrFullNameTeacher;
}

void CSubjectData::SetFullNameTeacher(CString _fullNameTeacher)
{
	m_cstrFullNameTeacher = _fullNameTeacher;
}


bool CSubjectData::GetFlagIsUpdate()
{
	return m_bIsUpdate;
}

void CSubjectData::SetFlagIsUpdate(bool _bIsUpdate)
{
	m_bIsUpdate = _bIsUpdate;
}

CSubject::CSubject()
{
}

/*virtual*/
CSubject::~CSubject()
{
}

bool CSubject::AddSubject(CSubjectData& oSubject)
{
	Library oLib;
    ofstream outFile;
    outFile.open("Subject.txt", ios::app);
	int m_iRoomNumber = oSubject.GetRoomNumber();
	string m_cstrSubject = oLib.ConvertToStirng(oSubject.GetNameSubject(), "");
	string m_strFNTeacher = oSubject.GetFirstNameTeacher();
	string m_strLNTeacher = oSubject.GetLastNameTeacher();

	outFile << m_iRoomNumber << '|' << m_cstrSubject << '|' << m_strFNTeacher << '|' << m_strLNTeacher << "\n";
	 outFile.close();

    return true;
}

//bool CSubject::EditSubject(const CSubjectData& oSubject)
bool CSubject::EditSubject(CSubjectData& oSubject)
{
	//Datas from edit boxes
	Library oLib;
	m_iRoomNum = oSubject.GetRoomNumber();
	m_strFName = oSubject.GetFirstNameTeacher();
	m_strLName = oSubject.GetLastNameTeacher();
	m_strSubject = oLib.ConvertToStirng(oSubject.GetNameSubject(), "");

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
			m_sizeTPosition = m_strText.find('|');
			m_strToken = m_strText.substr(0, m_sizeTPosition);
			m_iCount++;
			if (m_iCount == 1)currentSubject.SetRoomNumber(stoi(m_strToken));
			if (m_iCount == 2)
			{
				CString cstr(m_strToken.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (m_iCount == 3) currentSubject.SetFirstNameTeacher(m_strToken);
			else if (m_iCount == 4) { currentSubject.SetLastNameTeacher(m_strToken); break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}
		//if subject exist (from edit box) save it and continue. 
		if (currentSubject.GetRoomNumber() == m_iRoomNum ||
			(currentSubject.GetFirstNameTeacher() == m_strFName && currentSubject.GetLastNameTeacher() == m_strLName) ||
			oLib.ConvertToStirng(currentSubject.GetNameSubject(), "") == m_strSubject)
		{
			m_mapSubjects[m_iRoomNum].push_back(m_strSubject);
			m_mapSubjects[m_iRoomNum].push_back(m_strFName);
			m_mapSubjects[m_iRoomNum].push_back(m_strLName);
			m_bIsFind = true;
			continue;
		}
		//save subject from file
		m_mapSubjects[currentSubject.GetRoomNumber()].push_back(oLib.ConvertToStirng(currentSubject.GetNameSubject(), ""));
		m_mapSubjects[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		m_mapSubjects[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);
		//Set subject in the file.
		for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

//Empty
bool CSubject::LoadSubject(const int nClassNumber, CSubjectData& oSubject)
{

    return false;
}

bool CSubject::DeleteSubject(const int nClassNumber)
{
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
			m_sizeTPosition = m_strText.find('|');
			m_strToken = m_strText.substr(0, m_sizeTPosition);
			m_iCount++;
			if (m_iCount == 1) currentSubject.SetRoomNumber(stoi(m_strToken));
			else if (m_iCount == 2)
			{
				CString cstr(m_strToken.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (m_iCount == 3) currentSubject.SetFirstNameTeacher(m_strToken);
			else if (m_iCount == 4) { currentSubject.SetLastNameTeacher(m_strToken); break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		if (currentSubject.GetRoomNumber() == nClassNumber)//roomNum)
		{
			m_bIsFind = true;
			continue;
		}

		m_mapSubjects[currentSubject.GetRoomNumber()].push_back(oLib.ConvertToStirng(currentSubject.GetNameSubject(), ""));
		m_mapSubjects[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		m_mapSubjects[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	m_file.close();

	if (m_bIsFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);

		for (auto i = m_mapSubjects.begin(); i != m_mapSubjects.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

map<int, vector<string>> CSubject::PrintSubject() {
	Library oLib;
	fstream m_file;
	CSubjectData oCurrentSubject;

	m_file.open("Subject.txt", ios::in);

	while (getline(m_file, m_strText))
	{
		m_sizeTPosition = 0;
		m_iCount = 0;
		while (true)
		{
			m_sizeTPosition = m_strText.find('|');
			m_strToken = m_strText.substr(0, m_sizeTPosition);
			m_iCount++;
			if (m_iCount == 1) oCurrentSubject.SetRoomNumber(stoi(m_strToken));
			else if (m_iCount == 2) {
				CString cstr(m_strToken.c_str());
				oCurrentSubject.SetNameSubject(cstr);
			}
			else if (m_iCount == 3) oCurrentSubject.SetFirstNameTeacher(m_strToken);
			else if (m_iCount == 4) { oCurrentSubject.SetLastNameTeacher(m_strToken); break; }
			m_strText = m_strText.substr(m_sizeTPosition + 1, m_strText.length());
		}

		m_mapSubjects[oCurrentSubject.GetRoomNumber()].push_back(oLib.ConvertToStirng(oCurrentSubject.GetNameSubject(), ""));
		m_mapSubjects[oCurrentSubject.GetRoomNumber()].push_back(oCurrentSubject.GetFirstNameTeacher());
		m_mapSubjects[oCurrentSubject.GetRoomNumber()].push_back(oCurrentSubject.GetLastNameTeacher());
	}
	m_file.close();

	return m_mapSubjects;
}