#pragma once


// MoveDlg �Ի���

class MoveDlg : public CDialogEx
{
	DECLARE_DYNAMIC(MoveDlg)

public:
	MoveDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~MoveDlg();

// �Ի�������
	enum { IDD = IDD_MOVE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int MoveX;
	int MoveY;
	afx_msg void OnDeltaposSpin1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDeltaposSpin2(NMHDR *pNMHDR, LRESULT *pResult);
	
	afx_msg void OnBnClickedOk();
};
