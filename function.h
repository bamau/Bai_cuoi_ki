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
void Image::read_image()
{
	ifstream ifs;
	char buffer[10000];
	char *c;
	int i, j;
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
	ofs.open("result.pgm", ios_base::out);
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

void Filter::negative(Image &pic)
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
	int i, j, k, width, height, graylevel;
	int soluong[graylevel];
	double number[graylevel];
	graylevel = pic.getterGrayLevel();
	width = pic.getterWidth();
	height = pic.getterHeight();
	int **matrix = pic.getterPixels();
	for(k = 0; k <= graylevel; k++)
	{
		int count = 0;
		for(i = 0; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				if(matrix[i][j] ==k)
					count++;
			}
				
		}
		soluong[k]=count;
		if(k==0)
		{
			number[k]=double (soluong[k])/(height*width);
		}
		if(k!=0)
		{
			number[k]=double (soluong[k])/(height*width);
			for(int x = k-1 ;x >= 0; x--)
			{
				number[x]=double (soluong[x])/(height*width);
				number[k]+=number[x];
			}
		}
		
	}
	for(k = 0; k <= graylevel; k++)
	{
		for(i = 0; i < height; ++i)
		{
			for(j = 0; j < width; ++j)
			{
				if(matrix[i][j]==k)
				{
					matrix[i][j]=Round(graylevel*number[k]);
				}
			}
				
		}
	}
}
void Delete(int **&ptr)			
{
	int i;
	for (i = 0; i < 3; ++i)
		delete[] ptr[i];
	delete ptr;
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
  system("cls");   int chon =0;
  int i; 
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
