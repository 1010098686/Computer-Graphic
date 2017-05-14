#ifndef COMMON_H
#define COMMON_H

#include<GL/glut.h>

#define PI 3.1415926

struct IdentityPoint
{
	double x;
	double y;
	
};

struct Point3D
{
	double x;
	double y;
	double z;
};

struct IntPoint
{
	int x;
	int y;
	bool operator==(const IntPoint b)
	{
		return x == b.x && y == b.y;
	}
};

static IdentityPoint translate(int WindowWidth, int WindowHeight,int x,int y)
{
	int cx = WindowWidth / 2;
	int cy = WindowHeight / 2;
	int px = x - cx;
	int py = y - cy;
	IdentityPoint point;
	point.x = ((double)px) / cx;
	point.y = ((double)py) / cy;
	return point;
}


static void DrawPoints(double x, double y)
{
	glBegin(GL_POINTS);
	glVertex2d(x, y);
	glEnd();
}


#endif