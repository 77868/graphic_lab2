#include "MyRect.h"
#include <iostream>
#include <cmath>

MyRect::MyRect()
{
	cords[0][0] = 200;
	cords[0][1] = 200;
	cords[0][2] = 1;

	cords[1][0] = 200;
	cords[1][1] = 400;
	cords[1][2] = 1;

	cords[2][0] = 400;
	cords[2][1] = 400;
	cords[2][2] = 1;

	cords[3][0] = 400;
	cords[3][1] = 200;
	cords[3][2] = 1;

	polygons[0][0] = 0;
	polygons[0][1] = 1;
	polygons[0][2] = 3;

	polygons[1][0] = 1;
	polygons[1][1] = 2;
	polygons[1][2] = 3;
}

float MyRect::getMiddleX()// ��������� ���������� X �����, ������������ ������� ����������� �������� � ���������������
{
	float result = 0;
	for (size_t i = 0; i < 4; i++)
	{
		result += cords[i][0] * 0.25f;
	}
	return result;
}
float MyRect::getMiddleY()// ��������� ���������� Y �����, ������������ ������� ����������� �������� � ���������������
{
	float result = 0;
	for (size_t i = 0; i < 4; i++)
	{
		result += cords[i][1] * 0.25f;
	}
	return result;
}

void MyRect::move(float moveX, float moveY)
{
	float newCords[4][3] = { {0,0,0},{0,0,0},{0,0,0} };// ������� ��� ����� ���������
	float transformMatrix[3][3] = { {1,0,0},{0,1,0},{moveX,moveY,1} };// ������� �������������� ��� ����������� �������

	for (size_t i = 0; i < 4; i++)// ��������� ������� � ������������ �� ������� ��������������
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				newCords[i][j] += cords[i][k] * transformMatrix[k][j];
			}
		}
	}


	for (size_t i = 0; i < 4; i++) // ������� �������������� ������� � ������� ���������
	{
		for (size_t j = 0; j < 3; j++)
		{
			cords[i][j] = newCords[i][j];
		}
	}
}
void MyRect::rotate(float angle)
{
	float newCords[4][3]={{0,0,0},{0,0,0},{0,0,0}};// ������� ��� ����� ���������
	float transformMatrix[3][3] = { {cos(angle),sin(angle),0},{-sin(angle),cos(angle),0},{0,0,1}};// ������� �������������� ��� �������� �� ���� angle
	float midX = getMiddleX(), midY = getMiddleY();
	for (size_t i = 0; i < 4; i++)// ��������� ������ ������ � ������ ���������, ����� �������� ��������� ��������������
	{
		cords[i][0] -= midX;
		cords[i][1] -= midY;
	}
	
	for (size_t i = 0; i < 4; i++)// ��������� ������� � ������������ �� ������� ��������������
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				newCords[i][j] += cords[i][k] * transformMatrix[k][j];
			}
		}
	}

	

	for (size_t i = 0; i < 4; i++)// ������� �������������� ������� � ������� ���������
	{
		for (size_t j = 0; j < 3; j++)
		{
			cords[i][j] = newCords[i][j];
		}
	}
	
	for (size_t i = 0; i < 4; i++)// ���������� ������ � ��������� ������������
	{
		cords[i][0] += midX;
		cords[i][1] += midY;
	}
}
void MyRect::scale(float scale)
{
	float newCords[4][3] = { {0,0,0},{0,0,0},{0,0,0} };// ������� ��� ����� ���������
	float transformMatrix[3][3] = { {scale,0,0},{0,scale,0},{0,0,1} };// ������� �������������� ��� �������������� 

	float midX = getMiddleX(), midY = getMiddleY();// ��������� ������ ������ � ������ ���������, ����� �������� ��������� ��������������
	for (size_t i = 0; i < 4; i++)
	{
		cords[i][0] -= midX;
		cords[i][1] -= midY;
	}

	for (size_t i = 0; i < 4; i++)// ��������� ������� � ������������ �� ������� ��������������
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t k = 0; k < 3; k++)
			{
				newCords[i][j] += cords[i][k]*transformMatrix[k][j];
			}
		}
	}

	for (size_t i = 0; i < 4; i++)// ������� �������������� ������� � ������� ���������
	{
		for (size_t j = 0; j < 3; j++)
		{
			cords[i][j] = newCords[i][j];
		}
	}
	for (size_t i = 0; i < 4; i++)// ���������� ������ � ��������� ������������
	{
		cords[i][0] += midX;
		cords[i][1] += midY;
	}
}

void MyRect::fillTriangle(unsigned int* triangle,COLORREF color,HDC hdc)
{
	//���������� ������ �� Y ����������
	if (cords[triangle[0]][1] > cords[triangle[1]][1]) std::swap(triangle[0], triangle[1]);
	if (cords[triangle[1]][1] > cords[triangle[2]][1]) std::swap(triangle[1], triangle[2]);
	if (cords[triangle[0]][1] > cords[triangle[1]][1]) std::swap(triangle[0], triangle[1]);

	HPEN newPen= CreatePen(PS_SOLID, NULL, color);// �������� � ����� ����� ������������ �����
	HGDIOBJ prevPen = SelectObject(hdc, newPen);

	// ��������� ���� ������������
	MoveToEx(hdc, static_cast<int>(cords[triangle[0]][0]), static_cast<int>(cords[triangle[0]][1]), nullptr);
	LineTo(hdc, static_cast<int>(cords[triangle[1]][0]), static_cast<int>(cords[triangle[1]][1]));

	MoveToEx(hdc, static_cast<int>(cords[triangle[1]][0]), static_cast<int>(cords[triangle[1]][1]), nullptr);
	LineTo(hdc, static_cast<int>(cords[triangle[2]][0]), static_cast<int>(cords[triangle[2]][1]));

	MoveToEx(hdc, static_cast<int>(cords[triangle[2]][0]), static_cast<int>(cords[triangle[2]][1]), nullptr);
	LineTo(hdc, static_cast<int>(cords[triangle[0]][0]), static_cast<int>(cords[triangle[0]][1]));
	

	float x1, x2;
	// ����� ����� ������������ ��� X, ��������� ����� ������ ������������� ������� 0 1 � 0 2 
	for (int y = cords[triangle[0]][1]; y < cords[triangle[1]][1]; y++) {
		if ((cords[triangle[1]][1] - cords[triangle[0]][1]) < 1 || (cords[triangle[2]][1] - cords[triangle[0]][1]) < 1) {
			continue;
		}
		x1 = (((y - cords[triangle[0]][1]) * (cords[triangle[1]][0] - cords[triangle[0]][0])) / (cords[triangle[1]][1] - cords[triangle[0]][1])) + cords[triangle[0]][0];
		x2 = (((y - cords[triangle[0]][1]) * (cords[triangle[2]][0] - cords[triangle[0]][0])) / (cords[triangle[2]][1] - cords[triangle[0]][1])) + cords[triangle[0]][0];
		MoveToEx(hdc, static_cast<int>(round(x1)), y, NULL);
		LineTo(hdc, static_cast<int>(round(x2)), y);
	}
	// ����� ����� ������������ ��� X, ��������� ����� ������ ������������� ������� 1 2 � 0 2 
	for (int y = cords[triangle[1]][1]; y < cords[triangle[2]][1]; y++) {
		if ((cords[triangle[2]][1] - cords[triangle[1]][1]) == 0 || (cords[triangle[2]][1] - cords[triangle[0]][1]) == 0) {
			continue;
		}
		x1 = (((y - cords[triangle[1]][1]) * (cords[triangle[2]][0] - cords[triangle[1]][0])) / (cords[triangle[2]][1] - cords[triangle[1]][1])) + cords[triangle[1]][0];
		x2 = (((y - cords[triangle[0]][1]) * (cords[triangle[2]][0] - cords[triangle[0]][0])) / (cords[triangle[2]][1] - cords[triangle[0]][1])) + cords[triangle[0]][0];
		MoveToEx(hdc, static_cast<int>(round(x1)), y, NULL);
		LineTo(hdc, static_cast<int>(round(x2)), y);
	}
	SelectObject(hdc, prevPen);// ���������� ������ ����� � ������������ ������
	DeleteObject(newPen);
}



void MyRect::draw(HDC hdc,COLORREF color)
{
	for (size_t i = 0; i < 2; i++)//�������� ������������� ������������ ������
	{
		fillTriangle(polygons[i], color, hdc);
	}
}