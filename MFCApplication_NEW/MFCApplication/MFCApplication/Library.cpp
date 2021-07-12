#include "pch.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"

Library::Library(void) {}
Library::~Library(void) {}

void Library::ClearListCtrl(CListCtrl& listCtrl)
{
	int nColumnCount = listCtrl.GetHeaderCtrl()->GetItemCount();
	listCtrl.SetRedraw(FALSE);
	listCtrl.DeleteAllItems();
	listCtrl.SetRedraw(TRUE);

	CString strMessage = "";
	// Delete all of the columns.
	for (int i = 0; i < nColumnCount; i++)
	{
		listCtrl.DeleteColumn(0);
	}
}

CString Library::IntToCString(int input) {
	CString str;
	str.Format("%d", input);
	return str;
}

CString Library::OleDTToCString(COleDateTime input) {
	CString str;
	str.Format("%d/%d/%d" ,input.GetMonth(), input.GetDay(), input.GetYear());
	return str;
}

COleDateTime Library::CStringToDate(CString input) {
	COleDateTime oleDT;
	oleDT.ParseDateTime(input, 0, MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US));
	return oleDT;
}

CString Library::CDBVariantToCString(CDBVariant& varValueBirthday)
{
		COleDateTime oleDT(varValueBirthday.m_pdate->year, varValueBirthday.m_pdate->month, varValueBirthday.m_pdate->day,
			varValueBirthday.m_pdate->hour, varValueBirthday.m_pdate->minute, varValueBirthday.m_pdate->second);
		CString str = oleDT.Format("%m/%d/%Y");
	return str;
}

COleDateTime Library::CDBVariantToCOleDT(CDBVariant& varValueBirthday) 
{
	COleDateTime oleDT(varValueBirthday.m_pdate->year, varValueBirthday.m_pdate->month, varValueBirthday.m_pdate->day,
		varValueBirthday.m_pdate->hour, varValueBirthday.m_pdate->minute, varValueBirthday.m_pdate->second);
	return oleDT;
}