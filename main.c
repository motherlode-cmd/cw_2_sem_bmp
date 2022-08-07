#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>
#include "bmp.h"
#include "cut.h"
#include "Circle.h"
#include "line.h"
#include <math.h>
#include "triangle.h"
#include <string.h> 

void printHelp(){
printf("getopt example\n");
printf("-f <name.bmp> - имя выходного файла формата bmp\n");
printf("-i <name.bmp> - имя фходного файла формата bmp\n");
printf("-c <x1,y1,x2,y2> - инвертирует окружность, вписанную с квадрат с координатами нижекго левого угла x1 y1 и верхнего правого x2,y2\n");
printf("-c <r,x,y> - инвертирует цвета в окружность радиусом r и координатами центра x,y\n");
printf("-o <x1,y1,x2,y2> - Обрезает изображение x1y1 - координаты левого нижнего угла прямоугольника, x2y2 - верхнего правого\n");
printf("-l <r,g,b,k,x1,y1,x2,y2> - рисует орезок толщиной k, цветом rgb и соединяющий точки x1 y1 и x2 y2\n");
printf("-t <r,g,b,k,x1,y1,x2,y2,x3,y3> - рисует треугольник, не закрашенный, толщтна линий k, цвет линий rgb, координаты вершин - x1y1 и тд\n");
printf("-t <r1,g1,b1,r,g,b,k,x1,y1,x2,y2,x3,y3>- аналогичный треугольник, но закрашенный изнутри цветом r1 g1 b1 \n");
}

int is_white(Rgb temp) {
	if(temp.r == 255 && temp.g == 255 && temp.b == 255) {
		return 1;
	} else {
		return 0;
	}
}

int is_figure(int x, int y,int H, int W, Rgb** arr) {
	Rgb white_color = {0,0,0};
	if(x < W-1 && y < H-1 && x > 0 && y > 0) { //для не граничных точек
		if(1 == is_white(arr[y+1][x]) && 1 == is_white(arr[y+1][x + 1]) && 1 == is_white(arr[y+1][x-1]) && 1 == is_white(arr[y-1][x]) &&
			1 == is_white(arr[y-1][x-1]) && 1 == is_white(arr[y-1][x+1]) && 1 == is_white(arr[y][x]) && 1 == is_white(arr[y][x+1]) && 1 == is_white(arr[y][x-1])) {
			//printf("here");
			return 0;
		} else if(0 == is_white(arr[y+1][x]) || 0 == is_white(arr[y+1][x + 1]) || 0 == is_white(arr[y+1][x-1]) || 0 == is_white(arr[y-1][x]) ||
			0 == is_white(arr[y-1][x-1]) || 0 == is_white(arr[y-1][x+1]) || 0 == is_white(arr[y][x]) || 0 == is_white(arr[y][x+1]) || 0 == is_white(arr[y][x-1])){
			return 1;
		} else {
			return 0;
		}
	} else {
		return 0;
	}
}

void white_g(int H, int W ,Rgb color, Rgb** arr) {
	Rgb white_color = {0,0,0};
	int count = 0;
	int* dots_x = (int*)malloc(H*W*sizeof(int));
	int* dots_y = (int*)malloc(H*W*sizeof(int));
	for(int y = 0; y < H; y++) {
		for(int x = 0; x < W; x++) {
			if(is_white(arr[y][x])) {
				if(is_figure(x,y,H,W,arr) == 1) {
					//printf("%d ", count);
					dots_x[count] = x;
					dots_y[count] = y;
					count++;
					//arr[y][x] = color;
				}
			}
		}
	}
	for(int i = 0; i < count; i++) {
		arr[dots_y[i]][dots_x[i]] = color;
	}
}

int get_size(char* str) {
	int s = 0;
	for(int i = 0; i < strlen(str); i++) {
		if(str[i] == ',') {
			s++;
		}
	}
	return s+1;
}

int* get_all(char* str) {
	int size = get_size(str);
	int* all = (int*)malloc(size * sizeof(int));
	char* sep = ",";
	int i = 0;
	char* substr = strtok(str, sep);
	for(int i = 0; i < size; i++) {
		all[i] = atoi(substr);
		substr = strtok(NULL, sep);
	}
	return all;
}

char** get_file(char* str) {
	int size = get_size(str);
	char** all = (char**)malloc(size * sizeof(char*));
	char* sep = ",";
	int i = 0;
	char* substr = strtok(str, sep);
	for(int i = 0; i < size; i++) {
		all[i] = substr;
		substr = strtok(NULL, sep);
	}
	return all;
}

Rgb** cncat(BitmapFileHeader *bfh, BitmapInfoHeader *bih,BitmapFileHeader *bfh1, BitmapInfoHeader *bih1, Rgb** arr, Rgb** arr1) {
	Rgb temp = {0,0,0};
	int H = bih->height + bih1->height;
	int W = bih->width;
	Rgb** all_arr = (Rgb**)malloc(H * sizeof(Rgb*));
	for(int i = 0; i < H; i++) {
		all_arr[i] = (Rgb*)malloc(W * sizeof(Rgb));
	}
	for(int i = 0; i < bih->height; i++) {
		for(int j = 0; j < bih->width; j++) {
			all_arr[i][j] = arr[i][j];
		}
	}
	//printf("here");
	for(int i = bih->height; i < H; i++) {
		for(int j = 0; j < bih->width; j++) {
			if(j < bih1->width) {
				all_arr[i][j] = arr1[i - bih->height][j];
			} else {
				all_arr[i][j] = temp;
			}
		}
	}
	return all_arr;
	//arr = all_arr;
	//bih->height = H;
	//printf("\nhere %d  \n", H);
}

struct Configs{
	char* white;
	char* circle;
	char* cut;//-o обрезка
	char* line;
	char* triangle;
	char* infile;
	char* outfile; //-f
};

int main(int argc, char* argv[]){
	int read = 0;
	int write = 0;
	FILE* f;
	FILE* ff;
	Rgb** arr;
	BitmapFileHeader bfh;
	BitmapInfoHeader bih;
	struct Configs config = { NULL,NULL, NULL, NULL, NULL, NULL, NULL};
	char *opts = "s:w:c:o:l:t:i:f:h?";
	struct option longOpts[]={
		{"skl", 1, NULL, 's'},
		{"white", 1, NULL, 'w'},
		{"circle", 1, NULL, 'c'},
		{"cut", 1, NULL, 'o'},
		{"line", 1, NULL, 'l'},
		{"triangle", 1, NULL, 't'},
		{"infile", 1, NULL, 'i'},
		{"outfile", 1, NULL, 'f'},
		{"help", no_argument, NULL, 'h'},
		{ NULL, 0, NULL, 0}
	};
	int opt;
	int longIndex;
	opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	while(opt!=-1){
		switch(opt){
			case 'f':
				config.outfile = optarg;
				write++;
				break;
			case 'i':
				if ((f = fopen(optarg, "rb"))==NULL) {
				printf("[%s]", optarg);
				printf("Cannot open file.\n");
				exit(1);
				}
				fread(&bfh, 1, sizeof(BitmapFileHeader), f);
				fread(&bih, 1, sizeof(BitmapInfoHeader), f);
				printFileHeader(bfh);
				printInfoHeader(bih);
				unsigned int H = bih.height;
				unsigned int W = bih.width;
				arr = getArr(f, H, W);
				config.infile = optarg;
				read++;
				break;
			case 'h':
			case '?':
				printHelp();
				return 0;
				break;
			case 0:
				printf("->%s\n",longOpts[longIndex].name);

		}
		opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	}
	optind = 0;
    opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	while(opt!= -1){
		switch(opt){
			case 'w':
				int size = get_size(optarg);
				int* all = (int*)malloc(size * sizeof(int)); 
				all = get_all(optarg);
				if(read > 0) {
					if(size == 3) {
						Rgb color;
						color.r = all[0];
						color.g = all[1];
						color.b = all[2];
						white_g(bih.height, bih.width,color, arr);
					} else {
						printf("no arg");
					}
				}
				break;
			case 's':
				size = get_size(optarg);
				char** all_files = (char**)malloc(size * sizeof(char*));
				for(int i = 0; i < size; i++) {
					all_files[i] = (char*)malloc(sizeof(20 * sizeof(char)));
				}
				all_files = get_file(optarg);
				if(size == 1 && read != 0){
					FILE* f1;
					f1 = fopen(optarg, "rb");
					Rgb** arr1;
					BitmapFileHeader bfh1;
					BitmapInfoHeader bih1;
					fread(&bfh1, 1, sizeof(BitmapFileHeader), f1);
					fread(&bih1, 1, sizeof(BitmapInfoHeader), f1);
					printFileHeader(bfh1);
					printInfoHeader(bih1);
					arr1 = getArr(f1,bih1.height, bih1.width);
					//printf("\nhere\n");
					arr = cncat(&bfh, &bih, &bfh1, &bih1, arr, arr1);
					bih.height = bih.height + bih1.height;
					printf("\bdone cncat\n");
				} else {
					printf("wrong");
				}
			case 'c':
				size = get_size(optarg);
				all = get_all(optarg);
				if(read > 0) {
					config.circle = optarg;
					Circle circ;
					if(size == 3) {
						circ.r = all[0];
						circ.x = all[1];
						circ.y = all[2];
						circleArr(arr, circ, bih.width, bih.height);
					} else if(size == 4) {
						circ = getSqare(all[0], all[1], all[2], all[3]);
						circleArr(arr, circ, bih.width, bih.height);
					} else {
						printf("invalid circle");
					}	
				} 
				break;
			case 'o':
				size = get_size(optarg);
				all = get_all(optarg);
				if(read > 0) {
					if(size == 4) {
						if(all[0] < all[2] && all[1] < all[3] && all[0] >= 0 && all[1] >= 0 && all[2] <= bih.width && all[3] <= bih.height) {
							cutBMP(&bfh, &bih,all[0],all[1],all[2],all[3],arr);
						} else {
							printf("invalid dots");
						}
					} else {
						printf("invalid arg cut");
					}
				} 
				break;
			case 'l':
				size = get_size(optarg);
				all = get_all(optarg);
				if(read > 0) {
					if(size == 8) {
						uInt r = all[0]%256;
						uInt g = all[1]%256;
						uInt b = all[2]%256;
						Rgb color = {g,b,r};
						if(all[4] >= 0 && all[5] >= 0 && all[6] <= bih.width && all[7] <= bih.height){
							lineBMP(color, all[3], all[4], all[5], all[6], all[7], arr);
						} else {
							printf("bad line %d", size);
						}
					} else {
						printf("invalid arg line %d", size);
					}
				} 
				break;
			case 't':
				size = get_size(optarg);
				all = get_all(optarg);
				if(read > 0) { 
					if(size == 13) {
						uInt r1 = all[0]%256;
						uInt g1 = all[1]%256;
						uInt b1 = all[2]%256;
						Rgb color1 = {g1,b1,r1};
						uInt r2 = all[3]%256;
						uInt g2 = all[4]%256;
						uInt b2 = all[5]%256;
						Rgb color2 = {g2,b2,r2};
						zalit(color2, all[7], all[8], all[9], all[10], all[11], all[12], arr);
						triangle_no_c(color1, all[6], all[7], all[8], all[9], all[10], all[11], all[12], arr);
					} else if(size == 10){
						uInt r1 = all[0]%256;
						uInt g1 = all[1]%256;
						uInt b1 = all[2]%256;
						Rgb color1 = {g1,b1,r1};
						triangle_no_c(color1, all[3],all[4], all[5], all[6], all[7], all[8], all[9], arr);
					} else {
						printf("invalid arg triangle");
					}
				} 
				break;
		}
		opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
	}

	if(write != 0 && read != 0) {
		ff = fopen(config.outfile, "wb");
		printBMP(ff, &bfh, &bih, arr);
		printf("\nhere\n");
		fclose(ff);
	}
	return 0;
}
/*
	BitmapFileHeader bfh;
	BitmapInfoHeader bih;
	FILE* f = fopen("simpsonsvr.bmp", "rb");
	fread(&bfh, 1, sizeof(BitmapFileHeader), f);
	fread(&bih, 1, sizeof(BitmapInfoHeader), f);
	printFileHeader(bfh);
	printInfoHeader(bih);
	unsigned int H = bih.height;
	unsigned int W = bih.width;
	Rgb **arr = getArr(f, H, W);

	FILE *ff = fopen("out.bmp", "wb");
	Circle circ = { 100, 300, 300};
	Circle circ2 = { 100, 100, 100};
	//circleArr(arr, circ);
	//circleArr(arr, circ2);
	Rgb t = {0, 155, 155};
	cutBMP(&bfh, &bih,10,60,250,300,arr);
	//zalit(t,1,1,200,150,300,20,arr);
	//triangle_no_c(t,5, 0, 1, 200, 400, 300, 20, arr);
	printBMP(ff, &bfh, &bih, arr);
	fclose(ff);

	printf("\n");
	fclose(f);
	return 0;*/