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
#include "AddStudent.h"
#include "CAddSubject.h"
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
	ON_BN_CLICKED(IDC_BUTTON_ADD_SUBJECT, &CTabCRUD::OnBnClickedButtonAddSubject)
	ON_BN_CLICKED(IDC_BUTTON_ADD_SCORE, &CTabCRUD::OnBnClickedButtonAddScore)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_STUDENT, &CTabCRUD::OnBnClickedButtonUpdateStudent)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SUBJECT, &CTabCRUD::OnBnClickedButtonUpdateSubject)
	ON_BN_CLICKED(IDC_BUTTON_UPDATE_SCORE, &CTabCRUD::OnBnClickedButtonUpdateScore)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_STUDENT, &CTabCRUD::OnBnClickedButtonDeleteStudent)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SUBJECT, &CTabCRUD::OnBnClickedButtonDeleteSubject)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_SCORE, &CTabCRUD::OnBnClickedButtonDeleteScore)
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
void CTabCRUD::OnBnClickedButtonAddSubject()
{
	CAddSubjectDlg dlg;
	dlg.DoModal();
}
void CTabCRUD::OnBnClickedButtonAddScore()
{
	CAddScoreDlg dlg;
	dlg.DoModal();
}
void CTabCRUD::OnBnClickedButtonUpdateStudent()
{
	CUpdateStudentDlg dlg;
	dlg.DoModal();
}
void CTabCRUD::OnBnClickedButtonUpdateSubject()
{
	/*
	CUpdateSubjectDlg dlg;
	dlg.DoModal();
	*/
}
void CTabCRUD::OnBnClickedButtonUpdateScore()
{
	CUpdateScoreDlg dlg;
	dlg.DoModal();
}
void CTabCRUD::OnBnClickedButtonDeleteStudent()
{
	/*
	CDeleteStudent dlg;
	dlg.DoModal();
	*/
}
void CTabCRUD::OnBnClickedButtonDeleteSubject()
{
	/*
	CDeleteSubject dlg;
	dlg.DoModal();
	*/
}
void CTabCRUD::OnBnClickedButtonDeleteScore()
{
	/*
	CDeleteScore dlg;
	dlg.DoModal();
	*/
}