#include "pch.h"
#include "Subject.h"
#include <fstream>
#include "Library.h"

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


CSubject::CSubject()
{
}

/*virtual*/
CSubject::~CSubject()
{
}

//	! you must use the parametter oSubject
bool CSubject::AddSubject(CSubjectData& oSubject)
{
    CSubjectData subject;
    ofstream outFile;
    outFile.open("Subject.txt", ios::app);
    outFile << subject.GetRoomNumber() << '|' << subject.GetNameSubject() << '|' << subject.GetFirstNameTeacher() << '|' << subject.GetLastNameTeacher() << "\n";
    outFile.close();

    return true;
}

//	! you must use the parametter oSubject
bool CSubject::EditSubject(const CSubjectData& oSubject)
{
	//Datas from edit boxes
	CSubjectData subject;
	Library lib;
	int roomNum = subject.GetRoomNumber();
	string fName = subject.GetFirstNameTeacher();
	string lName = subject.GetLastNameTeacher();
	string _subject = lib.ConvertToStirng(subject.GetNameSubject(), "");


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
		// set data's subject to class subject
		while (true)
		{
			position = text.find('|');
			token = text.substr(0, position);
			count++;
			if (count == 1)currentSubject.SetRoomNumber(stoi(token));
			if (count == 2)
			{
				CString cstr(token.c_str());
				currentSubject.SetNameSubject(cstr);
			}
			else if (count == 3) currentSubject.SetFirstNameTeacher(token);
			else if (count == 4) { currentSubject.SetLastNameTeacher(token); break; }
			text = text.substr(position + 1, text.length());
		}
		//if subject exist (from edit box) save it and continue. 
		if (currentSubject.GetRoomNumber() == roomNum ||
			(currentSubject.GetFirstNameTeacher() == fName && currentSubject.GetLastNameTeacher() == lName) ||
			lib.ConvertToStirng(currentSubject.GetNameSubject(), "") == _subject)
		{
			mapSubject[roomNum].push_back(_subject);
			mapSubject[roomNum].push_back(fName);
			mapSubject[roomNum].push_back(lName);
			isFind = true;
			continue;
		}
		//save subject from file
		mapSubject[currentSubject.GetRoomNumber()].push_back(lib.ConvertToStirng(currentSubject.GetNameSubject(), ""));
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetFirstNameTeacher());
		mapSubject[currentSubject.GetRoomNumber()].push_back(currentSubject.GetLastNameTeacher());
	}
	file.close();

	if (isFind)
	{
		ofstream outFile;
		outFile.open("Subject.txt", ios::out | ios::trunc);
		//Set subject in the file.
		for (auto i = mapSubject.begin(); i != mapSubject.end(); i++)
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