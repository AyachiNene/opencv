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

//确定所选矩形中最大宽和高
struct maxrect
{
	int rectwidth = 0;
	int rectheight = 0;
};

//记录文字相关的其他信息
//也许你们会发现为毛记录空格个数的数据不设为uint呢？
//那是因为
//劳资要拿space = -1来换行！！！
typedef struct example
{
	int  space = 0;   //判定此字符后空格个数
	bool capital = true; //判定此字母大小写
}META;

//B方案：进行待判定字符与10个模板比对综合判定
void CharRecognizeB(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS], vector<META> metainfo);

//A方案：像素模板比对
void CharRecognizeA(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS]);

//用于测试（毕竟相当蛋疼）
void test(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS]);

//字符识别部分
void CharRecognize(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS], vector<META> metainfo);

//按照一定规则，将结果标号转换为字符
char NumToChar(int result);

//返回数组最大值元素下标
int  MaxIndex(int a[], int n);

//寻找数组中最小元素下标
int  MinIndex(int a[], int n);

//感知哈希算法
void PerceptualHash(const Mat srcimg, uchar arr[]);

//输出至文件
void OutToFile(uchar arr[][DIR][PIXELS]);

//矩形排序算法
bool pointascending(const Rect &a, const Rect &b);

//从文件读入
void ReadInFile(uchar arr[][DIR][PIXELS]);

//初步确定矩形框
vector<Rect> RectPushBack(const vector<vector<Point>> contours, Mat img);

//确定最大矩形长度和高度
struct maxrect MaxRect(vector<Rect> rect);

//矩形合并
vector<Rect> RectCombine(vector<Rect> rect);

//用矩形截取图像
vector<Mat> RectToMat(vector<Rect> dstrect, Mat img);

//图像预处理
void ImageProcessing(Mat &img);

//图像归一化
vector<Mat> ResizeMat(vector<Mat> dstMat);

//为字符添加其他信息
vector<META> AddMetaInfo(vector<Rect> dstrect);

#endif