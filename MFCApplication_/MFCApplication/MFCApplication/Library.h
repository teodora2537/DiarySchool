#pragma once
#include<string> 
#include<map> 
#include<vector> 
using namespace std;

enum DialogMode
{
	eDialogMode_Add = 1,
	eDialogMode_Edit = 2,
	eDialogMode_View = 3
};

class Library
{
public:
	Library(void);
	~Library(void);

	bool AddInStudent();
	bool AddInSubject();
	bool AddInScore();
	string ConvertToStirng(CString str_cstr, string row);
	bool UpdateStudent();
	bool UpdateSubject();
	bool UpdateScore();
	bool DeleteStudent();
	bool DeleteSubject();
	bool DeleteScore();
	map<int, vector<string>> PrintStudent();
	map<int, vector<string>> PrintSubject();
	multimap<int, vector<string>> PrintScore();
	map<int, vector<string>> AverageScoreBySubject_new();
	map<int, int> AverageScoreByAllSubject_new();
	vector<string> ExcellentStudent();
	vector<string> PeopleHaveBirthdayToday();
	map<int, vector<string>> remedialExaminationBySubject();
	vector<string> remedialExaminationByMoreSubjects();
};