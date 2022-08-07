//#pragma once

Rgb** cutArr(Rgb** arr, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2);

void cutBMP(BitmapFileHeader *bfh, BitmapInfoHeader *bih, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, Rgb** arr) ;

int correctCut(unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2, BitmapInfoHeader *bih);

