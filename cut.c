#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#define uInt unsigned int
Rgb** cutArr(Rgb** arr, uInt x1, uInt y1, uInt x2, uInt y2){
	Rgb **new_arr = malloc((y2 - y1)*sizeof(Rgb*));
	for(uInt i = 0; i < y2 - y1; i++) {
		new_arr[i] = malloc((x2 - x1) * sizeof(Rgb));
	}
	for(uInt y= y1; y< y2; y++){
		for(uInt x = x1; x < x2; x++) {
			new_arr[y - y1][x - x1] = arr[y][x];
		}
	}
	return new_arr;
}

int correctCut(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, BitmapInfoHeader *bih){
	return x2 < bih->height && y2 < bih->width && x1 > 0 && y1 > 0 && x1 < x2 && y1 < y2;
}

void cutBMP( BitmapFileHeader *bfh, BitmapInfoHeader *bih, uInt x1, uInt y1, uInt x2, uInt y2, Rgb** arr){
	arr = cutArr(arr, x1, y1, x2, y2);
	bih->height = y2-y1;
	bih->width = x2-x1;
}
