//#pragma once
#define uInt unsigned int

typedef struct Circle
{
	int r;
	int x, y;
}Circle; 

Circle getSqare(uInt x1, uInt y1, uInt x2, uInt y2);

void circleArr(Rgb **arr, Circle circ, int W, int H);

Rgb invert(Rgb t);

int correctCircle(Circle circ, BitmapInfoHeader *bih);
