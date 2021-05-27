#include "pch.h"
#include "MFCApplication.h"
#include "CTabControl.h"
#include "CTabCRUD.h"
#include "CTabReference.h"
#include "CTabStudent.h"
#include "CTabSubject.h"
#include "CTabScore.h"

CTabControl::CTabControl()
{
    m_tabPages[0] = new CTabStudent;
    m_tabPages[1] = new CTabSubject();
    m_tabPages[2] = new CTabScore;
    m_tabPages[3] = new CTabReference;
    m_nNumberOfPages = 4;
}

CTabControl::~CTabControl()
{
    for (int nCount = 0; nCount < m_nNumberOfPages; nCount++)
        delete m_tabPages[nCount];
}

void CTabControl::Init(void)
{
    m_tabCurrent = 0;

    m_tabPages[0]->Create(IDD_TAB_STUDENT, this);
    m_tabPages[1]->Create(IDD_TAB_SUBJECT, this);
    m_tabPages[2]->Create(IDD_TAB_SCORE, this);
    m_tabPages[3]->Create(IDD_TAB_REFERENCES, this);

    m_tabPages[0]->ShowWindow(SW_SHOW);
    m_tabPages[1]->ShowWindow(SW_HIDE);
    m_tabPages[2]->ShowWindow(SW_HIDE);
    m_tabPages[3]->ShowWindow(SW_HIDE);

    SetRectangle();
}

void CTabControl::SetRectangle(void)
{
    CRect tabRect, itemRect;
    int nX, nY, nXc, nYc;

    GetClientRect(&tabRect);
    GetItemRect(0, &itemRect);

    nX = itemRect.left;
    nY = itemRect.bottom + 1;
    nXc = tabRect.right - itemRect.left - 1;
    nYc = tabRect.bottom - nY - 1;

    m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
    for (int nCount = 1; nCount < m_nNumberOfPages; nCount++)
    {
        m_tabPages[nCount]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
    }
}

BEGIN_MESSAGE_MAP(CTabControl, CTabCtrl)
    ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CTabControl::OnLButtonDown(UINT nFlags, CPoint point)
{
    CTabCtrl::OnLButtonDown(nFlags, point);
    CTabCtrl::OnLButtonDown(nFlags, point);
    if (m_tabCurrent != GetCurFocus())
    {
        m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
        m_tabCurrent = GetCurFocus();
        m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
        m_tabPages[m_tabCurrent]->SetFocus();
    }
}