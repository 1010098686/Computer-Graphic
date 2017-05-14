#ifndef CIRCLE_H
#define CIRCLE_H

#include"Shape.h"

class Circle :public Shape
{
private:
	int x;
	int y;
	bool needFill;
	double radio;
	void DrawCircle();
	void DrawSymmetry(int u, int v);
public:
	Circle(int width, int height, int x, int y, double r);
	void Draw();
	void moveTo(int x, int y);
	void rotate(int x, int y, int degree);
	void scale(double x, double y);
	void FillShape(double r, double g, double b);
	void cut(int left, int top, int right, int buttom);

private:
	void FillCircle(double r, double g, double b);
	
};


#endif