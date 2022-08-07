#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "Circle.h"
#define uInt unsigned int

Circle getSqare(uInt x1, uInt y1, uInt x2, uInt y2){
	Circle circ;
	circ.r = (x2-x1)/2;
	circ.x = (x2-x1)/2;
	circ.y = (y2-y1)/2;
	return circ;
}

int correctCircle(Circle circ, BitmapInfoHeader *bih) {
	uInt r = circ.r;
	return circ.x - r > 0 && circ.y - r > 0 && circ.x + r < bih->width && circ.y < bih->height;
}

Rgb invert(Rgb col) {
	Rgb temp = {255 - col.b, 255 - col.g, 255 - col.r};
	return temp;
}

void circleArr(Rgb **arr, Circle circ,int W,int H){
	//Rgb test = {257, 0, 0};
	int x1 = circ.x - circ.r;
	int y1 = circ.y - circ.r;
	int x2 = circ.x + circ.r;
	int y2 = circ.y + circ.r;
	//Rgb **arr  = arr;
	if(y2 >= H) {
		y2 = H;
	}
	if(x2 >= W) {
		x2 = W;
	}
	if(x1 <= 0) {
		x1 = 0;
	} 
	if(y1 <= 0) {
		y1 = 0;
	} 
	for(int y = y1; y < y2; y++) {
		for(int x = x1; x<x2; x++) {
			if( (circ.x - x)*(circ.x - x) + (circ.y - y)*(circ.y - y) <= circ.r*circ.r) {
				arr[y][x] = invert(arr[y][x]);
			}
		}
	}
}
