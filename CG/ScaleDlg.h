#pragma once


// ScaleDlg 对话框

class ScaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDlg)

public:
	ScaleDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~ScaleDlg();

// 对话框数据
	enum { IDD = IDD_SCALE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double ScaleX;
	double ScaleY;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
