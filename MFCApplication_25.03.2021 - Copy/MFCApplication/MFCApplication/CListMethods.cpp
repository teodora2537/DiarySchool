#include "pch.h"
#include "CListMethods.h"
#include "Score.h"
#include <iostream>
#include <list>
#include "CTabSubject.h"
using namespace std;

void CListMethods::SortListStudent(int sortClm, list<StudentStruct>& listFromStruct, SortOrder order)
{
	switch (order)
	{
	case SORT_AZ: 
			 if (sortClm == 0)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.nIdStudent < b.nIdStudent; });
		else if (sortClm == 1)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.strNameStudent < b.strNameStudent; });
		else if (sortClm == 2)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) {Library oLib; return oLib.CStringToDate(a.strBirthday) < oLib.CStringToDate(b.strBirthday); });
	break;
	
	case SORT_ZA: 
		     if (sortClm == 0)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.nIdStudent > b.nIdStudent; });
		else if (sortClm == 1)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.strNameStudent > b.strNameStudent; });
		else if (sortClm == 2)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) {Library oLib; return oLib.CStringToDate(a.strBirthday) > oLib.CStringToDate(b.strBirthday); });
	break;
	}
}

void CListMethods::SortListSub(int sortClm, list<SubStruct>& listFromStruct, SortOrder order)
{
	switch (order)
	{
	case SORT_AZ:
			 if (sortClm == 0)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.strIdRoom < b.strIdRoom; });
		else if (sortClm == 1)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.strSubject < b.strSubject; });
		else if (sortClm == 2)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.strNameTeacher < b.strNameTeacher; });
	break;

	case SORT_ZA:
			 if (sortClm == 0)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.strIdRoom > b.strIdRoom; });
		else if (sortClm == 1)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.strSubject > b.strSubject; });
		else if (sortClm == 2)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.strNameTeacher > b.strNameTeacher; });
		break;
	}
}

void CListMethods::SortListScore(int sortClm, list<ScoreStruct>& listFromStruct, SortOrder order) {
	switch (order)
	{
		case SORT_AZ:
				 if (sortClm == 0)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strIdStudent < b.strIdStudent; });
			else if (sortClm == 1)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strNameStudent < b.strNameStudent; });
			else if (sortClm == 2)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strSubject < b.strSubject; });
			else if (sortClm == 3)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strScore < b.strScore; });
			else if (sortClm == 4)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) {Library oLib; return oLib.CStringToDate(a.strDate) < oLib.CStringToDate(b.strDate); });
		break;
		
		case SORT_ZA:
				 if (sortClm == 0)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strIdStudent > b.strIdStudent; });
			else if (sortClm == 1)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strNameStudent > b.strNameStudent; });
			else if (sortClm == 2)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strSubject > b.strSubject; });
			else if (sortClm == 3)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.strScore > b.strScore; });
			else if (sortClm == 4)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { Library oLib; return oLib.CStringToDate(a.strDate) > oLib.CStringToDate(b.strDate);  });
		break;
	}
}