#include "pch.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"
using namespace std;

Library::Library(void) {}
Library::~Library(void) {}

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

CString Library::CDBVariantToCString(CDBVariant& varValueBirthday)
{
		COleDateTime timestamp(varValueBirthday.m_pdate->year, varValueBirthday.m_pdate->month, varValueBirthday.m_pdate->day,
			varValueBirthday.m_pdate->hour, varValueBirthday.m_pdate->minute, varValueBirthday.m_pdate->second);
		CString str = timestamp.Format("%m/%d/%Y");
	return str;
}