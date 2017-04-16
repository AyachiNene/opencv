#include "Header.h"


/*void PicLoad(const int arr[][PIXELS])
{
	Mat img_gray;
	Mat img;
	img = imread("pictest.png");
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_gray, 128, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(img_gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i != contours.size();i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		sort(contours.begin(), contours.end(), pointascending);
	}

	const int csize = 100;
	Mat srcROI[csize];
	Mat dstROI[csize];
	for (int i = 0; i != contours.size();i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		img(rect).copyTo(srcROI[i]);
		resize(srcROI[i], dstROI[i], Size(ROWS, COLS));
	}
	int k = 0;
	int scrarray[PIXELS];
	int find = 1;
	for (int i = 0; i != contours.size(); i++)
	{
		PerceptualHash(dstROI[i], scrarray);
		for (int j = 0; j < 10; j++)
		{
			find = MAX_DEVIATION;
			for (int m = 0; m < PIXELS; m++)
			{
				if (arr[j][m] != scrarray[m])
				{
					find--;
				}
			}
			if (find >= 0)
			{
				cout << (j + 1) % 10;
			}
		}
	}
}

void ImageProcessing(Mat &srcimg)
{
	Mat img_gray;
	cvtColor(srcimg, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_gray, 128, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(img_gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	for (int i = 0; i != contours.size();i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		sort(contours.begin(), contours.end(), pointascending);
	}

	const int csize = 100;
	Mat srcROI[csize];
	Mat dstROI[csize];
	for (int i = 0; i != contours.size();i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		srcimg(rect).copyTo(srcROI[i]);
		resize(srcROI[i], dstROI[i], Size(ROWS, COLS));
	}
}

int main(int argc, char *argv[])
{
	Mat img_gray;
	Mat img;
	img = imread("picij.png");
	//ImageProcessing(img);
	cvtColor(img, img_gray, COLOR_BGR2GRAY);
	threshold(img_gray, img_gray, 128, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(img_gray, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);


	/*for (int i = 0; i != contours.size();i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		rectangle(img, rect, Scalar(255, 0, 0));
		sort(contours.begin(), contours.end(), pointascending);
	}
	imshow("", img);
	//const int csize = 100;
	//Mat srcROI[csize];
	//Mat dstROI[csize];
	vector<Mat> srcROI;
	vector<Mat> dstROI;
	Rect edgerect[100];
	Mat tmpROI;
	for (int i = 0; i != contours.size();i++)
	{
		Rect rect = boundingRect(Mat(contours[i]));
		edgerect[i] = rect;
		//img(rect).copyTo(tmpROI);
		//srcROI.push_back(tmpROI);
	}
	for (int i = 0; i != contours.size();i++)
	{
		for (int j = 0; j != contours.size();j++)
		{
			if (i != j && edgerect[i].x + edgerect[i].width == edgerect[j].x + edgerect[j].width)
			{
				edgerect[i] = edgerect[i] | edgerect[j];
				edgerect[j] = edgerect[i];
			}
		}
	}
	for (int i = 0; i != contours.size();i++)
	{
		//Rect rect = boundingRect(Mat(contours[i]));
		rectangle(img, edgerect[i], Scalar(255, 0, 0));
		//sort(contours.begin(), contours.end(), pointascending);
	}
	for (int i = 0; i != contours.size();i++)
	{
		resize(srcROI[i], tmpROI, Size(ROWS, COLS));
		dstROI.push_back(tmpROI);
	}
	int c = 1;
	for (int i = 0; i != contours.size();i++)
	{
		char a[100];
		_itoa(c++, a, 10);
		imshow(a, srcROI[i]);
	}
	/*int arr[10][PIXELS];
	int k = 0;
	for (int i = 0; i != contours.size(); i++)
	{
		PerceptualHash(dstROI[i], arr[i]);		
	}
	//PicLoad(arr);
	//imshow("", dstROI[0]);
	//imshow("f**k!", img);
	waitKey(0);
}*/