// MoveDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CG.h"
#include "MoveDlg.h"
#include "afxdialogex.h"


// MoveDlg 对话框

IMPLEMENT_DYNAMIC(MoveDlg, CDialogEx)

MoveDlg::MoveDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(MoveDlg::IDD, pParent)
	, MoveX(0)
	, MoveY(0)
{

}

MoveDlg::~MoveDlg()
{
}

void MoveDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_MOVE_X, MoveX);
	DDX_Text(pDX, IDC_MOVE_Y, MoveY);
}


BEGIN_MESSAGE_MAP(MoveDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &MoveDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN2, &MoveDlg::OnDeltaposSpin2)
	ON_BN_CLICKED(IDOK, &MoveDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// MoveDlg 消息处理程序


void MoveDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		MoveX++;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		--MoveX;
		UpdateData(FALSE);
	}
}


void MoveDlg::OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		MoveY++;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		--MoveY;
		UpdateData(FALSE);
	}
}





void MoveDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	UpdateData(TRUE);
}
