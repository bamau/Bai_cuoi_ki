#include<iostream>
#include<fstream>
#include<stdlib.h>
#include"Config.h"
#include"function.h"
using namespace std;

int main()
{
	Image image;
	Filter f;
	char *NameImage=new char[50];	
	int choice=MenuDong(thucdon);
	int number;
	NameImage={"mona_lisa.ascii.pgm"};
	image.read_image(NameImage);
	switch (choice)
	{
		case 1:
			{
				f.Negative(image);
				system("cls");
				cout<<"Complete Filter.\n";
				break;
			}
		case 2:
			{
				cout<<"Input Number Transformation: ";
				cin>>number;
				f.Log_Transformation(image,number);
				system("cls");
				cout<<"Complete Filter.\n";
				break;
			}
		case 3:
			{
				f.Histogram_equalization(image);
				system("cls");
				cout<<"Complete Filter.\n";
				break;
			}
		case 4:
			{
				f.Smoothing_Linear(image);
				system("cls");
				cout<<"Complete Filter.\n";
				break;
			}
		case 5:
			{
				f.Laplacian(image);
				system("cls");
				cout<<"Complete Filter.\n";
				break;
			}
		case 6:
			{
				system("cls");
				break;
			}
	}
	image.write_image();
	return 0;
}

