#pragma once
#include <list>
#include "Library.h"
#include "CListMethods.h"
#include "Score.h"
#include "Student.h"
#include "Subject.h"
#include "CUpdateScore.h"
#include "CUpdateStudent.h"
#include "CUpdateSubject.h"
#include "resource.h"
using namespace std;
// CTabReference dialog
class CTabReference : public CDialogEx
{
	DECLARE_DYNAMIC(CTabReference)

public:
	CTabReference();   // standard constructor
	virtual ~CTabReference();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_REFERENCES };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	DECLARE_MESSAGE_MAP()

private:
//buttons for list references
	afx_msg void OnBnClickedButtonAvgscorebysubject();
	afx_msg void OnBnClickedButtonAvgscorebyallsubjects();
	afx_msg void OnBnClickedButtonExcellentstudent();
	afx_msg void OnBnClickedButtonBirtdays();
	afx_msg void OnBnClickedButton();
	afx_msg void OnBnClickedButtonByMoreSubjects();

	void LoadData();

	CListMethods m_listCtrl;

private:
	bool m_bIsOnlyNames = false;
	CString m_strName;
	int m_iIdButton= IDC_BUTTON_AvgScoreBySubject;
	list<REFERENCE> m_listReference;
};