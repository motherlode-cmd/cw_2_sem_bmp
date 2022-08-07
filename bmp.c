#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"

void printFileHeader(BitmapFileHeader header){
	printf("signature:\t%x (%hu)\n", header.signature, header.signature);
	printf("filesize:\t%x (%u)\n", header.filesize, header.filesize);
	printf("reserved1:\t%x (%hu)\n", header.reserved1, header.reserved1);
	printf("reserved2:\t%x (%hu)\n", header.reserved2, header.reserved2);
	printf("pixelArrOffset:\t%x (%u)\n", header.pixelArrOffset, header.pixelArrOffset);
}

void printInfoHeader(BitmapInfoHeader header){
	printf("headerSize:\t%x (%u)\n", header.headerSize, header.headerSize);
	printf("width:     \t%x (%u)\n", header.width, header.width);
	printf("height:    \t%x (%u)\n", header.height, header.height);
	printf("planes:    \t%x (%hu)\n", header.planes, header.planes);
	printf("bitsPerPixel:\t%x (%hu)\n", header.bitsPerPixel, header.bitsPerPixel);
	printf("compression:\t%x (%u)\n", header.compression, header.compression);
	printf("imageSize:\t%x (%u)\n", header.imageSize, header.imageSize);
	printf("xPixelsPerMeter:\t%x (%u)\n", header.xPixelsPerMeter, header.xPixelsPerMeter);
	printf("yPixelsPerMeter:\t%x (%u)\n", header.yPixelsPerMeter, header.yPixelsPerMeter);
	printf("colorsInColorTable:\t%x (%u)\n", header.colorsInColorTable, header.colorsInColorTable);
	printf("importantColorCount:\t%x (%u)\n", header.importantColorCount, header.importantColorCount);
}

Rgb** getArr(FILE* f,unsigned int H,unsigned int W) {
	Rgb **arr = (Rgb**)malloc(H*sizeof(Rgb*));
	for(int i=0; i<H; i++){
		arr[i] = (Rgb*) malloc(W * sizeof(Rgb)+ (W*3)%4);
		fread(arr[i],1,W * sizeof(Rgb) +(W*3)%4, f); 
	}
	return arr;
}

void writeBMP(FILE* ff, unsigned int H, unsigned int W, Rgb** arr){
	for(int i=0; i<H; i++){
		fwrite(arr[i],1,W * sizeof(Rgb) + (W*3)%4,ff);
	}
}

void printBMP(FILE* ff,BitmapFileHeader *bfh, BitmapInfoHeader *bih,Rgb **arr){
	fwrite(bfh, 1, sizeof(BitmapFileHeader),ff);
	fwrite(bih, 1, sizeof(BitmapInfoHeader),ff);
	writeBMP(ff, bih->height , bih->width, arr);
}
