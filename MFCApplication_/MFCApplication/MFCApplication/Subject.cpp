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

//	! you must use the parametter nClassNumber
bool CSubject::DeleteSubject(const int nClassNumber)
{
	CSubjectData subject;
	Library lib;
	int roomNum = subject.GetRoomNumber();
	string _subject = lib.ConvertToStirng(subject.GetNameSubject(), "");
	string fName = subject.GetFirstNameTeacher();
	string lName = subject.GetLastNameTeacher();

	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	CSubjectData currentSubject;
	bool isFind = false;
	map<int, vector<string>> mapSubject;

	file.open("Subject.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentSubject.SetRoomNumber(stoi(token));
			else if (count == 2)
			{
				CString cstr(token.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (count == 3) currentSubject.SetFirstNameTeacher(token);
			else if (count == 4) { currentSubject.SetLastNameTeacher(token); break; }
			text = text.substr(position + 1, text.length());
		}

		if (currentSubject.GetRoomNumber() == roomNum)
		{
			isFind = true;
			continue;
		}

		mapSubject[currentSubject.GetRoomNumber()].push_back(lib.ConvertToStirng(currentSubject.GetNameSubject(), ""));
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);

		for (auto i = mapSubject.begin(); i != mapSubject.end(); i++)
		{
			outFile << (*i).first << '|' << (*i).second[0] << '|' << (*i).second[1] << '|' << (*i).second[2] << "\n";
		}
		outFile.close();

		return true;
	}
	else return false;
}

map<int, vector<string>> CSubject::PrintSubject() {
	Library lib;
	int count = 0;
	string text;
	string token;
	fstream file;
	size_t position;
	CSubjectData currentSubject;
	bool isFind = false;
	map<int, vector<string>> mapSubject;

	file.open("Subject.txt", ios::in);

	while (getline(file, text))
	{
		position = 0;
		count = 0;
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1) currentSubject.SetRoomNumber(stoi(token));
			else if (count == 2) {
				CString cstr(token.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (count == 3) currentSubject.SetFirstNameTeacher(token);
			else if (count == 4) { currentSubject.SetLastNameTeacher(token); break; }
			text = text.substr(position + 1, text.length());
		}

		mapSubject[currentSubject.GetRoomNumber()].push_back(lib.ConvertToStirng(currentSubject.GetNameSubject(), ""));
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	file.close();

	return mapSubject;
}