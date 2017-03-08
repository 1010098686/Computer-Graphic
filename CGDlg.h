
// CGDlg.h : ͷ�ļ�
//

#pragma once

#include<GL/glut.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib,"glu32.lib")
#pragma comment(lib,"glut32.lib")

#include"Line.h"
#include"Circle.h"
#include"Ellipse.h"
#include"Polygon.h"
#include"Curve.h"
#include"Cube.h"
#include<cmath>
#include<vector>
#include<string>
#include<cstdio>
#include"MoveDlg.h"
#include"RotateDlg.h"
#include"ScaleDlg.h"
using namespace std;



enum DIALOG_STATE{NORMAL=1,INSERT_LINE,INSERT_CIRCLE,INSERT_ELLIPSE,INSERT_POLYGON,INSERT_CURVE,SAVE_STATE,CUT};
// CCGDlg �Ի���
class CCGDlg : public CDialogEx
{
// ����
public:
	CCGDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	void DrawFunc();
	void ChangeWindowSize();
	void initValue();
	void save();

protected:
	HGLRC hrc;
	HDC hdc;
	Shape* shape;
	int pre_x;
	int pre_y;
	int degree_x;
	int degree_y;
	bool drag;
	int x;
	int y;
	vector<IntPoint> point_list;
	int cur_state;
	COLORREF color;
	string desFile;
	
public:
	afx_msg void OnClose();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnDrawLine();
	afx_msg void OnDrawCircle();
	afx_msg void OnDrawEllipse();
	afx_msg void OnSettingsColor();
	afx_msg void OnEditClear();
	afx_msg void OnFileSave32771();
	afx_msg void OnDrawPolygon();
	afx_msg void OnEditMove();
	afx_msg void OnEditRotate();
	afx_msg void OnEditScale();
	afx_msg void OnEditFill();
	afx_msg void OnEditCut32787();
	afx_msg void OnDrawCurve();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDrawCube();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};
