//#pragma once
#pragma pack (push, 1)
typedef struct
{
	unsigned short signature;
	unsigned int filesize;
	unsigned short reserved1; //резервы
	unsigned short reserved2;
	unsigned int pixelArrOffset; //смещение
} BitmapFileHeader;


typedef struct
{
	unsigned int headerSize;
	unsigned int width;
	unsigned int height;
	unsigned short planes;
	unsigned short bitsPerPixel;
	unsigned int compression;
	unsigned int imageSize;
	unsigned int xPixelsPerMeter;
	unsigned int yPixelsPerMeter;
	unsigned int colorsInColorTable;
	unsigned int importantColorCount;
} BitmapInfoHeader;

typedef struct
{
	unsigned char b;
	unsigned char g;
	unsigned char r;
} Rgb;

void printFileHeader(BitmapFileHeader header);
void printInfoHeader(BitmapInfoHeader header);

Rgb** getArr(FILE* f,unsigned int H,unsigned int W);

void writeBMP(FILE* ff, unsigned int H, unsigned int W, Rgb** arr);
void printBMP(FILE* ff,BitmapFileHeader *bfh, BitmapInfoHeader *bih,Rgb **arr);