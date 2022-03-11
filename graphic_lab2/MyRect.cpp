#include "MyRect.h"
#include <cmath>

MyRect::MyRect()
{
	cords[0].x = 10.0f;
	cords[1].x = 10.0f;
	cords[2].x = 120.0f;
	cords[3].x = 120.0f;

	cords[0].y = 10.0f;
	cords[1].y = 120.0f;
	cords[2].y = 120.0f;
	cords[3].y = 10.0f;
}
float MyRect::getMidleX()
{
	float result = 0;
	for (size_t i = 0; i < 4; i++)
	{
		result += cords[i].x * 0.25f;
	}
	return result;
}
float MyRect::getMidleY()
{
	float result = 0;
	for (size_t i = 0; i < 4; i++)
	{
		result += cords[i].y * 0.25f;
	}
	return result;
}
void MyRect::move(unsigned int direction, float moving)
{
	switch (direction)
	{
	case AXIS_X:
		for (size_t i = 0; i < 4; i++)
		{
			cords[i].x += moving;
		}
		break;
	case AXIS_Y:
		for (size_t i = 0; i < 4; i++)
		{
			cords[i].y += moving;
		}
		break;
	default:
		break;
	}
}
void MyRect::rotate(float angle)
{
	float midleX = getMidleX();
	float midleY = getMidleY();
	for (size_t i = 0; i < 4; i++)
	{
		float tmp = cords[i].x;
		cords[i].x = (cords[i].x - midleX) * cos(angle) - (cords[i].y - midleY) * sin(angle) + midleX;
		cords[i].y = (tmp - midleX) * sin(angle) + (cords[i].y -midleY) * cos(angle) + midleY;
	}
}
void MyRect::scale(float scale)
{
	float midleX = getMidleX();
	float midleY = getMidleY();
	for (size_t i = 0; i < 4; i++)
	{
		cords[i].x = (cords[i].x-midleX)* scale + midleX;
		cords[i].y = (cords[i].y - midleY) * scale + midleY;
	}
}
void MyRect::draw(HDC hdc,COLORREF color)
{
	//создание нового сплошного пера цвета color
	HPEN newPen = CreatePen(PS_SOLID, NULL, color);
	//выбор нового пера с сохранением старого
	HGDIOBJ prevPen = SelectObject(hdc, newPen);
	for (size_t i = 0; i < 3; i++)
	{
		MoveToEx(hdc, static_cast<int>(cords[i].x), static_cast<int>(cords[i].y), nullptr);
		LineTo(hdc, static_cast<int>(cords[i+1].x), static_cast<int>(cords[i+1].y));
		TextOut(hdc, static_cast<int>(cords[i].x), static_cast<int>(cords[i].y),names[i],2);
	}
	TextOut(hdc, static_cast<int>(cords[3].x), static_cast<int>(cords[3].y), names[3], 2);
	MoveToEx(hdc, static_cast<int>(cords[3].x), static_cast<int>(cords[3].y), nullptr);
	LineTo(hdc, static_cast<int>(cords[0].x), static_cast<int>(cords[0].y));
	//выбор старой кисти
	SelectObject(hdc, prevPen);
	//Освобождение памяти от новой кисте
	DeleteObject(newPen);
}