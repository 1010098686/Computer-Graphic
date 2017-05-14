#ifndef LINE_H
#define LINE_H

#include"Shape.h"
#include<vector>
using namespace std;

class Line :public Shape
{
private:
	int x1, y1, x2, y2;
	void Bresenham1();
	void Bresenham2();
	void Bresenham3();
	void Bresenham4();
public:
	Line(int WindowWidth, int WindowHeight, int x1, int y1, int x2, int y2);
	void Draw();
	void moveTo(int x, int y);
	void rotate(int x, int y, int degree);
	void scale(double x, double y);
	void FillShape(double r, double g, double b);
	void cut(int left, int top, int right, int buttom);
private:
	bool cutTest(float p, float q, float& u1, float& u2);
};

#endif