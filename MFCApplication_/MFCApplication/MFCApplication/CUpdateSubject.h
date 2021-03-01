#pragma once
#include "Subject.h"
#include "Library.h"

// CUpdateSubject dialog
//old CUpdateSubject
/*
class CUpdateSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateSubjectDlg)

public:
	CUpdateSubjectDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CUpdateSubjectDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SUBJECT };
#endif

protected:
	virtual	BOOL OnInitDialog() /*override//;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	
	CString m_strRoomNum;
	CString m_strSubject;
	CString m_strFN;
	CString m_strLN;
	CString m_strStaticText;
	
	CEdit m_eRoomNum;

	afx_msg void OnBnClickedOk();
};
*/

class CUpdateSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CUpdateSubjectDlg)

public:
	CUpdateSubjectDlg(CSubjectData& oSubject, const DialogMode eMode);   // standard constructor
	virtual ~CUpdateSubjectDlg();

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

/*
class CSubjectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSubjectDlg)

public:
	CSubjectDlg(const CSubjectData& oSubject, DialogMode eMode);   // standard constructor
	virtual ~CSubjectDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SUBJECT };
#endif

protected:
	virtual	BOOL OnInitDialog() override;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

private:
	BOOL ValidateData();

protected:
	CSubjectData& m_oSubject;
	DialogMode m_eMode;

private:
	CString m_strRoomNum;
	CString m_strSubject;
	CString m_strFN;
	CString m_strLN;
	CString m_strStaticText;

private:
	afx_msg void OnOK();
};
*/
