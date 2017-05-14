#ifndef POLYGON_H
#define POLYGON_H


#include"Shape.h"
#include"Line.h"
#include<list>
#include<vector>
#include<algorithm>
#include<numeric>
using namespace std;

struct EDGE
{
	double xi;
	double dx;
	int ymax;
};


class MPolygon :public Shape
{
private:
	vector<Line*> line_list;
	bool needFill;
public:
	vector<IntPoint> point_list;
	void construct(vector<IntPoint> points);
	int selected;
	MPolygon(int width,int height,vector<IntPoint> v);
	~MPolygon();
	void Draw();
	void moveTo(int x, int y);
	void rotate(int x, int y, int degree);
	void scale(double x, double y);
	void FillShape(double r, double g, double b);
	void cut(int left, int top, int right, int buttom);
private:
	//the fill algorithm uses the following functions
	void FillPolygon(double r, double g, double b);
	void GetPolygonMinMax(int& min, int& max);
	void InitScanLineNewEdgeTable(vector<list<EDGE>>& slNet, int ymin, int ymax);
	void HorizonEdgeFill(double r, double g, double b);
	void ProcessScanLineFill(vector<list<EDGE>>& slNet, int ymin, int ymax, double r, double g, double b);
	void InsertNetListToAet(list<EDGE>& sl, list<EDGE>& aet);
	void RemoveNonActiveEdgeFromAet(list<EDGE>& aet, int y);
	void UpdateAndResortAet(list<EDGE>& aet);
	void FillAetScanLine(list<EDGE>& aet, int y, double r, double g, double b);

private:
	//the cut algorithm uses the following functions
	bool InnerSide(IntPoint start, IntPoint end, IntPoint point);
	vector<IntPoint> CutByOneSide(IntPoint start, IntPoint end, vector<IntPoint> points);
	IntPoint genIntersection(IntPoint start, IntPoint end, IntPoint p1, IntPoint p2);
};


#endif