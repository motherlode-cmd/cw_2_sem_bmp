//#pragma once
#define uInt unsigned int

double in_line(int x, int y, uInt x1, uInt y1, uInt x2, uInt y2);

int getMax(double* arr, int k);

void lineBMP(Rgb temp,int k, uInt x1, uInt y1, uInt x2, uInt y2, Rgb** arr);

void lines(Rgb temp,int k,uInt x1, uInt y1, uInt x2, uInt y2, Rgb** arr);

/* {
	Rgb temp = {155, 0 ,0};
	if(x1 == x2) {
		for(int y = y1; y < y2; y++) {
			arr[y][x1] = temp;
		}
	} else if(y1 == y2) {
		for(int x = x1; x < x2; x++) {
			arr[y1][x] = temp;
		}
	} else {
		for(int x = x1; x < x2; x++) {
			for(int y = y1)
		}
	}
	return arr;
} */
