#pragma once
#include<iostream>
#include<math.h>
#include<cstring>
#include <conio.h>
#include <stdio.h>
#include <dos.h>
#include <string.h>
#include <windows.h>
#include <mylib.h>
#include <time.h>
#include"Config.h"
#define Round(a)  int(a+0.5)
using namespace std;

void Image::read_image(char* NameImage)
{
	ifstream ifs;
	char buffer[10000];
	char *c;
	int i, j;
	ifs.open(NameImage, ios_base::in);
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
		for(j = 0; j < width ; ++j)
		{
			pixels[i][j] = strtol(c, &c, 10);
		}
	}
	ifs.close();
}
void Image::write_image()
{
	ofstream ofs;
	int i, j;
	ofs.open("Result_Image.pgm", ios_base::out);
	if (ofs.fail()==true)
		cout<<"Failed to open this file"<<endl;
	ofs << "P2" << endl;
	ofs << "# result_image.pgm" << endl;
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

void Image::setPixels(int **matrix)
{
	int i, j;
	for(i = 0; i < height; ++i)
		for(j = 0; j < width; ++j)
			pixels[i][j] = matrix[i][j];
}

void Filter::Negative(Image &pic)
{
	int i, j, width, height, graylevel;
	graylevel = pic.getterGrayLevel();
	width = pic.getterWidth();
	height = pic.getterHeight();
	int **matrix = pic.getterPixels();
	for(i = 0; i < height; ++i)
		for(j = 0; j < width; ++j)
			matrix[i][j] = graylevel - matrix[i][j];
}
void Filter::Log_Transformation(Image &pic, int c)
{
	int i, j, width, height, graylevel;
	graylevel = pic.getterGrayLevel();
	width = pic.getterWidth();
	height = pic.getterHeight();
	int **matrix = pic.getterPixels();
	for(i = 0; i < height; ++i)
		for(j = 0; j < width; ++j)
			matrix[i][j] =c*Round(log(1 + matrix[i][j]));
}
void Filter::Histogram_equalization(Image &pic)
{
	int i, j, width, height, graylevel;
	graylevel = pic.getterGrayLevel();
	float count[graylevel]={0};
	width = pic.getterWidth();
	height = pic.getterHeight();
	int **matrix = pic.getterPixels();	
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{
			++count[matrix[i][j]];
		}
	}	
	for(i = 0; i<= graylevel;i++)
	{
		count[i]=float(count[i])/(height*width);
		if(i!=0)
		{
			count[i]+=count[i-1];
		}
	}			
	for(i = 0; i < height; ++i)
	{
		for(j = 0; j < width; ++j)
		{	
			matrix[i][j]=Round(graylevel*count[matrix[i][j]]);
		}	
	}
}

void Filter::Smoothing_Linear(Image &pic)
{
	int i, j, h, w, graylevel;
	graylevel = pic.getterGrayLevel();
	width = pic.getterWidth();
	height = pic.getterHeight();
	w=width+2;
	h=height+2;
	pixels = new int*[h];
	for(i = 0;i < h;i++) pixels[i]=new int[w];
	int **matrix = pic.getterPixels();
	for(i = 0; i < height; ++i)
	{
		j = 0;
		pixels[i+1][j] = 0;
		for(; j < width; ++j)
		{
			pixels[i+1][j+1] = matrix[i][j];
			if(i == 0)
				pixels[i][j+1] = 0;
			else if(i == height - 1)
				pixels[i+2][j+1] = matrix[i][j];
		}
		pixels[i+1][j+1] = 0;
	}
	pixels[0][0] = 0;
	pixels[0][w-1] = 0;		
	pixels[h-1][0] = 0;
	pixels[h-1][w-1] = 0;
	for(i = 1; i < h-1; ++i)
		for(j = 1; j < w-1; ++j)
			matrix[i-1][j-1] = (pixels[i][j] + pixels[i-1][j]+ 
								pixels[i+1][j] + pixels[i][j+1]+ 
								pixels[i][j-1] + pixels[i+1][j+1]+ 
								pixels[i-1][j+1] + pixels[i-1][j-1]+ 
								pixels[i+1][j-1])/9;
}
void Filter::Laplacian(Image &pic)
{
	int i, j, h, w, graylevel;
	graylevel = pic.getterGrayLevel();
	width = pic.getterWidth();
	height = pic.getterHeight();
	w=width+2;
	h=height+2;
	pixels = new int*[h];
	for(i = 0;i < h;i++) pixels[i]=new int[w];
	int **matrix = pic.getterPixels();
	for(i = 0; i < height; ++i)
	{
		j = 0;
		pixels[i+1][j] = matrix[i][j];
		for(; j < width; ++j)
		{
			pixels[i+1][j+1] = matrix[i][j];
			if(i == 0)
				pixels[i][j+1] = matrix[i][j];
			else if(i == height - 1)
				pixels[i+2][j+1] = matrix[i][j];
		}
		pixels[i+1][j+1] = matrix[i][j-1];
	}
	pixels[0][0] = matrix[0][0];
	pixels[0][w-1] = matrix[0][width-1];		
	pixels[h-1][0] = matrix[height-1][0];
	pixels[h-1][w-1] = matrix[height-1][width-1];
	for(i = 1; i < h-1; ++i)
	{
		for(j = 1; j < w-1; ++j)
		{
			matrix[i-1][j-1] = (pixels[i-1][j]+pixels[i+1][j]+ pixels[i][j+1]+pixels[i][j-1])-4*pixels[i][j];
			if(matrix[i-1][j-1] < 0)
				matrix[i-1][j-1] = pixels[i][j] - matrix[i-1][j-1];
			else
				matrix[i-1][j-1] += pixels[i][j];
		}
	}
}
void Normal () {
	SetColor(15);
	SetBGColor(0);
}
void HighLight () {
	SetColor(15);
	SetBGColor(1);
}
int MenuDong(char td [so_item][50]){
  Normal();
  system("cls");   
  cout<<"------------------------------------------------------IMAGE FILTER------------------------------------------------------";
  int chon =0; int i; 
  for ( i=0; i< so_item ; i++)
  { gotoxy(cot, dong +i);
    cout << td[i];
  }
  HighLight();
  gotoxy(cot,dong+chon);
  cout << td[chon];
  char kytu;
do {
  kytu = getch();
  if (kytu==0) kytu = getch();
  switch (kytu) {
    case Up :if (chon+1 >1)
  			  {
  		              	Normal();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon --;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case Down :if (chon+1 <so_item)
  			  {
  		        Normal();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
              	chon ++;
              	HighLight();
              	gotoxy(cot,dong+chon);
              	cout << td[chon];
  				
  			  }
  			  break;
  	case 13 : return chon+1;
  } 
  } while (1);
}
