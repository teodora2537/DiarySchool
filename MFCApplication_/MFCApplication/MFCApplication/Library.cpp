#include "pch.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include<math.h>
using namespace std;

Library::Library(void) {}
Library::~Library(void) {}

//Convert CString to string
string Library::ConvertToStirng(CString str_cstr, string row) 
{
	CString s_cstring = str_cstr;
	CT2CA ct(s_cstring);
	row = ct;
	return row;
}

void Library::ClearListCtrl(CListCtrl& m_listCtrl)
{
	int nColumnCount = m_listCtrl.GetHeaderCtrl()->GetItemCount();
	m_listCtrl.SetRedraw(FALSE);
	m_listCtrl.DeleteAllItems();
	m_listCtrl.SetRedraw(TRUE);
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		m_listCtrl.DeleteColumn(0);
	}
}