#include "pch.h"
#include "CListMethods.h"
using namespace std;

void CListMethods::SortListStudent(const int sortClm, list<STUDENT>& listFromStruct, SortOrder order)
{
	switch (order)
	{
		case SORT_AZ: 
				 if (sortClm == 0)
				listFromStruct.sort([](const STUDENT& a, const STUDENT& b) { return a.iId < b.iId; });
			else if (sortClm == 1)
				listFromStruct.sort([](const STUDENT& a, const STUDENT& b) { CString str1 = CString(a.szName); CString str2 = CString(b.szName); return str1 < str2; });
			else if (sortClm == 2)
				listFromStruct.sort([](const STUDENT& a, const STUDENT& b) {Library oLib; return oLib.CStringToDate(a.szDate) < oLib.CStringToDate(b.szDate); });
		break;
		
		case SORT_ZA: 
			     if (sortClm == 0)
				listFromStruct.sort([](const STUDENT& a, const STUDENT& b) { return a.iId > b.iId; });
			else if (sortClm == 1)									  
				listFromStruct.sort([](const STUDENT& a, const STUDENT& b) { CString str1 = CString(a.szName); CString str2 = CString(b.szName); return str1 > str2; });
			else if (sortClm == 2)									  
				listFromStruct.sort([](const STUDENT& a, const STUDENT& b) {Library oLib; return oLib.CStringToDate(a.szDate) > oLib.CStringToDate(b.szDate); });
		break;
	}
}

void CListMethods::SortListSub(const int sortClm, list<SUBJECT>& listFromStruct, SortOrder order)
{
	switch (order)
	{

	case SORT_AZ:
			 if (sortClm == 0)
			listFromStruct.sort([](const SUBJECT& a, const SUBJECT& b) { return a.iId < b.iId; });
		else if (sortClm == 1)									  
			listFromStruct.sort([](const SUBJECT& a, const SUBJECT& b) { CString str1 = CString(a.szSubject); CString str2 = CString(b.szSubject); return str1 < str2; });
		else if (sortClm == 2)									  
			listFromStruct.sort([](const SUBJECT& a, const SUBJECT& b) { CString str1 = CString(a.szTeacher); CString str2 = CString(b.szTeacher); return str1 < str2; });
	break;														  
																  
	case SORT_ZA:												  
			 if (sortClm == 0)									  
			listFromStruct.sort([](const SUBJECT& a, const SUBJECT& b) { return a.iId > b.iId; });
		else if (sortClm == 1)									  
			listFromStruct.sort([](const SUBJECT& a, const SUBJECT& b) { CString str1 = CString(a.szSubject); CString str2 = CString(b.szSubject); return str1 > str2; });
		else if (sortClm == 2)
			listFromStruct.sort([](const SUBJECT& a, const SUBJECT& b) { CString str1 = CString(a.szTeacher); CString str2 = CString(b.szTeacher); return str1 > str2; });

		break;
	}
}

void CListMethods::SortListScore(const int sortClm, list<SCORE>& listFromStruct, SortOrder order) {
	switch (order)
	{
		case SORT_AZ:
				 if (sortClm == 0)
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { return a.iClassNum < b.iClassNum; });
			else if (sortClm == 1)				
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { CString str1 = CString(a.szName); CString str2 = CString(b.szName); return str1 < str2; });
			else if (sortClm == 2)				
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { CString str1 = CString(a.szSubject); CString str2 = CString(b.szSubject); return str1 < str2; });
			else if (sortClm == 3)				
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { return a.iScore < b.iScore; });
			else if (sortClm == 4)				
				listFromStruct.sort([](const SCORE& a, const SCORE& b) {Library oLib; return oLib.CStringToDate(a.szDate) < oLib.CStringToDate(b.szDate); });
		break;
		
		case SORT_ZA:
				 if (sortClm == 0)
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { return a.iClassNum > b.iClassNum; });
			else if (sortClm == 1)
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { CString str1 = CString(a.szName); CString str2 = CString(b.szName); return str1 > str2; });
			else if (sortClm == 2)
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { CString str1 = CString(a.szSubject); CString str2 = CString(b.szSubject); return str1 > str2; });
			else if (sortClm == 3)
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { return a.iScore > b.iScore; });
			else if (sortClm == 4)
				listFromStruct.sort([](const SCORE& a, const SCORE& b) { Library oLib; return oLib.CStringToDate(a.szDate) > oLib.CStringToDate(b.szDate);  });
		break;
	}
}

void CListMethods::SortListReference(const int sortClm, list<REFERENCE>& listFromStruct, SortOrder order, bool bIsNames)
{
	switch (order)
	{
	case SORT_AZ:
			if (sortClm == 0 && !bIsNames)
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) { return a.iId < b.iId; });
		else if (sortClm == 0 && bIsNames)
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) { CString str1 = CString(a.szClm0); CString str2 = CString(b.szClm0); return str1 < str2; });
		else if (sortClm == 1)			 						   
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) { CString str1 = CString(a.szClm1); CString str2 = CString(b.szClm1); return str1 < str2; });
		else if (sortClm == 2)			 					   				
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) { CString str1 = CString(a.szClm2); CString str2 = CString(b.szClm2); return str1 < str2; });
		else if (sortClm == 3)			 					   				
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) { CString str1 = CString(a.szClm3); CString str2 = CString(b.szClm3); return str1 < str2; });
		break;							
	case SORT_ZA:	
			 if (sortClm == 0 && !bIsNames)
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) { return a.iId > b.iId; });
		else if (sortClm == 0 && bIsNames)			 
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) {CString str1 = CString(a.szClm0); CString str2 = CString(b.szClm0); return str1 > str2; });
		else if (sortClm == 1)																																
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) {CString str1 = CString(a.szClm1); CString str2 = CString(b.szClm1); return str1 > str2; });
		else if (sortClm == 2)																																
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) {CString str1 = CString(a.szClm2); CString str2 = CString(b.szClm2); return str1 > str2; });
		else if (sortClm == 3)																																
			listFromStruct.sort([](const REFERENCE& a, const REFERENCE& b) {CString str1 = CString(a.szClm3); CString str2 = CString(b.szClm3); return str1 > str2; });
		break;
	}
}
