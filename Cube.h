#ifndef MCUBE_H
#define MCUBE_H

#include"Shape.h"

class MCube :public Shape
{
private:
	Point3D vertex[6][4];
public:
	GLfloat degreex, degreey;
	MCube(int width, int height);
	~MCube();
	void Draw();
	void moveTo(int x, int y);
	void rotate(int x, int y, int degree);
	void scale(double x, double y);
	void FillShape(double r, double g, double b);
	void cut(int left, int top, int right, int bottom);
};

#endif