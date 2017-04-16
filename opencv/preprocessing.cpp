#include "Header.h"

//以下进行滑条控制
int  g_scalevalue = 30;
int  g_Cvalue = 40;
Mat  tempimg;

void scalecallback(int, void*)
{
	Mat  temp;
	adaptiveThreshold(tempimg, temp, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 2 * g_scalevalue + 3, g_Cvalue);
	imshow("img", temp);
}

void Ccallback(int, void*)
{
	Mat  temp;
	adaptiveThreshold(tempimg, temp, 255, ADAPTIVE_THRESH_GAUSSIAN_C, THRESH_BINARY, 2 * g_scalevalue + 3, g_Cvalue);
	imshow("img", temp);
}

void ImageProcessing(Mat &img)
{
	//Mat dstimg;
	imshow("rgb", img);
	//cvtColor(img, dstimg, CV_BGR2GRAY);
	//cvtColor(img, img, CV_BGR2HSV);
	//HsvNormalize(img);
	//imshow("hsv", img);
	//cvtColor(img, img, CV_HSV2BGR);
	//imshow("rgb1", img);
	//GaussianBlur(img, img, Size(3, 3), 0);
	cvtColor(img, img, CV_BGR2GRAY);
	//imshow("gray1", img);
	//cvtColor(img, img, CV_BGR2GRAY);
	imshow("photocvt", img);
	/*namedWindow("img", WINDOW_NORMAL);
	img.copyTo(tempimg);
	imshow("photocv", tempimg);
	createTrackbar("scale", "img", &g_scalevalue, 100, scalecallback);
	createTrackbar("C", "img", &g_Cvalue, 300, Ccallback);
	scalecallback(g_scalevalue, 0);
	Ccallback(g_Cvalue, 0);*/
	//threshold(img, img, 128, 255, THRESH_OTSU | THRESH_BINARY);
	//img = ClearNoise(img);
	//threshold(dstimg, dstimg, 128, 255, THRESH_OTSU | THRESH_BINARY);
	adaptiveThreshold(img, img, 255, ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY, 2 * g_scalevalue + 3, g_Cvalue);
	imshow("pht", img);
	//imshow("phs", dstimg);
	/*Mat element = getStructuringElement(MORPH_CROSS, Size(1, 2));
	dilate(img, img, element);
	imshow("phs", img);
	erode(img, img, element);
	imshow("ph", img);*/
}