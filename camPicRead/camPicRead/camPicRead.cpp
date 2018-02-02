#include <iostream>
#include "opencv2/opencv.hpp"
#include <fstream>
#include <sstream>
#include<string>
#include <iomanip>
#include <cstdio>
using namespace std;
using namespace cv;
int readPics(const char *fileName, Mat &img, int width, int height);
void get_fName(char *txtname, char *imgname, int start, int end);
char* txtName[20] = {};
char* imgName[20] = {};

void hex2bin(unsigned char hex)
{
	//	int n = 0x50;
	int a[8];
	int i;
	for (i = 0; i != 8; ++i)
	{
		a[8 - 1 - i] = hex % 2;
		hex /= 2;
	}
	for (i = 0; i != 8; ++i)
	{
		cout <<  a[i];
	}
	cout << endl;

}
void readStr(string str, ofstream &ofs)
{
	unsigned char hex = 0;
	//string str = "1F";
	if (str[0] >= 'A'&&str[0] <= 'F') hex += ((str[0] - 'A' + 10) << 4);
	else hex += ((str[0] - '0') << 4);
	if (str[1] >= 'A'&&str[1] <= 'F') hex += ((str[1] - 'A' + 10));
	else hex += ((str[1] - '0'));
//	hex2bin(hex);
	int a[8];
	int i;
	for (i = 0; i != 8; ++i)
	{
		a[8 - 1 - i] = hex % 2;
		hex /= 2;
		ofs << a[8 - 1 - i];
	}
	
}
int main()
{
	ifstream ifs("loop/15.txt");
	ofstream ofs("out.txt");
	string inStr;
	int count = 0;
	while (ifs >> inStr)
	{
		readStr(inStr,ofs);
	//	cout << str << endl;
		count++;
	}

	ifs.close();
	ofs.close();
	cout << count << endl;
	Mat img;
	int result = readPics("out.txt", img, 120, 60);//160, 120);
	resize(img, img, Size(img.cols, img.rows));//(img.cols * 8, img.rows * 8));
	imshow("img", img);
	imwrite("img.jpg", img);
	waitKey();
	return 0;
}


int readPics(const char *fileName, Mat &img, int width, int height)
{
	FILE * fp;
	fp = fopen(fileName, "r");
	img = Mat::zeros(height, width, CV_8UC1);
	MatIterator_<uchar> it = img.begin<uchar>();
	int pixels = 0;
	do
	{
		char c = fgetc(fp);
		if (c != '0'&&c != '1')
			continue;
		if (c == '1')
			*it = 255;
		it++;
		pixels++;
	} while (!feof(fp));
	fclose(fp);
	return pixels;
}
void get_fName(char *txtname, char *imgname, int start,int end)
{
	for (int i = start; i <= end; i++) {
		sprintf(txtname, "%u.txt", i);
		sprintf(imgname, "%u.jpg", i);
	}
}
//stringstream sstream;
//sstream << "FF";
//unsigned char result;
//sstream >> result;
//cout << result;
//char buf[2500];
//int i=0;
//FILE *fp;
//fp = fopen("pic2.txt", "r");
//while (fscanf(fp, "%2x ", &buf[i]) != EOF) {
//	i++;
//	cout << buf[i] << endl;
//}
//void EightToOne(char Edge[][120], const int Length)
//{
//	int ByteCount = 0, LineCount = 0, ColumnCount = 0;
//	int TempImgByteCount = 0;
//	char BitCount = 0; double TempSUANZI = 0.50;
//	memset(TempImg, 0, 900);
//	for (ByteCount = 0; ByteCount < Length; ByteCount++)
//	{
//		if (ColumnCount == 120)//列记录
//		{
//			ColumnCount = 0;
//			LineCount++;
//		}
//		if (BitCount == 8)    //位记录
//		{
//			BitCount = 0;
//			TempImgByteCount++;//字节自加
//			if (TempImgByteCount == 900)
//				break;
//			TempSUANZI = 0.50;
//		}
//		TempImg[TempImgByteCount] = TempImg[TempImgByteCount] + Edge[LineCount][ColumnCount] * ((char)(TempSUANZI * 2));
//		TempSUANZI = TempSUANZI * 2;
//		ColumnCount++;
//		BitCount++;
//	}
//	return;
//}
