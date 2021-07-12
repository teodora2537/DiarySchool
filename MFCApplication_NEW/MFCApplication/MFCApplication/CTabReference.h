#pragma once
#include "MFCApplication.h"
#include <list>
#include "Library.h"
#include "CListMethods.h"

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
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV support
	DECLARE_MESSAGE_MAP()

private: //methods
	afx_msg void OnBnClickedButtonAvgScoreBySubject();
	void ClearList();
	afx_msg void OnBnClickedButtonAvgScore();
	afx_msg void OnBnClickedButtonExcellentStudent();
	afx_msg void OnBnClickedButtonBirtdays();
	afx_msg void OnBnClickedButtonCorrectionBySubject();
	afx_msg void OnBnClickedButtonCorrectionByMoreSubjects();
	BOOL CTabReference::OnInitDialog();
	void LoadData();

private: //member
	CListMethods m_listCtrl;
	list<REFERENCE> m_listReference;
	bool m_bIsOnlyNames;

};