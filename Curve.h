#ifndef MCURVE_H
#define MCURVE_H

#include"Shape.h"
#include<vector>
#include<algorithm>
#include<numeric>
#include<functional>
using namespace std;

class MCurve:public Shape
{
private :
	vector<vector<IntPoint>> lists;
	void Draw4(vector<IntPoint> v);
	void Draw3(vector<IntPoint> v);
	void Draw2(vector<IntPoint> v);
public:
	int selected;
	vector<IntPoint> point_list;
	void construct(vector<IntPoint> points);
	MCurve(int width, int height, vector<IntPoint> v);
	void Draw();
	void moveTo(int x, int y);
	void rotate(int x, int y, int degree);
	void scale(double x, double y);
	void FillShape(double r, double g, double b);
	void cut(int left, int top, int right, int bottom);
};


#endif