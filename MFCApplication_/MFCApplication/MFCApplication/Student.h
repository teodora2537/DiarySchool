#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;
class CStudentData
{
protected:

public:

	CStudentData(int _classNum, string fName, string lName, string birthday);
	CStudentData();
	
	string m_strFirstName;
	string m_strLastName;
	string m_strBirthday;
	CString m_cstrFullName;
	int m_iClassNumber;

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
	
	map<int, vector<string>> PrintStudent();
	
	map<int, vector<string>> AverageScoreBySubject();
	map<int, vector<string>> AverageScoreByAllSubject();
	
	vector<string> ExcellentStudent();
	vector<string> PeopleHaveBirthdayToday();
	
	map<int, vector<string>> remedialExaminationBySubject();
	vector<string> remedialExaminationByMoreSubjects();
};