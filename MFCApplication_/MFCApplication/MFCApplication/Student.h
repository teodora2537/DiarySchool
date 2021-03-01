#pragma once
#include <string>
#include <map>
#include <vector>
using namespace std;
class CStudentData
{
protected:

public:

	CStudentData(int _classNum, CString fName, CString lName, CString birthday);
	CStudentData();
	
	CString m_strFirstName;
	CString m_strLastName;
	CString m_strBirthday;
	CString m_strFullName;
	int m_iClassNumber;
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
	
	void PrintStudent(map<int, vector<CString>>& m_mapAllStudent);
	
	void AverageScoreBySubject(map<int, vector<CString>>& m_mapAverageScoreBySub);
	void AverageScoreByAllSubject(map<int, vector<CString>>& m_mapAverageScore);
	
	void ExcellentStudent(vector<CString>& m_vecStudentsName);
	void PeopleHaveBirthdayToday(vector<CString>& m_vecStudentsName);
	
	void remedialExaminationBySubject(map<int, vector<CString>>& m_mapAverageScore);
	void remedialExaminationByMoreSubjects(vector<CString>& m_vecStudentsName);
};
