#ifndef  HEADER_H
#define  HEADER_H

#include <opencv2\opencv.hpp>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>

#define ROWS 32
#define COLS 48
#define PIXELS ROWS*COLS
#define MAX_DEVIATION 350
#define DIR 10
#define PIC 62

#define _STDCHAR_LOOKUP

using namespace cv;
using namespace std;

//ȷ����ѡ����������͸�
struct maxrect
{
	int rectwidth = 0;
	int rectheight = 0;
};

//��¼������ص�������Ϣ
//Ҳ�����ǻᷢ��Ϊë��¼�ո���������ݲ���Ϊuint�أ�
//������Ϊ
//����Ҫ��space = -1�����У�����
typedef struct example
{
	int  space = 0;   //�ж����ַ���ո����
	bool capital = true; //�ж�����ĸ��Сд
}META;

//B���������д��ж��ַ���10��ģ��ȶ��ۺ��ж�
void CharRecognizeB(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS], vector<META> metainfo);

//A����������ģ��ȶ�
void CharRecognizeA(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS]);

//���ڲ��ԣ��Ͼ��൱���ۣ�
void test(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS]);

//�ַ�ʶ�𲿷�
void CharRecognize(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS], vector<META> metainfo);

//����һ�����򣬽�������ת��Ϊ�ַ�
char NumToChar(int result);

//�����������ֵԪ���±�
int  MaxIndex(int a[], int n);

//Ѱ����������СԪ���±�
int  MinIndex(int a[], int n);

//��֪��ϣ�㷨
void PerceptualHash(const Mat srcimg, uchar arr[]);

//������ļ�
void OutToFile(uchar arr[][DIR][PIXELS]);

//���������㷨
bool pointascending(const Rect &a, const Rect &b);

//���ļ�����
void ReadInFile(uchar arr[][DIR][PIXELS]);

//����ȷ�����ο�
vector<Rect> RectPushBack(const vector<vector<Point>> contours, Mat img);

//ȷ�������γ��Ⱥ͸߶�
struct maxrect MaxRect(vector<Rect> rect);

//���κϲ�
vector<Rect> RectCombine(vector<Rect> rect);

//�þ��ν�ȡͼ��
vector<Mat> RectToMat(vector<Rect> dstrect, Mat img);

//ͼ��Ԥ����
void ImageProcessing(Mat &img);

//ͼ���һ��
vector<Mat> ResizeMat(vector<Mat> dstMat);

//Ϊ�ַ����������Ϣ
vector<META> AddMetaInfo(vector<Rect> dstrect);

#endif