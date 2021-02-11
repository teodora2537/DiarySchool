#include "pch.h"
#include "Subject.h"

int roomNumber;
CString nameSubject;
string fNameTeacher;
string lNameTeacher;
CString fullNameTeacher;

Subject::Subject(int _roomNumber, CString _nameSubject, string _fNameTeacher, string _lNameTeacher)
{
    roomNumber=_roomNumber;
    nameSubject = _nameSubject;
    fNameTeacher = _fNameTeacher;
    lNameTeacher = _lNameTeacher;
}

Subject::Subject()
{
}

string Subject::GetFirstNameTeacher()
{
    return fNameTeacher;
}

void Subject::SetFirstNameTeacher(string _firstNameTeacher)
{
    fNameTeacher = _firstNameTeacher;
}

string Subject::GetLastNameTeacher()
{
    return lNameTeacher;
}

void Subject::SetLastNameTeacher(string _lastNameTeacher)
{
    lNameTeacher = _lastNameTeacher;
}

CString Subject::GetNameSubject()
{
    return nameSubject;
}

void Subject::SetNameSubject(CString _nameSubject)
{
    nameSubject = _nameSubject;
}

int Subject::GetRoomNumber()
{
    return roomNumber;
}

void Subject::SetRoomNumber(int _roomNumber)
{
    roomNumber = _roomNumber;
}

CString Subject::GetFullNameTeacher()
{
    return fullNameTeacher;
}

void Subject::SetFullNameTeacher(CString _fullNameTeacher)
{
    fullNameTeacher = _fullNameTeacher;
}
