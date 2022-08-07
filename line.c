#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "line.h"
#include <math.h>
#define uInt unsigned int 

double in_line(int x, int y, uInt x1, uInt y1, uInt x2, uInt y2) {
	return sqrt((x - x1)*(x - x1) + (y - y1)*(y - y1)) + sqrt((x - x2)*(x - x2) + (y - y2)*(y - y2)); 
}

void lineBMP(Rgb col_temp,int k, uInt x1, uInt y1, uInt x2, uInt y2, Rgb** arr) {
	int prex = x1;
	if(x1 == x2) {
		for(int y = y1; y < y2; y++) {
			for(int x = x1; x < k + x1; x++) {
				arr[y][x] = col_temp;
			}
		}
	} else if(y1 == y2) {
		for(int x = x1; x < x2; x++) {
			for(int y = y1; y < y1 + k; y++){
				arr[y][x] = col_temp;
			}
		}
	} else {
		lines(col_temp,k, x1, y1, x2, y2, arr);
	}
}

int getMax(double* arr, int k) {
	int ind = 0;
	for(int i = 0; i < k; i++) {
		if(arr[i] >= arr[ind]) {
			ind = i;
		}
	}
	return ind;
}

void lines(Rgb temp,int k,uInt x1, uInt y1, uInt x2, uInt y2, Rgb** arr){
	uInt ymin = y1, ymax = y2, xmin = x1, xmax = x2;
	if(x1 > x2) {
		xmin = x2;
		xmax = x1;
	}
	if(y1 > y2) {
		ymin = y2;
		ymax = y1;
	}
	ymin = 0;
	xmin = 0;
	ymax = 500;
	xmax = 500;
		double *mins = malloc(k * sizeof(double*));
		int *index = malloc(k * sizeof(int*));
	int counter = 0;
	for(int y = ymin; y < ymax; y++) {
		for(int i = 0; i < k; i++) {
			mins[i] = -1;
		}
		for(int x = xmin; x < xmax; x++) {
			double r = in_line(x,y,x1,y1,x2,y2);
			if(mins[counter] == -1 || counter < k){
				mins[counter] = r;
				index[counter++] = x;
			} else {//
				int i = getMax(mins, k);
				if(mins[i] >= r) {
					mins[i] = r;
					index[i] = x;
				}
			}//
		}
		//printf("y = %d \n", y);
		for(int i = 0; i < k; i++) {
			arr[y][index[i]] = temp;
			//printf("%d ", i);
		}
		counter = 0;
	}
	for(int x = xmin; x < xmax; x++) {
		for(int i = 0; i < k; i++) {
			mins[i] = -1;
		}
		for(int y = ymin; y < ymax; y++) {
			double r = in_line(x,y,x1,y1,x2,y2);
			if(mins[counter] == -1 || counter < k){
				mins[counter] = r;
				index[counter++] = y;
			} else {//
				int i = getMax(mins, k);
				if(mins[i] >= r) {
					mins[i] = r;
					index[i] = y;
				}
			}//
		}
		//printf("y = %d \n", y);
		for(int i = 0; i < k; i++) {
			arr[index[i]][x] = temp;
			//printf("%d ", i);
		}
		counter = 0;
	}
}