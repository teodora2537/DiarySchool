#pragma once
#include "Subject.h"
#include "Library.h"

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

protected:
	virtual	BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	CString m_strRoomNum;
	CString m_strSubject;
	CString m_strFN;
	CString m_strLN;
	CString m_strStaticText;

	CSubjectData& m_oSubject;
	DialogMode m_eMode;

protected:
	CEdit m_eRoomNum;

private:
	afx_msg void OnBnClickedOk();
	afx_msg BOOL ValidateData();
};