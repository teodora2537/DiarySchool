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
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.idStudent < b.idStudent; });
		else if (sortClm == 1)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.nameStudent < b.nameStudent; });
		else if (sortClm == 2)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) {Library oLib; return oLib.CStringToDate(a.birthday) < oLib.CStringToDate(b.birthday); });
	break;
	
	case SORT_ZA: 
		     if (sortClm == 0)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.idStudent > b.idStudent; });
		else if (sortClm == 1)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) { return a.nameStudent > b.nameStudent; });
		else if (sortClm == 2)
			listFromStruct.sort([](const StudentStruct& a, const StudentStruct& b) {Library oLib; return oLib.CStringToDate(a.birthday) > oLib.CStringToDate(b.birthday); });
	break;
	}
}

void CListMethods::SortListScore(int sortClm, list<ScoreStruct>& listFromStruct, SortOrder order) {
	switch (order)
	{
		case SORT_AZ:
				 if (sortClm == 0)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.idStudent < b.idStudent; });
			else if (sortClm == 1)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.nameStudent < b.nameStudent; });
			else if (sortClm == 2)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.subject < b.subject; });
			else if (sortClm == 3)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.score < b.score; });
			else if (sortClm == 4)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) {Library oLib; return oLib.CStringToDate(a.date) < oLib.CStringToDate(b.date); });
		break;
		
		case SORT_ZA:
				 if (sortClm == 0)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.idStudent > b.idStudent; });
			else if (sortClm == 1)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.nameStudent > b.nameStudent; });
			else if (sortClm == 2)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.subject > b.subject; });
			else if (sortClm == 3)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { return a.score > b.score; });
			else if (sortClm == 4)
				listFromStruct.sort([](const ScoreStruct& a, const ScoreStruct& b) { Library oLib; return oLib.CStringToDate(a.date) > oLib.CStringToDate(b.date);  });
		break;
	}
}

void CListMethods::SortListSub(int sortClm, list<SubStruct>& listFromStruct, SortOrder order)
{
	switch (order)
	{
	case SORT_AZ:
			 if (sortClm == 0)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.idRoom < b.idRoom; });
		else if (sortClm == 1)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.subject < b.subject; });
		else if (sortClm == 2)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.nameTeacher < b.nameTeacher; });
	break;

	case SORT_ZA:
			 if (sortClm == 0)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.idRoom > b.idRoom; });
		else if (sortClm == 1)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.subject > b.subject; });
		else if (sortClm == 2)
			listFromStruct.sort([](const SubStruct& a, const SubStruct& b) { return a.nameTeacher > b.nameTeacher; });
		break;
	}
}