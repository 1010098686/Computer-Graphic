#include"stdafx.h"
#include"Line.h"
#include<cmath>
#include<GL/glut.h>



Line::Line(int Width, int Height, int x1, int y1, int x2, int y2) :Shape(Width,Height)
{
	this->x1 = x1;
	this->x2 = x2;
	this->y1 = y1;
	this->y2 = y2;

	if (this->x1 > this->x2)
	{
		int temp = this->x1;
		this->x1 = this->x2;
		this->x2 = temp;
		temp = this->y1;
		this->y1 = this->y2;
		this->y2 = temp;
	}
}

void Line::Draw()
{
	glPushMatrix();
	glColor3f(r, g, b);
	
	int dx = x2 - x1;
	int dy = y2 - y1;
	double k = (double)dy / dx;
	
	if (k >= 0)
	{
		if (k >= 1) Bresenham1();
		else Bresenham2();
	}
	else
	{
		if (k <= -1) Bresenham4();
		else Bresenham3();
	}
	

	glPopMatrix();
}

void Line::moveTo(int x, int y)
{
	x1 += x;
	x2 += x;
	y1 += y;
	y2 += y;
}

void Line::rotate(int x, int y, int degree)
{
	double radian = degree * PI / 180;
	int tx1 = cos(radian) *(x1 - x) - sin(radian)*(y1 - y) + x;
	int ty1 = sin(radian)*(x1 - x) + cos(radian)*(y1 - y) + y;

	x1 = tx1;
	y1 = ty1;

	tx1 = cos(radian)*(x2 - x) - sin(radian)*(y2 - y) + x;
	ty1 = sin(radian)*(x2 - x) + cos(radian)*(y2 - y) + y;

	x2 = tx1;
	y2 = ty1;
}

void Line::scale(double x, double y)
{
	x1 *= x;
	y1 *= y;
	x2 *= x;
	y2 *= y;
}

void Line::FillShape(double r, double g, double b)
{
	//do nothing
}



void Line::Bresenham2()
{
	int u = x1;
	int v = y1;
	
	IdentityPoint pos = translate(WindowWidth, WindowHeight, u, v);
	DrawPoints(pos.x, pos.y);

	int dx = x2 - x1;
	int dy = y2 - y1;
	int dy2 = dy + dy;
	int dy2sdx2 = dy2 - dx - dx;
	int p = dy2 - dx;
	
	for (int i = x1+1; i <= x2; ++i)
	{
		if (p < 0)
		{
			u++;
			pos = translate(WindowWidth, WindowHeight, u, v);
			DrawPoints(pos.x, pos.y);
			p = p + dy2;
		}
		else
		{
			u++;
			v++;
			pos = translate(WindowWidth, WindowHeight, u, v);
			DrawPoints(pos.x, pos.y);
			p = p + dy2sdx2;
		}
	}
}


//先将直线关于y=x对称，这样斜率就小于1，然后按照之前的算法计算点集，最后在对称，就可以得到原来的直线
void Line::Bresenham1()
{
	int m1 = y1;
	int n1 = x1;
	int m2 = y2;
	int n2 = x2;
	
	int u = m1;
	int v = n1;

	IdentityPoint pos = translate(WindowHeight, WindowWidth, u, v);
	DrawPoints(pos.y, pos.x);

	int dx = m2 - m1;
	int dy = n2 - n1;
	int dy2 = dy + dy;
	int dy2sdx2 = dy2 - dx - dx;
	int p = dy2 - dx;

	for (int i = m1 + 1; i <= m2; ++i)
	{
		if (p < 0)
		{
			u++;
			pos = translate(WindowHeight, WindowWidth, u, v);
			DrawPoints(pos.y, pos.x);
			p = p + dy2;
		}
		else
		{
			u++;
			v++;
			pos = translate(WindowHeight, WindowWidth, u, v);
			DrawPoints(pos.y, pos.x);
			p = p + dy2sdx2;
		}
	}
}

void Line::Bresenham3()
{
	int dx = x2 - x1;
	int dy = y2 - y1;
	int dy2 = dy + dy;
	int dy2adx2 = dy2 + dx + dx;
	int p = dy2 - dx;

	int u = x1;
	int v = y1;
	IdentityPoint pos = translate(WindowWidth, WindowHeight, u, v);
	DrawPoints(pos.x, pos.y);

	for (int i = x1 + 1; i <= x2; ++i)
	{
		if (p < 0)
		{
			u++;
			v--;
			pos = translate(WindowWidth, WindowHeight, u, v);
			DrawPoints(pos.x, pos.y);
			p = p + dy2adx2;
		}
		else
		{
			u++;
			pos = translate(WindowWidth, WindowHeight, u, v);
			DrawPoints(pos.x, pos.y);
			p = p + dy2;
		}
	}
}

void Line::Bresenham4()
{
	int m1 = y1;
	int n1 = x1;
	int m2 = y2;
	int n2 = x2;

	if (m1 > m2)
	{
		int temp = m1;
		m1 = m2;
		m2 = temp;

		temp = n1;
		n1 = n2;
		n2 = temp;
	}
	
	int dx = m2 - m1;
	int dy = n2 - n1;
	int dy2 = dy + dy;
	int dy2adx2 = dy2 + dx + dx;
	int p = dy2 - dx;

	int u = m1;
	int v = n1;
	IdentityPoint pos = translate(WindowHeight, WindowWidth, u, v);
	DrawPoints(pos.y, pos.x);

	for (int i = m1 + 1; i <= m2; ++i)
	{
		if (p < 0)
		{
			u++;
			v--;
			pos = translate(WindowHeight, WindowWidth, u, v);
			DrawPoints(pos.y, pos.x);
			p = p + dy2adx2;
		}
		else
		{
			u++;
			pos = translate(WindowHeight, WindowWidth, u, v);
			DrawPoints(pos.y, pos.x);
			p = p + dy2;
		}
	}
}

void Line::cut(int left, int top, int right, int buttom)
{
	bool flag = false;
	float u1 = 0, u2 = 1;
	float dx = x2 - x1;
	float dy;
	if (cutTest(-dx, x1 - left, u1, u2)){
		if (cutTest(dx, right - x1, u1, u2)){
			dy = y2 - y1;
			if (cutTest(-dy, y1 - buttom, u1, u2)){
				if (cutTest(dy, top - y1, u1, u2))
				{
					flag = true;
					if (u2 < 1)
					{
						x2 = x1 + u2*dx;
						y2 = y1 + u2*dy;
					}
					if (u1>0)
					{
						x1 = x1 + u1*dx;
						y1 = y1 + u1*dy;
					}
				}
			}
		}
	}
	if (!flag)
	{
		x1 = x2 = y1 = y2 = 0;
	}
}

bool Line::cutTest(float p, float q, float& u1, float& u2)
{
	int flag = 1;
	float r;
	if (p < 0)
	{
		r = q / p;
		if (r>u2)
		{
			flag = 0;
		}
		else if (r > u1)
		{
			u1 = r;
		}
	}
	else if (p > 0)
	{
		r = q / p;
		if (r < u1)
		{
			flag = 0;
		}
		else if (r < u2)
		{
			u2 = r;
		}
	}
	else if (q < 0)
	{
		flag = 0;
	}
	return flag;
}