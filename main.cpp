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
	mau.read_image();
	mau.negative();
	mau.write_image();
	return 0;
}

