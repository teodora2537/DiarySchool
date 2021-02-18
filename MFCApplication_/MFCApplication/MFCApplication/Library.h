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

	string ConvertToStirng(CString str_cstr, string row);
	void ClearListCtrl(CListCtrl& m_listCtrl);
};