#pragma once


// RotateDlg �Ի���

class RotateDlg : public CDialogEx
{
	DECLARE_DYNAMIC(RotateDlg)

public:
	RotateDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~RotateDlg();

// �Ի�������
	enum { IDD = IDD_ROTATE_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int RotateX;
	int RotateY;
	int RotateD;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin3(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin4(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedOk();
};
