#pragma once
#include <iostream>
using namespace std;

class Matrix
{
	protected:
		int width;
		int height;
		int **pixels;
	public:
};
class Image : Matrix
{
	private:
		int graylevel;
	public:
		Image()
		{
			width = 0;
			height = 0;
			graylevel = 0;
		}
		~Image()
		{
			int i;
			for (i = 0; i < height; ++i)
				delete[] pixels[i];
			delete pixels;
		}
		void read_image();
		void write_image();
		void setPixels(int **matrix);
		void setPixel(int value, int x, int y)	{pixels[x][y] = value;}
		int getPixel(int x, int y)	{return this->pixels[x][y];}
		int getterWidth() {return width;}
		int getterHeight()	{return height;}
		int getterGrayLevel()	{return graylevel;}
		int **getterPixels()	{return pixels;}
};
class Filter : Matrix
{
	public:
		Filter()
		{
			width = 0;
			height = 0;
		}
		~Filter()
		{
			int i;
			for (i = 0; i < height; ++i)
				delete[] pixels[i];
			delete pixels;
		}
		void negative(Image &pic);
		void Log_Transformation(Image &pic, int c);
		void Histogram_equalization(Image &pic);
};

typedef struct node
{  int info ;
    struct node *next ;
};
typedef struct node *PTR;

const int so_item = 5;
const int dong =2;
const int cot = 2 ;
const int Up = 72;
const int Down = 80;
char thucdon [so_item][50] = {"1. Negative                 ",
			                  "2. Log Transformation       ",
			                  "3. Histogram Equalization   ",
			                  "4. Smoothing linear filter  ",
			                  "5. Laplacian filter         ",
			                 };

