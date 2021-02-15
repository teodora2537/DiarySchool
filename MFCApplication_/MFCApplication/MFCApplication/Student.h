#pragma once
#include<string>
using namespace std;
class CStudentData
{
protected:

public:

	CStudentData(int _classNum, string fName, string lName, string birthday);
	CStudentData();
	string GetFirstName();
	void SetFirstName(string firstName);
	
	string GetLastName();
	void SetLastName(string lastName);

	string GetBirthday();
	void SetBirthday(string birthday);

	int GetClassNumber();
	void SetClassNumber(int classNumber);
	CString GetFullName();
	void SetFullName(CString _fullName);
};



class CStudent
{
public:
	CStudent();
	virtual ~CStudent();

public:

	bool AddStudent(CStudentData& oStudent);
	bool EditStudent(const CStudentData& oStudent);
	bool LoadStudent(const int nClassNumber, CStudentData& oStudent);
	bool DeleteStudent(const int nClassNumber);
};