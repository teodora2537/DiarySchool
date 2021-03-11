// CTabCRUD.cpp : implementation file
//
#include "pch.h"
#include "MFCApplication.h"
#include "CTabCRUD.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
#include "Score.h"
#include <string>
#include "CAddScore.h"
#include "CUpdateStudent.h"
#include "CUpdateSubject.h"
#include "CUpdateScore.h"
#include "MFCApplicationDlg.h"
// CTabCRUD dialog

IMPLEMENT_DYNAMIC(CTabCRUD, CDialogEx)
CTabCRUD::CTabCRUD(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_TAB_CRUD, pParent)
{

}
CTabCRUD::~CTabCRUD()
{
}

void CTabCRUD::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CTabCRUD, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD_STUDENT, &CTabCRUD::OnBnClickedButtonAddStudent)
END_MESSAGE_MAP()

void CTabCRUD::OnBnClickedButtonAddStudent()
{
	CStudentData oStudentData;
	
	CAddStudentDlg dlg(oStudentData, eDialogMode_Add);
	
	if (dlg.DoModal() != IDOK)
		return;

	CStudent oStudent;

	oStudent.AddStudent(oStudentData);
}