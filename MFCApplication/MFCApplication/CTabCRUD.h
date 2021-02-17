#pragma once
#include<string>
#include<afxwin.h>

// CTabCRUD dialog

class CTabCRUD : public CDialogEx
{
	DECLARE_DYNAMIC(CTabCRUD)

public:
	CTabCRUD(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CTabCRUD();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TAB_CRUD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAddStudent();
	afx_msg void OnBnClickedButtonAddSubject();
	afx_msg void OnBnClickedButtonAddScore();
	afx_msg void OnBnClickedButtonUpdateStudent();
	afx_msg void OnBnClickedButtonUpdateSubject();
	afx_msg void OnBnClickedButtonUpdateScore();
	afx_msg void OnBnClickedButtonDeleteStudent();
	afx_msg void OnBnClickedButtonDeleteSubject();
	afx_msg void OnBnClickedButtonDeleteScore();
};
