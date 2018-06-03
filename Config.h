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
		void negative();
		void Log_Transformation();
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
};
class Negative : Filter
{
	public:
		void transform(Image);
};
