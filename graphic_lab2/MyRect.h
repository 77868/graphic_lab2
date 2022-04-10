#ifndef MYRECT_H
#define MYRECT_H

#include <Windows.h>

class MyRect
{
public:
	MyRect();
	void draw(HDC hdc,COLORREF color);
	void rotate(float angle);
	void scale(float scale);
	void move(float moveX, float moveY);
	float getMiddleX();
	float getMiddleY();
private:
	void fillTriangle(unsigned int* triangle, COLORREF color, HDC hdc);
	float cords[4][3];
	unsigned int polygons[2][3];
};

#endif 
