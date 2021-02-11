#pragma once
#include <afxcmn.h>
class CTabControl :    public CTabCtrl
{
public:
	CTabControl();
	virtual ~CTabControl();
	CDialog* m_tabPages[2];
	int m_tabCurrent;
	int m_nNumberOfPages;
	
	void Init();
	void SetRectangle();
	DECLARE_MESSAGE_MAP()
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};