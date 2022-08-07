//#pragma once
#define uInt unsigned int

void triangle_no_c(Rgb temp,int k, uInt x1, uInt y1, uInt x2, uInt y2, uInt x3, uInt y3, Rgb **arr); 
int triangle_test(uInt x1, uInt y1, uInt x2, uInt y2, uInt x3, uInt y3, uInt x, uInt y);
void zalit(Rgb temp,uInt x1, uInt y1, uInt x2, uInt y2, uInt x3, uInt y3, Rgb **arr);
uInt max(uInt x1, uInt x2, uInt x3);
uInt min(uInt x1, uInt x2, uInt x3);