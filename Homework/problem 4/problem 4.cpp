#include <stdio.h>
#include <stdlib.h>
#include "2_dimensin_figure.h"
#include <math.h>


int main()
{
	Point p1, p2, p3;
	Line s;
	Rect r;
	Circle c;
	double length, area;

	p1 = make_point(1, 1);
	p2 = make_point(3, 3);
	s = make_line(p1, p2);
	r = make_rect(p1, p2);
	length = line_length(s);
	area = rect_area(r);

	printf("line_length: %f, rect_area: %f\n", length, area);

}

Point make_point(float _x, float _y)
{
	Point p;
	p.x = _x;
	p.y = _y;

	return p;
}

Line make_line(Point _p1, Point _p2)
{
	Line line;
	line.p1 = _p1;
	line.p2 = _p2;

	return line;
}

//_p1과 _p2를 이은 선은 직사각형의 대각선이다
Rect make_rect(Point _p1, Point _p2)
{
	Rect r;
	r.p1 = _p1;
	r.p2 = _p2;

	return r;
}

double line_length(Line s)
{
	return sqrt(pow(s.p1.x - s.p2.x, 2) + pow(s.p1.y - s.p2.y, 2));
}

double rect_area(Rect r)
{
	return fabs(r.p1.x - r.p2.x) * fabs(r.p1.y - r.p2.y);
}