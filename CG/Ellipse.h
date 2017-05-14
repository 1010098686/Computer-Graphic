#ifndef MELLIPSE_H
#define MELLIPSE_H

#include"Shape.h"

class MEllipse : public Shape
{
private:
	int x;
	int y;
	double rx;
	double ry;
	bool needFill;
	void DrawEllipse();
	void DrawSymmetry(int u, int v);
public:
	MEllipse(int width, int height, int x, int y, double rx, double ry);
	void Draw();
	void moveTo(int x, int y);
	void rotate(int x, int y, int degree);
	void scale(double x, double y);
	void FillShape(double r, double g, double b);
	void cut(int left, int top, int right, int buttom);

private:
	void FillEllipse(double r, double g, double b);
};


#endif