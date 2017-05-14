#include"stdafx.h"
#include"Curve.h"
#include<cmath>



void MCurve::construct(vector<IntPoint> v)
{
	this->point_list = v;
	lists = vector<vector<IntPoint>>();
	vector<IntPoint> temp = point_list;
	while (temp.size() >= 4)
	{
		vector<IntPoint> t = vector<IntPoint>();
		t.push_back(temp[0]);
		t.push_back(temp[1]);
		t.push_back(temp[2]);
		t.push_back(temp[3]);
		lists.push_back(t);
		vector<IntPoint>::iterator it = temp.begin();
		for (int j = 1; j <= 3; ++j)
		{
			it = temp.erase(it);
		}
	}
	lists.push_back(temp);
	
}

MCurve::MCurve(int width, int height, vector<IntPoint> v) :Shape(width, height)
{
	construct(v);
	selected = -1;
}

void MCurve::Draw4(vector<IntPoint> v)
{
	for (double u = 0; u <= 1; u = u + 0.001)
	{
		int x = pow(1 - u, 3)*v[0].x + 3 * u*(1 - u)*(1 - u)*v[1].x + 3 * u*u*(1 - u)*v[2].x + u*u*u*v[3].x;
		int y = pow(1 - u, 3)*v[0].y + 3 * u*(1 - u)*(1 - u)*v[1].y + 3 * u*u*(1 - u)*v[2].y + u*u*u*v[3].y;
		IdentityPoint p = translate(WindowWidth, WindowHeight, x, y);
		DrawPoints(p.x, p.y);
	}
}

void MCurve::Draw3(vector<IntPoint> v)
{
	for (double u = 0; u <= 1; u = u + 0.001)
	{
		int x = (u - 1)*(u - 1)*v[0].x + 2 * u*(1 - u)*v[1].x + u*u*v[2].x;
		int y = (u - 1)*(u - 1)*v[0].y + 2 * u*(1 - u)*v[1].y + u*u*v[2].y;
		IdentityPoint p = translate(WindowWidth, WindowHeight, x, y);
		DrawPoints(p.x, p.y);
	}
}

void MCurve::Draw2(vector<IntPoint> v)
{
	for (double u = 0; u <= 1; u = u + 0.001)
	{
		int x = (1 - u)*v[0].x + u*v[1].x;
		int y = (1 - u)*v[0].y + u*v[1].y;
		IdentityPoint p = translate(WindowWidth, WindowHeight, x, y);
		DrawPoints(p.x, p.y);
	}
}

void MCurve::Draw()
{
	glPushMatrix();

	glColor3f(0, 0, 0);
	glEnable(GL_LINE_STIPPLE);
	glLineStipple(2,0x0f0f);
	int size = point_list.size();
	glBegin(GL_LINES);
	for (int i = 0; i < size-1; ++i)
	{
		IdentityPoint ip = translate(WindowWidth, WindowHeight, point_list[i].x, point_list[i].y);
		glVertex2f(ip.x, ip.y);
		ip = translate(WindowWidth, WindowHeight, point_list[i + 1].x, point_list[i + 1].y);
		glVertex2f(ip.x, ip.y);
	}
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	glColor3f(r, g, b);
	
	int num = lists.size();
	for (int i = 0; i < num; ++i)
	{
		switch (lists[i].size())
		{
		case 4:
			Draw4(lists[i]);
			break;
		case 3:
			Draw3(lists[i]);
			break;
		case 2:
			Draw2(lists[i]);
			break;
		default:break;
		}
	}
	
	glPopMatrix();
}

void MCurve::moveTo(int x, int y)
{
	for_each(point_list.begin(), point_list.end(), [x,y](IntPoint& p){
		p.x += x;
		p.y += y;
	});
	construct(point_list);
}

void MCurve::rotate(int x, int y, int degree)
{
	double radian = degree*PI / 180;
	for_each(point_list.begin(), point_list.end(), [x, y, radian](IntPoint& p){
		int tx1 = cos(radian) *(p.x - x) - sin(radian)*(p.y - y) + x;
		int ty1 = sin(radian)*(p.x - x) + cos(radian)*(p.y - y) + y;

		p.x = tx1;
		p.y = ty1;
	});
	construct(point_list);
}

void MCurve::scale(double x, double y)
{
	for_each(point_list.begin(), point_list.end(), [x, y](IntPoint& p){
		p.x *= x;
		p.y *= y;
	});
	construct(point_list);
}

void MCurve::FillShape(double r, double g, double b)
{

}

void MCurve::cut(int left, int top, int right, int bottom)
{

}