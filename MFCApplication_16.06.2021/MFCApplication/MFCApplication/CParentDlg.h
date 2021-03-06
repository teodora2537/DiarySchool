#pragma once
#include <list>
#include "Student.h"

// CParentDlg dialog

class CParentDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CParentDlg)

public:
	CParentDlg(list<CStudentData>& listData, const DialogMode eMode);   // standard constructor
	virtual ~CParentDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PARENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

	void FillEditBoxes();

	DECLARE_MESSAGE_MAP()

public:
	CString m_strFn;
	CString m_strLn;
	CString m_strEmail;
	CString m_strPhoneNumber;
	CString m_strCity;
	CString m_strPostCode;
	CString m_strNeighborhood;
	CString m_strAddress;

	DialogMode m_eMode;
	list<CStudentData>& m_listData;
};
