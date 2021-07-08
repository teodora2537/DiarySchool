#pragma once
#include "MFCApplication.h"
#include "Student.h"
#include "Subject.h"

class CScoreDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScoreDlg)

public:
	CScoreDlg(CScoreData& oScore, const DialogMode eMode);   // standard constructor
	virtual ~CScoreDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SCORE };
#endif

protected: //mehods
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual	BOOL OnInitDialog() override;
	
private: //methods
	void SetRangeOfDTPicker();
	void FillComboBox();
	void FillEditBoxes();
	void EnableDisableBoxes();
	BOOL ValidateData();
	afx_msg void OnBnClickedOk();
	DECLARE_MESSAGE_MAP()


private: //member
	//string
	CString m_strStudentID;
	CString m_strSubject;
	CString m_strScore;
	//date
	COleDateTime m_oleDateTime;
	CDateTimeCtrl m_dtCtrlDate;
	//combobox
	CComboBox m_comboBoxSubject;
	CComboBox m_comboBoxScore;
	//object
	CScoreData& m_oScore;
	//dialogMode
	DialogMode m_eMode;
};