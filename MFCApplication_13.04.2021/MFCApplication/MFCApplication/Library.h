#pragma once
#include<string> 
#include<map> 
#include<vector> 
#include <winnt.h>
#include "afxdb.h"

using namespace std;

#define DEF_FILE_DATA_SEPARATOR	'|'

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

	string ConvertToString(CString str_cstr, string row);
	void ClearListCtrl(CListCtrl& m_listCtrl);
	CString IntToCString(int input);
	COleDateTime CStringToDate(CString input);
	CString CDBVariantToCString(CDBVariant& varValueBirthday);
};