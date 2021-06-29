#pragma once
#include "Library.h"
#include "Student.h"
#include "CParent.h"
#include "CTabReference.h"
#include <list>

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

	BOOL ValidateStudent();
	CStudentData& m_oStudent;
	//CStudentData m_oParent;
	DialogMode m_eMode;
	RecordMode m_eParentMode;
	CListMethods m_listCtrl;
	afx_msg void OnBnClickedOk();
	afx_msg void LoadParents(const int& nIdStudent);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddParent();
	afx_msg void OnEditParent();
	afx_msg void OnDeleteParent();
	afx_msg void OnViewParent();
	void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);
	list<PARENT> m_lParents;
};