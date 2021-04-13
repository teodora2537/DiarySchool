#pragma once
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

	void ClearListCtrl(CListCtrl& m_listCtrl);
	CString IntToCString(int input);
	CString CDBVariantToCString(CDBVariant& varValueBirthday);
	COleDateTime CStringToDate(CString input);
};