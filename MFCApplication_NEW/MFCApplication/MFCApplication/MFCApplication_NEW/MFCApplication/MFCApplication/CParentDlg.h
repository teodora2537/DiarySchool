#pragma once
#include "Student.h"
#include "afxdialogex.h"
// CParentDlg dialog

class CParentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParentDlg)

public:
	CParentDlg(CParentData& oParent, const DialogMode eMode);   // standard constructor
	virtual ~CParentDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PARENT };
#endif

protected: //methods
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL OnInitDialog();
	void EnableDisableBoxes();
	void FillEditBoxes();
	BOOL ValidateData();

	DECLARE_MESSAGE_MAP()

private: //member
	CString m_strFisrt_name;
	CString m_strLast_name;
	CString m_strEmail;
	CString m_strPhoneNumber;
	CString m_strCity;
	CString m_strPostCode;
	CString m_strNeighborhood;
	CString m_strAddress;
	DialogMode m_eMode;
	CParentData& m_oParent;

private: //method
	afx_msg void OnBnClickedOk();
};