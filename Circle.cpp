#include"stdafx.h"
#include"Circle.h"
#include<cmath>
#include<GL/glut.h>

Circle::Circle(int width, int height, int x, int y, double r) :Shape(width, height)
{
	this->x = x;
	this->y = y;
	this->radio = r;
	needFill = false;
}

void Circle::moveTo(int x, int y)
{
	this->x += x;
	this->y += y;
}

void Circle::rotate(int x, int y, int degree)
{
	double radian = degree*PI / 180;

	int tx = cos(radian)*(this->x - x) - sin(radian)*(this->y-y) + x;
	int ty = sin(radian)*(this->x - x) + cos(radian)*(this->y - y) + y;
	this->x = tx;
	this->y = ty;
}

void Circle::scale(double x, double y)
{
	this->radio *= x;
}

void Circle::FillShape(double r, double g, double b)
{
	
	needFill = true;
	nr = r;
	ng = g;
	nb = b;
}

void Circle::Draw()
{
	glPushMatrix();

	glColor3f(r, g, b);

	
	DrawCircle();
	if (needFill)
	{
		FillCircle(nr, ng, nb);
	}
	

	glPopMatrix();
}

void Circle::DrawSymmetry(int u, int v)
{
	IdentityPoint pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	int temp = u;
	u = v;
	v = temp;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	v = -v;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	temp = u;
	u = v;
	v = temp;
	u = -u;
	v = -v;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	u = -u;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	temp = u;
	u = v;
	v = temp;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	v = -v;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);

	temp = u;
	u = v;
	v = temp;
	u = -u;
	v = -v;
	pos = translate(WindowWidth, WindowHeight, u + x, v + y);
	DrawPoints(pos.x, pos.y);
}
void Circle::DrawCircle()
{
	int u = 0;
	int v = radio;
	double p = 1.25 - radio;

	DrawSymmetry(u, v);

	while (u < v)
	{
		if (p < 0)
		{
			p = p + u + u + 3;

			u = u + 1;
			DrawSymmetry(u, v);
		}
		else
		{
			u = u + 1;
			p = p + u + u + 3 - v - v - 2;
			v = v - 1;
			DrawSymmetry(u, v);
		}
	}
}

void Circle::FillCircle(double r, double g, double b)
{
	glColor3f(r, g, b);
	for (int i = x - radio; i <= x + radio; ++i)
	{
		for (int j = y - radio; j <= y + radio; ++j)
		{
			int dx = abs(i - x);
			int dy = abs(j - y);
			if (dx*dx + dy*dy < radio*radio)
			{
				IdentityPoint p = translate(WindowWidth, WindowHeight, i, j);
				DrawPoints(p.x, p.y);
			}
		}
	}
}

void Circle::cut(int left, int top, int right, int buttom)
{
	//do nothing
}