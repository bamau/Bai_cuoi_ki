#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<iomanip>
#include"Config.h"
#include"function.h"
using namespace std;

int main()
{
	Image mau;
	Filter f;
	int number;
	mau.read_image();
	switch (MenuDong(thucdon))
	{
		case 1:
			{
				f.negative(mau);
				break;
			}
		case 2:
			{
				system("cls");
				cout<<"Input Number Transformation: ";
				cin>>number;
				f.Log_Transformation(mau,number);
				break;
			}
		case 3:
			{
				f.Histogram_equalization(mau);
				break;
			}
		case 4:
			{
				break;
			}
		case 5:
			{
				break;
			}
	}
	mau.write_image();
	system("cls");
	cout<<"Complete Filter.\n";
	return 0;
}

