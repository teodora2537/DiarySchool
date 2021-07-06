#pragma once
#include "MFCApplication.h"
#include "CParentDlg.h"
#include "CTabReference.h"

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

protected: //methods
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual	BOOL OnInitDialog() override;
	void SetRangeOfDTPicker();
	void EnableDisableBoxes();
	void FillEditBoxes();
	DECLARE_MESSAGE_MAP()

private: //context menu methods
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnAddParent();
	afx_msg void OnEditParent();
	afx_msg void OnDeleteParent();
	afx_msg void OnViewParent();

private: //methods
	BOOL ValidateStudent();
	afx_msg void OnBnClickedOk();
	afx_msg void LoadDatas(const int& nIdStudent);
	void OnNMDblclkList(NMHDR* pNMHDR, LRESULT* pResult);

public: //member
	CString m_strStudentId;
	CString m_strFirst_name;
	CString m_strLast_name;
	CString m_strEmail;
	CString m_strPhoneNumber;
	CString m_strEGN;
	CString m_strCity;
	CString m_strPostCode;
	CString m_strNeighborhood;
	CString m_strAddress;
	DialogMode m_eMode;
	RecordMode m_eParentMode;
	CListMethods m_listCtrl;
	CDateTimeCtrl m_dtCtrlBirthday;
	CStudentData& m_oStudent;
	list<CParentData> m_lParents;
};