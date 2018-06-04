#pragma once
#include<iostream>
#include<math.h>
#include<cstring>
#include"Config.h"
using namespace std;
void Image::read_image()
{
	ifstream ifs;
	char buffer[10000];
	char *c;
	int i = 0, j, k;
	ifs.open("mona_lisa.ascii.pgm", ios_base::in);
	if (ifs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ifs.getline(buffer, 100, '\n');
	if(buffer[0] != 'P' || buffer[1] != '2')
	{
		cout << "Format error!!";
		ifs.close();
		return;
	}
	do
	{
		ifs.getline(buffer, 100, '\n');
	}while(buffer[0] == '#');
	width = strtol(buffer, &c, 10);
	height = atoi(c);
	ifs.getline(buffer, 100, '\n');
	graylevel = atoi(buffer);
	pixels = new int* [height];
	for(i = 0; i < height; ++i)	
		pixels[i] = new int[width];
	for(i = 0; i < height; ++i)
	{
		ifs.getline(buffer, 10000, '\n');
		c = &buffer[0];
		for(k = 0; k < width ; ++k)
		{
			pixels[i][k] = strtol(c, &c, 10);
		}
	}
	ifs.close();
}
void Image::write_image()
{
	ofstream ofs;
	int i, j;
	ofs.open("mona_lisa.ascii.pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs << "P2" << endl;
	ofs << "# mona_lisa.ascii.pgm" << endl;
	ofs << width << " " << height << endl;
	ofs << graylevel << endl;
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			ofs << getPixel(i,j) << " ";
		}
		ofs << endl;
	}
	ofs.close();
}

void Image::negative()
{
	int i, j;
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			pixels[i][j] = graylevel - pixels[i][j];
		}
	}
}
void Image::Log_Transformation()
{
	int i, j, c, n;
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			//n = 1 + pixels[i][j];
			c= 1;
			pixels[i][j] = c*(log(1 + pixels[i][j]));
		}
	}
}
void Image::setPixels(int **matrix)
{
	int i, j;
	for(i = 0; i < height; ++i)
		for(j = 0; j < width; ++j)
			pixels[i][j] = matrix[i][j];
}

void Delete(int **&ptr)			
{
	int i;
	for (i = 0; i < 3; ++i)
		delete[] ptr[i];
	delete ptr;
}

//void Negative::transform(Image pic)
//{
//	int i, j, width, height, graylevel;
//	graylevel = pic.getterGrayLevel();
//	width = pic.getterWidth();
//	height = pic.getterHeight();
//	int **matrix = pic.getterPixels();
//	for(i = 0; i < height; ++i)
//		for(j = 0; j < width; ++j)
//			matrix[i][j] = graylevel - matrix[i][j];
//}
