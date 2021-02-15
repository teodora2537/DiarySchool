#include "pch.h"
#include "Student.h"
#include <string>
using namespace std;

string firstName;
string lastName;
string birthday;
CString fullName;
int classNumber;
//int status;

CStudentData::CStudentData(int _classNum, string _fName, string _lName, string _birthday)
{
	classNumber = _classNum;
	firstName = _fName;
	lastName = _lName;
	birthday = _birthday;
}

CStudentData::CStudentData()
{
}

string CStudentData::GetFirstName() {
	return firstName;
}
void CStudentData::SetFirstName(string _firstName) {
	firstName = _firstName;
}

string CStudentData::GetLastName() {
	return lastName;
}
void CStudentData::SetLastName(string _lastName) {
	lastName = _lastName;
}

string CStudentData::GetBirthday() {
	return birthday;
}
void CStudentData::SetBirthday(string _birthday) {
	birthday = _birthday;
}

int CStudentData::GetClassNumber() {
	return classNumber;
}
void CStudentData::SetClassNumber(int _classNumber) {
	classNumber = _classNumber;
}
CString CStudentData::GetFullName() {
	return fullName;
}
void CStudentData::SetFullName(CString _fullName) {
	fullName = _fullName;
}



CStudent::CStudent()
{
}

/*virtual*/
CStudent::~CStudent()
{
}


bool CStudent::AddStudent(CStudentData& oStudent)
{
	return true;
}