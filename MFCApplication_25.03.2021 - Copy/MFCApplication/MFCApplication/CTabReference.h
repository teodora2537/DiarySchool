#pragma once
#include <stdlib.h>

using namespace std;
// CTabReference dialog
class CTabReference : public CDialogEx
{
	DECLARE_DYNAMIC(CTabReference)

public:
	CTabReference(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabReference();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_REFERENCES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAvgscorebysubject();
	afx_msg void OnBnClickedButtonAvgscorebyallsubjects();
	afx_msg void OnBnClickedButtonExcellentstudent();
	afx_msg void OnBnClickedButtonBirtdays();
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButtonByMoreSubjects();

	CListCtrl m_listCtrl;

	CString m_class;

	int m_nItem;

	//////////////////////////////////////////////////////////////////////////////////
	/*
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);

	afx_msg void OnAddStudent();
	afx_msg void OnEditStudent();
	afx_msg void OnViewStudent();
	afx_msg	void OnDeleteStudent();

	afx_msg void OnAddSubject();
	afx_msg void OnEditSubject();
	afx_msg void OnViewSubject();
	afx_msg	void OnDeleteSubject();

	afx_msg void OnAddScore();
	afx_msg void OnEditScore();
	afx_msg void OnViewScore();
	afx_msg	void OnDeleteScore();

	afx_msg	void SubmenuStudent(CWnd* pWnd, CPoint point);
	afx_msg	void SubmenuSubject(CWnd* pWnd, CPoint point);
	afx_msg	void SubmenuScore(CWnd* pWnd, CPoint point);

	afx_msg void getStudentFromDlg();
	afx_msg void getSubjectFromDlg();
	afx_msg void getScoreFromDlg();

	afx_msg void DeleteItem();
	*/

	CString m_cstrId;
	CString m_cstrName;
	CString m_cstrBirthday;
	CString m_cstrFirstName;
	CString m_cstrLastName;
	CString m_cstrSubject;
	CString m_cstrTeacher;

	int m_iPosition = 0;
	int m_iStudent;
	int m_iCount = 0;

};