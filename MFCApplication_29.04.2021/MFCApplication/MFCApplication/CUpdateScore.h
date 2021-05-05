#pragma once
#include "Score.h"
#include "Library.h"
#include "Student.h"
#include "Subject.h"
using namespace std;
// CUpdateScore dialog

class CScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreDlg)

public:
	CScoreDlg(CScoreData& oScore, const DialogMode eMode);   // standard constructor
	virtual ~CScoreDlg();

	CScoreDlg();
	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SCORE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual	BOOL OnInitDialog() override;
	DECLARE_MESSAGE_MAP()

private:
	CString m_strClassNum;
	CEdit m_editClassNum;
	CString m_strSubject;
	CString m_strScore;
	COleDateTime m_strDate;

	BOOL ValidateData();

	CDateTimeCtrl m_dtCtrlDate;
	CComboBox m_comboBoxSubject;
	CComboBox m_comboBoxScore;

	CScoreData& m_oScore;
	DialogMode m_eMode;
	afx_msg void OnBnClickedOk();
};