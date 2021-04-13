#pragma once
#include <string>
#include <map>
#include <vector>
#include <list>
#include "CListMethods.h"
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

	void AvgScoreBySubject(list<ReferenceStruct>& m_listReference);
	void AvgScoreByAllSubject(list<ReferenceStruct>& m_listReference);
	void ExcellentStud(list<ReferenceStruct>& m_listReference);
	void PeopleHaveBirthday(list<ReferenceStruct>& m_listReference);
	void remedialExaminationBySub(list<ReferenceStruct>& m_listReference);
	void remedialExaminationByMoreSub(list<ReferenceStruct>& m_listReference);
	void PrintStudent_(list<StudentStruct>& m_listStudent);
};
