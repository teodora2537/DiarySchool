#include "pch.h"
#include "Subject.h"

int roomNumber;
CString nameSubject, fullNameTeacher;
string fNameTeacher, lNameTeacher;

CSubjectData::CSubjectData(int _roomNumber, CString _nameSubject, string _fNameTeacher, string _lNameTeacher)
{
    roomNumber=_roomNumber;
    nameSubject = _nameSubject;
    fNameTeacher = _fNameTeacher;
    lNameTeacher = _lNameTeacher;
}

CSubjectData::CSubjectData()
{
}

string CSubjectData::GetFirstNameTeacher()
{
    return fNameTeacher;
}

void CSubjectData::SetFirstNameTeacher(string _firstNameTeacher)
{
    fNameTeacher = _firstNameTeacher;
}

string CSubjectData::GetLastNameTeacher()
{
    return lNameTeacher;
}

void CSubjectData::SetLastNameTeacher(string _lastNameTeacher)
{
    lNameTeacher = _lastNameTeacher;
}

CString CSubjectData::GetNameSubject()
{
    return nameSubject;
}

void CSubjectData::SetNameSubject(CString _nameSubject)
{
    nameSubject = _nameSubject;
}

int CSubjectData::GetRoomNumber()
{
    return roomNumber;
}

void CSubjectData::SetRoomNumber(int _roomNumber)
{
    roomNumber = _roomNumber;
}

CString CSubjectData::GetFullNameTeacher()
{
    return fullNameTeacher;
}

void CSubjectData::SetFullNameTeacher(CString _fullNameTeacher)
{
    fullNameTeacher = _fullNameTeacher;
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
    return false;
}

bool CSubject::EditSubject(const CSubjectData& oSubject)
{
    return false;
}

bool CSubject::LoadSubject(const int nClassNumber, CSubjectData& oSubject)
{
    return false;
}

bool CSubject::DeleteSubject(const int nClassNumber)
{
    return false;
}
