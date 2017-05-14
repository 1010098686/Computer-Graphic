#include"stdafx.h"
#include"Ellipse.h"
#include<cmath>
#include<GL/glut.h>

MEllipse::MEllipse(int width, int height, int x, int y, double rx, double ry) :Shape(width, height)
{
	this->x = x;
	this->y = y;
	this->rx = rx;
	this->ry = ry;
	needFill = false;
}

void MEllipse::moveTo(int x, int y)
{
	this->x += x;
	this->y += y;
}

void MEllipse::rotate(int x, int y, int degree)
{
	double radian = degree*PI / 180;

	int tx = cos(radian)*(this->x - x) - sin(radian)*(this->y - y) + x;
	int ty = sin(radian)*(this->x - x) + cos(radian)*(this->y - y) + y;
	this->x = tx;
	this->y = ty;
}

void MEllipse::scale(double x, double y)
{
	this->rx *= x;
	this->ry *= y;
}

void MEllipse::FillShape(double r, double g, double b)
{
	needFill = true;
	nr = r;
	ng = g;
	nb = b;
}

void MEllipse::Draw()
{
	glPushMatrix();

	glColor3f(r, g, b);

	
	DrawEllipse();
	
	if (needFill)
	{
		FillEllipse(nr, ng, nb);
	}
	glPopMatrix();
}

void MEllipse::DrawSymmetry(int u, int v)
{
	IdentityPoint pos = translate(WindowWidth, WindowHeight, u+x, v+y);
	DrawPoints(pos.x, pos.y);

	v = -v;
	pos = translate(WindowWidth,WindowHeight,u+x, v+y);
	DrawPoints(pos.x, pos.y);

	u = -u;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	v = -v;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);
}


void MEllipse::DrawEllipse()
{
	double p1 = ry*ry - rx*rx*ry + rx*rx / 4;
	
	int u = 0;
	int v = ry;

	DrawSymmetry(u, v);
	while (ry*ry*u < rx*rx*v)
	{
		if (p1 < 0)
		{
			p1 = p1 + 2 * ry*ry*u + 3 * ry*ry;
			u = u + 1;
			DrawSymmetry(u, v);
		}
		else
		{
			p1 = p1 + 2 * ry*ry*u - 2 * rx*rx*v + 2 * rx*rx + 3 * ry*ry;
			u = u + 1;
			v = v - 1;
			DrawSymmetry(u, v);
		}
	}
	double p2 = ry*ry*(u + 0.5)*(u + 0.5) + rx*rx*(v - 1)*(v-1) - rx*rx*ry*ry;
	while (v>0)
	{
		if (p2 < 0)
		{	
			p2 = p2 + 2 * ry*ry*u - 2 * rx*rx*v + 2 * ry*ry + 3 * rx*rx;
			u = u + 1;
			v = v - 1;	
			DrawSymmetry(u, v);
		}
		else
		{
			p2 = p2 - 2 * rx*rx*v + 3 * rx*rx;
			v = v - 1;
			DrawSymmetry(u, v);
		}
	}
}



void MEllipse::FillEllipse(double r, double g, double b)
{
	glColor3f(r, g, b);
	for (int i = x - rx; i <= x + rx; ++i)
	{
		for (int j = y - ry; j <= y + ry; ++j)
		{
			int dx = abs(i - x);
			int dy = abs(j - y);
			if (ry*ry*dx*dx + rx*rx*dy*dy < rx*rx*ry*ry)
			{
				IdentityPoint p = translate(WindowWidth, WindowHeight, i, j);
				DrawPoints(p.x, p.y);
			}
		}
	}
}

void MEllipse::cut(int left, int top, int right, int buttom)
{
	//do nothing
}