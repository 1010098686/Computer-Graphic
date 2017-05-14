#pragma once


// MoveDlg 对话框

class MoveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MoveDlg)

public:
	MoveDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~MoveDlg();

// 对话框数据
	enum { IDD = IDD_MOVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	int MoveX;
	int MoveY;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedOk();
};
