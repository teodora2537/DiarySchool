#pragma once
#include "MFCApplication.h"
#include "CTabSubject.h"

class CSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubjectDlg)

public:
	CSubjectDlg(CSubjectData& oSubject, const DialogMode eMode);   // standard constructor
	virtual ~CSubjectDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SUBJECT };
#endif

protected: //methods
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog() override;
	DECLARE_MESSAGE_MAP()

private: //member
	CString m_strRoomNum;
	CString m_strSubject;
	CString m_strFirst_Name;
	CString m_strLast_Name;
	CSubjectData& m_oSubject;
	DialogMode m_eMode;

private: //methods
	afx_msg void OnBnClickedOk();
	afx_msg BOOL ValidateData();
	void FillEditBoxes();
	void EnableDisableBoxes();
};