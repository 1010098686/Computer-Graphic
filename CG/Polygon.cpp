#include"stdafx.h"
#include"Polygon.h"
#include<GL/glut.h>


void MPolygon::construct(vector<IntPoint> points)
{
	point_list = points;
	for (int i = 0; i < line_list.size(); ++i)
	{
		Line* l = line_list[i];
		if (l != NULL) delete l;
	}
	line_list.clear();

	int size = points.size();
	for (int i = 0; i < size; ++i)
	{
		IntPoint p1 = points[i];
		IntPoint p2 = points[(i + 1) % size];
		Line* l = new Line(WindowWidth, WindowHeight, p1.x, p1.y, p2.x, p2.y);
		line_list.push_back(l);
	}
	needFill = false;
	
}

MPolygon::MPolygon(int width, int height, vector<IntPoint> v) :Shape(width,height)
{
	line_list = vector<Line*>();
	construct(v);
	selected = -1;
}

MPolygon::~MPolygon()
{
	int size = line_list.size();
	for (int i = 0; i < size; ++i)
	{
		Line* l = line_list.at(i);
		if (l != NULL){
			delete l;
		}
	}
}

void MPolygon::moveTo(int x, int y)
{
	for_each(line_list.begin(), line_list.end(), [x,y](Line* l){
		l->moveTo(x, y);
	});
	for_each(point_list.begin(), point_list.end(), [x, y](IntPoint& p){
		p.x += x;
		p.y += y;
	});
}

void MPolygon::rotate(int x, int y, int degree)
{
	for_each(line_list.begin(), line_list.end(), [x, y, degree](Line* l){
		l->rotate(x, y, degree);
	});
	double radian = degree*PI / 180;
	for_each(point_list.begin(), point_list.end(), [x, y, radian](IntPoint& p){
		int tx1 = cos(radian) *(p.x - x) - sin(radian)*(p.y - y) + x;
		int ty1 = sin(radian)*(p.x - x) + cos(radian)*(p.y - y) + y;

		p.x = tx1;
		p.y = ty1;
	});
	
}

void MPolygon::scale(double x, double y)
{
	for_each(line_list.begin(), line_list.end(), [x, y](Line* l){
		l->scale(x, y);
	});
	for_each(point_list.begin(), point_list.end(), [x, y](IntPoint& p){
		p.x *= x;
		p.y *= y;
	});
}

void MPolygon::FillShape(double r, double g, double b)
{
	needFill = true;
	nr = r;
	ng = g;
	nb = b;
}

void MPolygon::Draw()
{
	
	glPushMatrix();

	int size = line_list.size();
	for (int i = 0; i < size; ++i)
	{
		Line* l = line_list.at(i);
		l->SetColor(r, g, b);
		l->Draw();
	}
	if (needFill)
	{
		FillPolygon(nr, ng, nb);
	}
	glPopMatrix();
}


void MPolygon::FillPolygon(double r, double g, double b)
{
	int ymin = 10000;
	int ymax = 0;
	GetPolygonMinMax(ymin, ymax);

	vector<list<EDGE>> slNet = vector<list<EDGE>>(ymax-ymin+1);
	InitScanLineNewEdgeTable(slNet, ymin, ymax);
	HorizonEdgeFill(r, g, b);
	ProcessScanLineFill(slNet, ymin, ymax, r, g, b);
}

void MPolygon::GetPolygonMinMax(int& min, int& max)
{
	for_each(point_list.begin(), point_list.end(), [&max, &min](IntPoint p){
		if (p.y < min) min = p.y;
		if (p.y > max) max = p.y;
	});
}

void MPolygon::InitScanLineNewEdgeTable(vector<list<EDGE>>& slNet, int ymin, int ymax)
{
	EDGE e;
	int count = line_list.size();
	for (int i = 0; i < count; ++i)
	{
		const IntPoint& ps = point_list.at(i);
		const IntPoint& pe = point_list.at((i + 1) % count);
		const IntPoint& pss = point_list.at((i-1+count)%count);
		const IntPoint& pee = point_list.at((i + 2) % count);
		if (pe.y != ps.y)
		{
			e.dx = double(pe.x - ps.x) / double(pe.y - ps.y);
			if (pe.y>ps.y)
			{
				e.xi = ps.x;
				if (pee.y >= pe.y)
					e.ymax = pe.y - 1;
				else
					e.ymax = pe.y;
				slNet[ps.y - ymin].push_front(e);
			}
			else
			{
				e.xi = pe.x;
				if (pss.y >= ps.y)
					e.ymax = ps.y - 1;
				else
					e.ymax = ps.y;
				slNet[pe.y - ymin].push_front(e);
			}
		}
	}
}

void MPolygon::HorizonEdgeFill(double r, double g, double b)
{

}

void MPolygon::ProcessScanLineFill(vector<list<EDGE>>& slNet, int ymin, int ymax, double r, double g, double b)
{
	list<EDGE> aet = list<EDGE>();
	for (int y = ymin; y <= ymax; ++y)
	{
		InsertNetListToAet(slNet[y - ymin], aet);
		FillAetScanLine(aet, y, r, g, b);
		RemoveNonActiveEdgeFromAet(aet, y);
		UpdateAndResortAet(aet);
	}
}

void MPolygon::InsertNetListToAet(list<EDGE>& sl, list<EDGE>& aet)
{
	for_each(sl.begin(), sl.end(), [&aet](EDGE e){
		aet.push_back(e);
	});
	aet.sort([](EDGE& a, EDGE& b)->bool{
		return a.xi < b.xi;
	});
}

void MPolygon::RemoveNonActiveEdgeFromAet(list<EDGE>& aet, int y)
{
	aet.remove_if([y](EDGE a)->bool{return a.ymax == y; });
}

void MPolygon::UpdateAndResortAet(list<EDGE>& aet)
{
	for_each(aet.begin(), aet.end(), [](EDGE& a){a.xi += a.dx; });
	aet.sort([](EDGE& a, EDGE& b){
		return a.xi < b.xi;
	});
}

void MPolygon::FillAetScanLine(list<EDGE>& aet, int y, double r, double g, double b)
{
	list<EDGE>::iterator it;
	for (it = aet.begin(); it!= aet.end();)
	{
		int x1 = it->xi;
		it++;
		int x2 = it->xi;
		glColor3f(r, g, b);
		for (int i = x1; i < x2; ++i)
		{
			IdentityPoint p = translate(WindowWidth, WindowHeight, i, y);
			DrawPoints(p.x, p.y);
		}
		++it;
	}
}

void MPolygon::cut(int left, int top, int right, int buttom)
{
	vector<IntPoint> points = point_list;
	IntPoint vertex[] = { { left, top }, { right, top }, { right, buttom }, {left,buttom} };
	for (int i = 0; i < 4; ++i)
	{
		IntPoint start = vertex[i];
		IntPoint end = vertex[(i+1)%4];
		points = CutByOneSide(start, end, points);
	}
	construct(points);
}

bool MPolygon::InnerSide(IntPoint start, IntPoint end, IntPoint point)
{
	int v = (end.x - start.x)*(point.y - start.y) - (end.y - start.y)*(point.x - start.x);
	if (v <= 0) return true;
	else return false;
}

vector<IntPoint> MPolygon::CutByOneSide(IntPoint start, IntPoint end, vector<IntPoint> points)
{
	vector<IntPoint> res = vector<IntPoint>();
	int size = points.size();
	for (int i = 0; i < size;)
	{
		IntPoint p1 = points[i];
		IntPoint p2 = points[(i + 1) % size];
		bool f1 = InnerSide(start, end, p1);
		bool f2 = InnerSide(start, end, p2);
		if (f1 && f2)
		{
			res.push_back(p2);
		}
		else if (!f1 && !f2)
		{
			// generate none points
		}
		else
		{
			IntPoint intersection = genIntersection(start, end, p1, p2);
			if (!f1 && f2)
			{
				res.push_back(intersection);
				res.push_back(p2);
			}
			else if (f1 && !f2)
			{
				res.push_back(intersection);
			}
		}
		i += 1;
	}
	return res;
}

IntPoint MPolygon::genIntersection(IntPoint start, IntPoint end, IntPoint p1, IntPoint p2)
{
	if (start.x == end.x)
	{
		int dx = p2.x - p1.x;
		double u = double(start.x - p1.x) / dx;
		int y = p1.y + (p2.y - p1.y)*u;
		IntPoint res = { start.x, y };
		return res;
	}
	else if (start.y == end.y)
	{
		int dy = p2.y - p1.y;
		double u = double(start.y - p1.y) / dy;
		int x = p1.x + (p2.x - p1.x)*u;
		IntPoint res = { x, start.y };
		return res;
	}
	return{ 0, 0 };
}