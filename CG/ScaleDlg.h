#pragma once


// ScaleDlg �Ի���

class ScaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(ScaleDlg)

public:
	ScaleDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~ScaleDlg();

// �Ի�������
	enum { IDD = IDD_SCALE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	double ScaleX;
	double ScaleY;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
