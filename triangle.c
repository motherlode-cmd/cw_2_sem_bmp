#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "triangle.h"
#include "line.h"
#include "math.h"
#define uInt unsigned int 

void triangle_no_c(Rgb temp,int k, uInt x1, uInt y1, uInt x2, uInt y2, uInt x3, uInt y3, Rgb **arr){
	lineBMP(temp,k, x1, y1, x2, y2, arr);
	lineBMP(temp,k, x1, y1, x3, y3, arr);
	lineBMP(temp,k, x3, y3, x2, y2, arr);
}

int triangle_test(uInt x1, uInt y1, uInt x2, uInt y2, uInt x3, uInt y3, uInt x, uInt y) {
	int ABx = x2 - x1;
	int ABy = y2 - y1;
	int ACx = x3 - x1;
	int ACy = y3 - y1;
	int ADx = x - x1;
	int ADy = y - y1;
	if(abs(ABx * ADy - ADx * ABy) + abs(ACx * ADy - ACy * ADx) <= abs(ABx * ACy - ABy * ACx)) {
		return 1;
	} else {
		return 0;
	}
}
uInt max(uInt x1, uInt x2, uInt x3) {
	if(x1 > x2) {
		x2 = x1;
	} else {
		x1 = x2;
	}
	if(x3 > x1) {
		return x3;
	} else {
		return x1;
	}
}
uInt min(uInt x1, uInt x2, uInt x3) {
	if(x1 < x2) {
		x2 = x1;
	} else {
		x1 = x2;
	}
	if(x3 < x1) {
		return x3;
	} else {
		return x1;
	}
}
void zalit(Rgb temp,uInt x1, uInt y1, uInt x2, uInt y2, uInt x3, uInt y3, Rgb **arr){
	
	for(int y = min(y1,y2,y3); y <= max(y1,y2,y3); y++) {
		for(int x = min(x1,x2,x3); x <= max(x1,x2,x3); x++) {
			if(triangle_test(x1,y1,x2,y2,x3,y3,x,y) == 1 && triangle_test(x2,y2,x1,y1,x3,y3,x,y) == 1 && 
					triangle_test(x3,y3,x2,y2,x1,y1,x,y) == 1) {
				arr[y][x] = temp;
			}
		}
	}
}