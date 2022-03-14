#ifndef MYRECT_H
#define MYRECT_H

#include <Windows.h>

#define AXIS_Y 0
#define AXIS_X 1

struct POINT_f
{
	float x, y;
};
class MyRect
{
public:
	MyRect();
	void draw(HDC hdc,COLORREF color);
	void rotate(float angle);
	void scale(float scale);
	void move(unsigned int direction, float speed);
	float getMidleX();
	float getMidleY();
private:
	POINT_f cords[4];
	wchar_t names[4][2] = { L"A",L"B",L"C",L"D" };
};

#endif 
