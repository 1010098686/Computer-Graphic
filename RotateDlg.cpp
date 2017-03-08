// RotateDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CG.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// RotateDlg 对话框

IMPLEMENT_DYNAMIC(RotateDlg, CDialogEx)

RotateDlg::RotateDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(RotateDlg::IDD, pParent)
	, RotateX(0)
	, RotateY(0)
	, RotateD(0)
{

}

RotateDlg::~RotateDlg()
{
}

void RotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROTATE_X, RotateX);
	DDX_Text(pDX, IDC_ROTATE_Y, RotateY);
	DDX_Text(pDX, IDC_ROTATE_DEGREE, RotateD);
}


BEGIN_MESSAGE_MAP(RotateDlg, CDialogEx)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN1, &RotateDlg::OnDeltaposSpin1)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN3, &RotateDlg::OnDeltaposSpin3)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN4, &RotateDlg::OnDeltaposSpin4)
	ON_BN_CLICKED(IDOK, &RotateDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// RotateDlg 消息处理程序


void RotateDlg::OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		RotateX++;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		RotateX--;
		UpdateData(FALSE);
	}
}


void RotateDlg::OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		RotateY++;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		RotateY--;
		UpdateData(FALSE);
	}
}


void RotateDlg::OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	if (pNMUpDown->iDelta == -1)
	{
		UpdateData(TRUE);
		RotateD++;
		UpdateData(FALSE);
	}
	else if (pNMUpDown->iDelta == 1)
	{
		UpdateData(TRUE);
		RotateD--;
		UpdateData(FALSE);
	}
}


void RotateDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	UpdateData(TRUE);
}
