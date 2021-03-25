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

};
