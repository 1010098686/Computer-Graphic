#ifndef SHAPE_H
#define SHAPE_H


#include"Common.h"
#include<list>
#include<GL/glut.h>
using namespace std;

class Shape
{
public:
	Shape(int x, int y) {
		WindowWidth = x;
		WindowHeight = y;
	}
	virtual void Draw() = 0;
	virtual void moveTo(int x, int y) = 0;
	virtual void rotate(int x, int y, int degree) = 0;
	virtual void scale(double x, double y) = 0;
	virtual void FillShape(double r,double g,double b)=0;
	virtual void cut(int left, int top, int right, int buttom)=0;
	void SetColor(double r, double g, double b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}
	
protected:
	double r;
	double g;
	double b;
	double nr;
	double ng;
	double nb;
	int WindowWidth;
	int WindowHeight;


};

#endif