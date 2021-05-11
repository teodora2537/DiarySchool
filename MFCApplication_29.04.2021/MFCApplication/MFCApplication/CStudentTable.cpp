// CStudentTable.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CStudentTable.h"
#include "afxdialogex.h"


// CStudentTable dialog

IMPLEMENT_DYNAMIC(CStudentTable, /*CDialogEx*/CRecordset)

CStudentTable::CStudentTable(CDatabase* pdb)
	: CDialogEx(IDD_DIALOG_UPDATE_STUDENT)
	,CRecordset(pdb)
{

}

CStudentTable::~CStudentTable()
{
}

void CStudentTable::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CStudentTable, CDialogEx)
END_MESSAGE_MAP()


// CStudentTable message handlers


void CStudentTable::DoFieldExchange(CFieldExchange* pFX)
{
	// TODO: Add your specialized code here and/or call the base class

	__super::DoFieldExchange(pFX);

	pFX->SetFieldType(CFieldExchange::inoutParam);
	RFX_Int(pFX, "[id]", m_iClassNum);
	RFX_Text(pFX, "[first_name]", m_strFn);
	RFX_Text(pFX, "[last_name]", m_strLn);
	
	m_dtCtrlBirthday.GetTime(time);
	RFX_Date(pFX, "[birth_date]", time);

	pFX->SetFieldType(CFieldExchange::inputParam);

}
