#include "pch.h"
#include "CChildFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildFrame

IMPLEMENT_DYNCREATE(CChildFrame, CMDIChildWnd)

BEGIN_MESSAGE_MAP(CChildFrame, CMDIChildWnd)
//	ON_WM_CONTEXTMENU()
	//ON_BN_CLICKED(IDC_MENU_ADD, m_wndSplitter)
END_MESSAGE_MAP()

// CChildFrame construction/destruction

CChildFrame::CChildFrame() noexcept
{
	// TODO: add member initialization code here
}

CChildFrame::~CChildFrame()
{
}


BOOL CChildFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying the CREATESTRUCT cs
	if (!CMDIChildWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style = WS_CHILD | WS_VISIBLE | WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU
		| FWS_ADDTOTITLE | WS_THICKFRAME;

	return TRUE;
}

// CChildFrame diagnostics

#ifdef _DEBUG
void CChildFrame::AssertValid() const
{
	CMDIChildWnd::AssertValid();
}

void CChildFrame::Dump(CDumpContext& dc) const
{
	CMDIChildWnd::Dump(dc);
}
#endif //_DEBUG


//void CChildFrame::OnContextMenu(CWnd* /*pWnd*/, CPoint /*point*/)
//{
//	CMenu submenu;
//
//	submenu.CreatePopupMenu();
//	//submenu.AppendMenuW(MF_STRING, IDC_MENU_ADD, _T("Line"));
//}