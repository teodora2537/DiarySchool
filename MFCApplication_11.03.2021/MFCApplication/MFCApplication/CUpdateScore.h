#pragma once
#include "Score.h"
#include "Library.h"
#include "Student.h"

// CUpdateScore dialog

class CScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreDlg)

public:
	//CScoreDlg(CWnd* pParent = nullptr);   // standard constructor
	CScoreDlg(CScoreData& oScore, const DialogMode eMode);   // standard constructor
	virtual ~CScoreDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog() override;
	DECLARE_MESSAGE_MAP()

public:
	CString m_strClassNum;
	CString m_strSubject;
	CString m_strScore;
	CString m_strDate;
	CString m_strComboBoxSubjects;

	CString m_strStaticText;

	BOOL ValidateData();

	CScoreData& m_oScore;
	DialogMode m_eMode;
	afx_msg void OnBnClickedOk();
};