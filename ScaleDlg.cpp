// ScaleDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CG.h"
#include "ScaleDlg.h"
#include "afxdialogex.h"


// ScaleDlg 对话框

IMPLEMENT_DYNAMIC(ScaleDlg, CDialogEx)

ScaleDlg::ScaleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(ScaleDlg::IDD, pParent)
	, ScaleX(0)
	, ScaleY(0)
{

}

ScaleDlg::~ScaleDlg()
{
}

void ScaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_SCALE_X, ScaleX);
	DDX_Text(pDX, IDC_SCALE_Y, ScaleY);
}


BEGIN_MESSAGE_MAP(ScaleDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &ScaleDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &ScaleDlg::OnDeltaposSpin3)
	ON_BN_CLICKED(IDOK, &ScaleDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// ScaleDlg 消息处理程序


void ScaleDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		ScaleX += 0.1;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		ScaleX -= 0.1;
		UpdateData(FALSE);
	}
}


void ScaleDlg::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		ScaleY += 0.1;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		ScaleY -= 0.1;
		UpdateData(FALSE);
	}
}


void ScaleDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	UpdateData(TRUE);
}
