#pragma once
#include "afxdb.h"
#include <afxwin.h>
#include <string>
using namespace std;

#define DEF_FILE_DATA_SEPARATOR	'|'

enum DialogMode
{
	eDialogMode_Add = 1,
	eDialogMode_Edit = 2,
	eDialogMode_View = 3
};

enum RecordMode
{
	eRecordMode_None = 0,
	eRecordMode_Add = 1,
	eRecordMode_Edit = 2,
	eRecordMode_Delete = 3,
	eRecordMode_View = 4
};

class Library
{
public:
	Library(void);
	~Library(void);

	void ClearListCtrl(CListCtrl& m_listCtrl);
	CString IntToCString(int input);
	CString OleDTToCString(COleDateTime input);
	COleDateTime CStringToDate(CString input);
	CString ChangeSingleDate(COleDateTime oleDt);
};