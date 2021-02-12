// CDeleteScore.cpp : implementation file
//

#include "pch.h"
#include "MFCApplication.h"
#include "CDeleteScore.h"
#include "afxdialogex.h"
#include "Library.h"
#include "Score.h"


// CDeleteScore dialog

IMPLEMENT_DYNAMIC(CDeleteScore, CDialogEx)

CDeleteScore::CDeleteScore(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_DELETE_SCORE, pParent)
{
	Score m_oScore;
	idScore.Format(L"%d", m_oScore.GetIdScore());
}

CDeleteScore::~CDeleteScore()
{
}

void CDeleteScore::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_DELETE_SCORE_ID_SCORE, idScore);

}


BEGIN_MESSAGE_MAP(CDeleteScore, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDeleteScore::OnBnClickedOk)
END_MESSAGE_MAP()
 
// CDeleteScore message handlers


void CDeleteScore::OnBnClickedOk()
{
	CString message;
	message.Format(L"Do you want to delete score with id %s?", idScore);
	int result = MessageBox(message, L"Delete student", MB_YESNO);
	CDialogEx::OnOK();
	
	//button yes clicked
	if (result == 6)
	{
	UpdateData(TRUE);
	Library lib;
	string row = "";

	Score score;
	score.SetIdScore(_ttoi(idScore));

	lib.DeleteScore();
	}
}
