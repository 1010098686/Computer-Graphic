
// CGDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CG.h"
#include "CGDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CCGDlg 对话框



CCGDlg::CCGDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCGDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCGDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCGDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_DRAW_LINE, &CCGDlg::OnDrawLine)
	ON_COMMAND(ID_DRAW_CIRCLE, &CCGDlg::OnDrawCircle)
	ON_COMMAND(ID_DRAW_ELLIPSE, &CCGDlg::OnDrawEllipse)
	ON_COMMAND(ID_SETTINGS_COLOR, &CCGDlg::OnSettingsColor)
	ON_COMMAND(ID_EDIT_CLEAR, &CCGDlg::OnEditClear)
	ON_COMMAND(ID_FILE_SAVE32771, &CCGDlg::OnFileSave32771)
	ON_COMMAND(ID_DRAW_POLYGON, &CCGDlg::OnDrawPolygon)
	ON_COMMAND(ID_EDIT_MOVE, &CCGDlg::OnEditMove)
	ON_COMMAND(ID_EDIT_ROTATE, &CCGDlg::OnEditRotate)
	ON_COMMAND(ID_EDIT_SCALE, &CCGDlg::OnEditScale)
	ON_COMMAND(ID_EDIT_FILL, &CCGDlg::OnEditFill)
	ON_COMMAND(ID_EDIT_CUT32787, &CCGDlg::OnEditCut32787)
	ON_COMMAND(ID_DRAW_CURVE, &CCGDlg::OnDrawCurve)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_DRAW_CUBE, &CCGDlg::OnDrawCube)
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()


// CCGDlg 消息处理程序

BOOL CCGDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	initValue();
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		24,
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		32,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};
	int pixelformat;
	hdc = ::GetDC(GetSafeHwnd());
	if (!(pixelformat = ChoosePixelFormat(hdc, &pfd)))
	{
		MessageBox(_T("choose pixel format fail"));
		return false;
	}
	if (!SetPixelFormat(hdc, pixelformat, &pfd))
	{
		MessageBox(_T("set pixel format fail"));
		return false;
	}
	if (!(hrc = wglCreateContext(hdc)))
	{
		MessageBox(_T("create context fail"));
		return false;
	}
	if (!wglMakeCurrent(hdc, hrc))
	{
		MessageBox(_T("make current fail"));
		return false;
	}

	ChangeWindowSize();
	SetTimer(1, 100, NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CCGDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCGDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCGDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCGDlg::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	KillTimer(1);
	CDialogEx::OnClose();
}


void CCGDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO:  在此处添加消息处理程序代码
	ChangeWindowSize();
}


void CCGDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	DrawFunc();
	CDialogEx::OnTimer(nIDEvent);
}

void CCGDlg::ChangeWindowSize()
{
	CRect rect;
	GetClientRect(rect);
	glViewport(0, 0, rect.Width(), rect.Height());

	
}

void CCGDlg::DrawFunc()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	if (shape != NULL)
	{
		shape->Draw();
	}

	if (cur_state == SAVE_STATE)
	{
		save();
		cur_state = NORMAL;
	}
	SwapBuffers(hdc);
}

void CCGDlg::initValue()
{
	//shape_list = vector<Shape*>();
	shape = NULL;
	point_list = vector<IntPoint>();
	color = RGB(0, 0, 0);
	cur_state = NORMAL;
	desFile = string();
	degree_x = degree_y = 0;
	drag = false;
}

void CCGDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	drag = true;
	CRect rect;
	GetClientRect(rect);
	pre_x = point.x;
	pre_y = rect.Height() - point.y;

	if (cur_state == INSERT_POLYGON || cur_state==INSERT_CURVE)
	{
		IntPoint p = { pre_x, pre_y };
		point_list.push_back(p);
	}

	MCurve* curve = dynamic_cast<MCurve*>(shape);
	if (curve != NULL)
	{
		int num = curve->point_list.size();
		for (int i = 0; i < num; ++i)
		{
			int dx = curve->point_list[i].x - pre_x;
			int dy = curve->point_list[i].y - pre_y;
			int dis = dx*dx + dy*dy;
			if (dis <= 25)
			{
				curve->selected = i;
				break;
			}
		}
	}

	MPolygon* polygon = dynamic_cast<MPolygon*>(shape);
	if (polygon != NULL)
	{
		int num = polygon->point_list.size();
		for (int i = 0; i < num; ++i)
		{
			int dx = polygon->point_list[i].x - pre_x;
			int dy = polygon->point_list[i].y - pre_y;
			int dis = dx*dx + dy*dy;
			if (dis <= 25)
			{
				polygon->selected = i;
				break;
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CCGDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	drag = false;
	CRect rect;
	GetClientRect(rect);
	x = point.x;
	y = rect.Height() - point.y;

	switch (cur_state)
	{
	case INSERT_LINE:
	{
						Line* line = new Line(rect.Width(), rect.Height(), pre_x, pre_y, x, y);
						double r = GetRValue(color) / 255;
						double g = GetGValue(color) / 255;
						double b = GetBValue(color) / 255;
						line->SetColor(r, g, b);
						//shape_list.push_back(line);
						if (shape != NULL) delete shape;
						shape = line;
						cur_state = NORMAL;
						break;
	}
	case INSERT_CIRCLE:
	{
						  double rx = abs(pre_x - x);
						  double ry = abs(pre_y - y);
						  double radio = sqrt(rx*rx + ry*ry);
						  Circle* circle = new Circle(rect.Width(), rect.Height(), pre_x, pre_y, radio);
						  double r = GetRValue(color) / 255;
						  double g = GetGValue(color) / 255;
						  double b = GetBValue(color) / 255;
						  circle->SetColor(r, g, b);
						 // shape_list.push_back(circle);
						  if (shape != NULL) delete shape;
						  shape = circle;
						  cur_state = NORMAL;
						  break;
	}
	case INSERT_ELLIPSE:
	{
						   int cx = (pre_x + x) / 2;
						   int cy = (pre_y + y) / 2;
						   double rx = abs(pre_x - x) / 2;
						   double ry = abs(pre_y - y) / 2;
						   MEllipse* ellipse = new MEllipse(rect.Width(), rect.Height(), cx, cy, rx, ry);
						   double r = GetRValue(color) / 255;
						   double g = GetGValue(color) / 255;
						   double b = GetBValue(color) / 255;
						   ellipse->SetColor(r, g, b);
						   //shape_list.push_back(ellipse);
						   if (shape != NULL) delete shape;
						   shape = ellipse;
						   cur_state = NORMAL;
						   break;
	}
	case NORMAL:break;
	case CUT:
	{
				if (shape != NULL)
				{
					int left = (pre_x < x) ? pre_x : x;
					int right = (pre_x < x) ? x : pre_x;
					int top = (pre_y < y) ? y : pre_y;
					int buttom = (pre_y < y) ? pre_y : y;
					shape->cut(left, top, right, buttom);
				}
				cur_state = NORMAL;
				break;
	}
	default:break;
	}

	MCurve* curve = dynamic_cast<MCurve*>(shape);
	if (curve != NULL && curve->selected != -1)
	{
		curve->selected = -1;
	}

	MPolygon* polygon = dynamic_cast<MPolygon*>(shape);
	if (polygon != NULL && polygon->selected != -1)
	{
		polygon->selected = -1;
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}


void CCGDlg::OnDrawLine()
{
	// TODO:  在此添加命令处理程序代码
	cur_state = INSERT_LINE;
}


void CCGDlg::OnDrawCircle()
{
	// TODO:  在此添加命令处理程序代码
	cur_state = INSERT_CIRCLE;
}


void CCGDlg::OnDrawEllipse()
{
	// TODO:  在此添加命令处理程序代码
	cur_state = INSERT_ELLIPSE;
}


void CCGDlg::OnSettingsColor()
{
	// TODO:  在此添加命令处理程序代码
	CColorDialog dialog = CColorDialog(color);
	if (IDOK == dialog.DoModal())
	{
		color = dialog.GetColor();
		double r = GetRValue(color)/255;
		double g = GetGValue(color)/255;
		double b = GetBValue(color)/255;
		if (shape != NULL)
		{
			shape->SetColor(r, g, b);
		}
	}
}


void CCGDlg::OnEditClear()
{
	// TODO:  在此添加命令处理程序代码
	//shape_list.clear();
	if (shape != NULL) delete shape;
	shape = NULL;
	
}



void CCGDlg::save()
{
	GLint pView[4];
	glGetIntegerv(GL_VIEWPORT, pView);
	int width = pView[2];
	int height = pView[3];

	GLubyte* data;
	BITMAPFILEHEADER hdr;
	BITMAPINFOHEADER infoHdr;
	int pixelDataLength;

	int i;
	i = width * 3;
	while (i % 4 != 0) ++i;
	pixelDataLength = i*height;
	data = new GLubyte[pixelDataLength];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glReadPixels(0, 0, width, height, GL_BGR_EXT, GL_UNSIGNED_BYTE, data);


	
	infoHdr.biSize = 40;
	infoHdr.biWidth = width;
	infoHdr.biHeight = height;
	infoHdr.biPlanes = 1;
	infoHdr.biBitCount = 24;
	infoHdr.biCompression = 0;
	infoHdr.biSizeImage = width* height * 3;
	infoHdr.biXPelsPerMeter = 0;
	infoHdr.biYPelsPerMeter = 0;
	infoHdr.biClrUsed = 0;
	infoHdr.biClrImportant = 0;

	hdr.bfType = 0x4D42;
	hdr.bfReserved1 = 0;
	hdr.bfReserved2 = 0;
	hdr.bfOffBits = 54;
	hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFOHEADER)+width* height * 3);


	FILE *fd;

	if (!(fd = fopen(desFile.c_str(), "wb+")))
	{
		exit(0);
	}
	fwrite(&hdr, 1, sizeof(BITMAPFILEHEADER), fd);
	fwrite(&infoHdr, 1, sizeof(BITMAPINFOHEADER), fd);
	fwrite(data, pixelDataLength, 1, fd);
	fclose(fd);
	delete[]data;
	
}

void CCGDlg::OnFileSave32771()
{
	// TODO:  在此添加命令处理程序代码
	TCHAR filter[] = _T("图片文件(*.bmp)|*.bmp||");
	CFileDialog dialog = CFileDialog(FALSE, _T("bmp"), NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filter, this);
	CString str;

	if (IDOK == dialog.DoModal())
	{
		str = dialog.GetPathName();
		
		LPCWSTR temp = str.GetBuffer(str.GetLength());
		int len = WideCharToMultiByte(CP_ACP, 0, temp, -1, NULL, 0, NULL, NULL);
		if (len < 0) desFile = "";
		else
		{
			char* p = new char[len];
			WideCharToMultiByte(CP_ACP, 0, temp, -1, p, len, NULL, NULL);
			p[len - 1] = 0;
			desFile = p;
			delete[]p;
		}
		str.ReleaseBuffer();
		cur_state = SAVE_STATE;
	}
}


void CCGDlg::OnDrawPolygon()
{
	// TODO:  在此添加命令处理程序代码
	cur_state = INSERT_POLYGON;
}


void CCGDlg::OnEditMove()
{
	// TODO:  在此添加命令处理程序代码
	if (shape != NULL)
	{
		MoveDlg* dlg = new MoveDlg(this);

		if (IDOK == dlg->DoModal())
		{
			int x = dlg->MoveX;
			int y = dlg->MoveY;
			shape->moveTo(x, y);
		}
		delete dlg;
		dlg = NULL;
	}
}


void CCGDlg::OnEditRotate()
{
	// TODO:  在此添加命令处理程序代码
	if (shape != NULL)
	{
		RotateDlg* dlg = new RotateDlg(this);
		if (IDOK == dlg->DoModal())
		{
			int x = dlg->RotateX;
			int y = dlg->RotateY;
			int degree = dlg->RotateD;
			if (x < 0 || y < 0)
			{
				MessageBox(_T("the parameter should be positive"));
				return;
			}
			shape->rotate(x, y, degree);
		}
		delete dlg;
		dlg = NULL;
	}
}


void CCGDlg::OnEditScale()
{
	// TODO:  在此添加命令处理程序代码
	if (shape != NULL)
	{
		ScaleDlg* dlg = new ScaleDlg(this);
		if (IDOK == dlg->DoModal())
		{
			double x = dlg->ScaleX;
			double y = dlg->ScaleY;
			if (x < 0 || y < 0)
			{
				MessageBox(_T("the parameter should be positive"));
				return;
			}
			shape->scale(x, y);
		}
		delete dlg;
		dlg = NULL;
	}
}


void CCGDlg::OnEditFill()
{
	// TODO:  在此添加命令处理程序代码
	if (shape != NULL)
	{
		CColorDialog dialog = CColorDialog(color);
		if (IDOK == dialog.DoModal())
		{
			COLORREF newColor = dialog.GetColor();
			double r = GetRValue(newColor) / 255;
			double g = GetGValue(newColor) / 255;
			double b = GetBValue(newColor) / 255;
			shape->FillShape(r, g, b);
		}
	}
}


void CCGDlg::OnEditCut32787()
{
	// TODO:  在此添加命令处理程序代码
	cur_state = CUT;
}


void CCGDlg::OnDrawCurve()
{
	// TODO:  在此添加命令处理程序代码
	cur_state = INSERT_CURVE;
}


void CCGDlg::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CRect rect;
	GetClientRect(&rect);
	double r = GetRValue(color) / 255;
	double g = GetGValue(color) / 255;
	double b = GetBValue(color) / 255;
	if (cur_state == INSERT_CURVE)
	{
		MCurve* curve = new MCurve(rect.Width(), rect.Height(), point_list);
		curve->SetColor(r, g, b);
		if (shape != NULL) delete shape;
		shape = curve;
	}
	else if (cur_state == INSERT_POLYGON)
	{
		MPolygon* polygon = new MPolygon(rect.Width(), rect.Height(), point_list);
		polygon->SetColor(r, g, b);
		if (shape != NULL) delete shape;
		shape = polygon;
	}
	cur_state = NORMAL;
	point_list.clear();
	CDialogEx::OnLButtonDblClk(nFlags, point);
}


void CCGDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	int dx = point.x - degree_x;
	int dy = point.y - degree_y;
	degree_x = point.x;
	degree_y = point.y;
	if (drag && cur_state==NORMAL)
	{
		MCube* cube = dynamic_cast<MCube*>(shape);
		if (cube != NULL)
		{
			CRect rect;
			GetClientRect(&rect);
			int width = rect.Width();
			int height = rect.Height();
			double rax = 360 * double(dx) / width;
			double ray = 360 * double(dy) / height;
			cube->degreex += rax;
			cube->degreey += ray;
		}
		
		MCurve* curve = dynamic_cast<MCurve*>(shape);
		if (curve != NULL)
		{
			if (curve->selected != -1)
			{
				CRect rect;
				GetClientRect(&rect);
				curve->point_list[curve->selected] = { point.x, rect.Height() - point.y };
				curve->construct(curve->point_list);
			}
		}

		MPolygon* polygon = dynamic_cast<MPolygon*>(shape);
		if (polygon != NULL)
		{
			if (polygon->selected != -1)
			{
				CRect rect;
				GetClientRect(&rect);
				polygon->point_list[polygon->selected] = { point.x, rect.Height() - point.y };
				polygon->construct(polygon->point_list);
			}
		}
	}
	CDialogEx::OnMouseMove(nFlags, point);
}


void CCGDlg::OnDrawCube()
{
	// TODO:  在此添加命令处理程序代码
	double r = GetRValue(color) / 255;
	double g = GetGValue(color) / 255;
	double b = GetBValue(color) / 255;

	if (shape != NULL) delete shape;

	CRect rect;
	GetClientRect(&rect);
	shape = new MCube(rect.Width(),rect.Height());
	shape->SetColor(r, g, b);
}


BOOL CCGDlg::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	MCube* cube = dynamic_cast<MCube*>(shape);
	if (cube != NULL)
	{
		if (zDelta > 0)
		{
			double b = double(zDelta) / 120;
			double radio = pow(1.2, b);
			cube->scale(radio, radio);
		}
		else if (zDelta < 0)
		{
			double b = -double(zDelta) / 120;
			double radio = pow(0.8, b);
			cube->scale(radio, radio);
		}
	}
	return CDialogEx::OnMouseWheel(nFlags, zDelta, pt);
}
