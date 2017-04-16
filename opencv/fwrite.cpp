#include "Header.h"




/*int main()
{
	//处理层
	Mat img = imread("piccomic.png");
	Mat img_gray;
	cvtColor(img, img_gray, CV_BGR2GRAY);
	threshold(img_gray, img_gray, 128, 255, THRESH_BINARY_INV);
	//切割层
	vector<vector<Point>> contours;
	findContours(img_gray, contours, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Rect> rect;
	Rect temprect;
	int matcount = contours.size();

	for (decltype(contours.size())i = 0; i != contours.size(); i++)
	{
		temprect = boundingRect(Mat(contours[i]));
		rect.push_back(temprect);
		//rectangle(img, rect[i], Scalar(255,0,0));
	}
	//寻找最大间距
	int rectwidth = 0;
	int rectheight = 0;
	for (decltype(contours.size())i = 0; i != contours.size(); i++)
	{
		if (rect[i].height > rectheight)
		{
			rectheight = rect[i].height;
		}
		if (rect[i].width > rectwidth)
		{
			rectwidth = rect[i].width;
		}
	}
	//合成层
	for (decltype(contours.size())i = 0; i != contours.size(); i++)
	{
		for (decltype(contours.size())j = 0; j != contours.size(); j++)
		{
			bool widthjudge = abs(rect[i].x + rect[i].width - rect[j].x - rect[j].width) < rectwidth / 6;
			bool heightjudge = abs(rect[i].y - rect[j].y) < rectheight / 4;
			bool areajudge = ((rect[i].area() > 10 * rect[j].area()) || (rect[j].area() > 10 * rect[i].area()));
			if (i != j && widthjudge && heightjudge && areajudge)
			{
				rect[i] = rect[i] | rect[j];
				rect[j] = rect[i];
			}
		}
	}
	
	vector<Rect> dstrect;
	for (decltype(contours.size())i = 0; i != contours.size(); i++)
	{
		bool find = false;
		for (decltype(contours.size())j = 0; j != i; j++)
		{
			if (rect[i] == rect[j])
			{
				find = true;
			}
		}
		if (!find)
		{
			dstrect.push_back(rect[i]);
			matcount--;
		}
	}
	sort(dstrect.begin(), dstrect.end(), pointascending);
	/*for (decltype(dstrect.size())i = 0; i != dstrect.size(); i++)
	{
		rectangle(img, rect[i], Scalar(255,0,0));
	}
	//分离层
	vector<Mat> dstMat;
	for (decltype(dstrect.size())i = 0; i != dstrect.size(); i++)
	{
		Mat tempmat;
		img(dstrect[i]).copyTo(tempmat);
		dstMat.push_back(tempmat);
	}


	int c = 1;
	for (int i = 0; i != dstMat.size();i++)
	{
		char a[100] = "";
		sprintf(a, "09\\%d.png", c++);
		imwrite(a, dstMat[i]);
	}
	//imshow("", img);
	waitKey(0);
	return 0;
}*/