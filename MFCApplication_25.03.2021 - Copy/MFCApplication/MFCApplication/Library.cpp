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
string Library::ConvertToString(CString str_cstr, string row)
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

/*
BOOL Library::IsCorrectDate(CString strDate) {

	COleDateTime date;
	date.ParseDateTime(strDate, 0, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	COleDateTime oleDate = COleDateTime::GetCurrentTime();
	CString currentDate = oleDate.Format(_T("%m/%d/%Y"));

	if (date.GetStatus() || strDate[2] != '/' || strDate[5] != '/')
		return false;
	else if (date.GetYear() < oleDate.GetYear())
		return true;
	else if (date.GetYear() > oleDate.GetYear())
		return false;
	else if (date.GetMonth() < oleDate.GetMonth())
		return true;
	else if (date.GetMonth() > oleDate.GetMonth())
		return false;
	else if (date.GetDay() < oleDate.GetDay())
		return true;
	else if (date.GetDay() > oleDate.GetDay())
		return false;

	return true;
}
*/

CString Library::IntToCString(int input) {
	CString str;
	str.Format("%d", input);

	return str;
}

COleDateTime Library::CStringToDate(CString input) {
	COleDateTime date;
	date.ParseDateTime(input, 0, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	return date;
}

