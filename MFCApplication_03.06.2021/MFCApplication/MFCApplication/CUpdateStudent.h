#pragma once
#include "Library.h"
#include "Student.h"
#include "CTabReference.h"
using namespace std;

class CStudentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStudentDlg)

public:
	CStudentDlg(CStudentData& oStudent, const DialogMode eMode);   // standard constructor
	virtual ~CStudentDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual	BOOL OnInitDialog() override;
	
	void SetRangeOfDTPicker();
	void EnableDisableBoxes();
	void FillEditBoxes();

	DECLARE_MESSAGE_MAP()
public:
	CString m_strStudent_ClassNum;
	CString m_strStudent_Fn;
	CString m_strStudent_Ln;
	CDateTimeCtrl m_dtStudent_CtrlBirthday;
	CString m_strStudent_Email;
	CString m_strStudent_PhoneNumber;
	CString m_strStudent_EGN;
	CString m_strStudent_City;
	CString m_strStudent_PostCode;
	CString m_strStudent_Neighborhood;
	CString m_strStudent_Address;
	
	CString m_strParent_Fn;
	CString m_strParent_Ln;
	CString m_strParent_PhoneNumber;
	CString m_strParent_Email;
	CString m_strParent_City;
	CString m_strParent_PostCode;
	CString m_strParent_Neighborhood;
	CString m_strParent_Address;

	BOOL ValidateData();
	CStudentData& m_oStudent;
	DialogMode m_eMode;
	afx_msg void OnBnClickedOk();
};