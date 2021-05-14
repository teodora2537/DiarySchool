#pragma once
#include <afxdb.h>


// CSubjectTable dialog

class CSubjectTable : public CDialogEx, public CRecordset
{
public:
	CSubjectTable(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CSubjectTable)

public:
	CSubjectTable(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CSubjectTable();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_UPDATE_SUBJECT };
#endif

protected:
	virtual CString GetDefaultConnection();
	virtual CString GetDefaultSQL();
	virtual void DoFieldExchange(CFieldExchange* pFX);
	DECLARE_MESSAGE_MAP()

public:
	int	m_iRoomNumber;
	CString m_strNameSubject;
	CString m_strFNameTeacher;
	CString m_strLNameTeacher;
	CString m_strStatus;
};