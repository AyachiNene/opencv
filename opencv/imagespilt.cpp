#include "Header.h"



vector<Mat> ResizeMat(vector<Mat> dstMat)
{
	vector<Mat> resizeMat;
	for (int i = 0; i != dstMat.size();i++)
	{
		Mat tempMat;
		resize(dstMat[i], tempMat, Size(ROWS, COLS));
		resizeMat.push_back(tempMat);
	}
	return resizeMat;
}

//为字符添加其他信息
vector<META> AddMetaInfo(vector<Rect> dstrect)
{
	vector<META> metainfo;
	struct maxrect maxrect = MaxRect(dstrect);
	for (decltype(dstrect.size())i = 0; i != dstrect.size(); i++)
	{
		META tempmeta;
		if (dstrect[i].height * 3 / 2 < maxrect.rectheight)
		{
			tempmeta.capital = false;
		}
		int j = (i > 0) ? (i - 1) : 0;//在进行i与i-1的比较时防止越界
		if (abs(dstrect[i].y - dstrect[j].y) > maxrect.rectheight)
		{
			tempmeta.space = -1;
		}
		else if (dstrect[i].x - dstrect[j].x > maxrect.rectwidth * 5 / 4)
		{
			tempmeta.space++;
		}
		metainfo.push_back(tempmeta);
	}
	return metainfo;
}

void HsvNormalize(Mat &img)
{
	for (int i = 0; i < img.rows; i++)
	{
		for (int j = 0; j < img.cols; j++)
		{
			//img.at<Vec3b>(i, j)[0] = 127;
			//img.at<Vec3b>(i, j)[1] *= 3;
			img.at<Vec3b>(i, j)[2] *= 2;
		}
	}
}

//注意：仅接受二值图像，适用于椒盐噪点
Mat ClearNoise(Mat &img)
{
	Mat temp(img);
	//以下用于调整边界值
	//Mat_<uchar>::iterator it = img.begin<uchar>();
	//Mat_<uchar>::iterator itend = img.end<uchar>();
	for (int i = 0; i < temp.rows; i++)
	{
		temp.at<uchar>(i, 0) = 255;
		temp.at<uchar>(i, temp.cols - 1) = 255;
	}
	for (int j = 0; j < temp.cols; j++)
	{
		temp.at<uchar>(0, j) = 255;
		temp.at<uchar>(temp.rows - 1, j) = 255;
	}

	for (int i = 0; i < temp.rows; i++)
	{
		for (int j = 0; j < temp.rows; j++)
		{

		}
	}
	return temp;
}



vector<Mat> RectToMat(vector<Rect> dstrect, Mat img)
{
	vector<Mat> dstMat;
	for (decltype(dstrect.size())i = 0; i != dstrect.size(); i++)
	{
		Mat tempmat;
		img(dstrect[i]).copyTo(tempmat);
		dstMat.push_back(tempmat);
	}
	return dstMat;
}

vector<Rect> RectCombine(vector<Rect> rect)
{
	struct maxrect macrect = MaxRect(rect);

	for (decltype(rect.size())i = 0; i != rect.size(); i++)
	{
		for (decltype(rect.size())j = 0; j != rect.size(); j++)
		{
			//以下为合并i，j判据
			bool widthjudge = abs(rect[i].x + rect[i].width - rect[j].x - rect[j].width) < macrect.rectwidth / 6;
			bool heightjudge = abs(rect[i].y - rect[j].y) < macrect.rectheight / 2;
			bool areajudge = ((rect[i].area() > 3 * rect[j].area()) || (rect[j].area() > 3 * rect[i].area()));
			if (i != j && widthjudge && heightjudge && areajudge)
			{
				rect[i] = rect[i] | rect[j];
				rect[j] = rect[i];//令两矩形均为合并后矩形，方便除去重复矩形
			}
		}
	}

	vector<Rect> dstrect;
	//此处除去重复矩形
	for (decltype(rect.size())i = 0; i != rect.size(); i++)
	{
		bool find = false;
		for (decltype(rect.size())j = 0; j != i; j++)
		{
			if (rect[i] == rect[j])
			{
				find = true;
			}
		}
		if (!find)
		{
			dstrect.push_back(rect[i]);
		}
	}
	return dstrect;
}

struct maxrect MaxRect(const vector<Rect> rect)
{
	struct maxrect maxrect;
	for (decltype(rect.size())i = 0; i != rect.size(); i++)
	{
		if (rect[i].height > maxrect.rectheight)
		{
			maxrect.rectheight = rect[i].height;
		}
		if (rect[i].width > maxrect.rectwidth)
		{
			maxrect.rectwidth = rect[i].width;
		}
	}
	return maxrect;
}
extern Mat img_bgr;
vector<Rect> RectPushBack(const vector<vector<Point>> contours, Mat img)
{
	vector<Rect> rect;
	Rect temprect;

	for (decltype(contours.size())i = 0; i != contours.size(); i++)
	{
		temprect = boundingRect(Mat(contours[i]));
		//rectangle(img_bgr, temprect, Scalar(255, 0, 0));
		rect.push_back(temprect);
	}
	//imshow("", img_bgr);
	return rect;
}

bool pointascending(const Rect &a, const Rect &b)
{
	if (abs(a.y - b.y) < max(a.width, b.width))
	{
		return a.x < b.x;
	}
	else
	{
		return a.y < b.y;
	}
}

void ReadInFile(uchar arr[][DIR][PIXELS])
{
	ifstream in("hashdata", ios::in | ios::binary);
	if (in.is_open())
	{
		for (int i = 0; i < PIC; i++)
		{
			for (int j = 0; j < DIR; j++)
			{
				for (int k = 0; k < COLS; k++)
				{
					for (int l = 0; l < ROWS; l++)
					{
						in.read((char *)&arr[i][j][k*ROWS + l], sizeof(uchar));
					}
				}
			}
		}
	}
}

void PerceptualHash(const Mat srcimg, uchar arr[])
{
	int count = PIXELS;
	for (int i = 0; i != srcimg.rows; i++)
	{
		for (int j = 0; j != srcimg.cols*srcimg.channels(); j += srcimg.channels())
		{
			arr[PIXELS - count] = srcimg.at<uchar>(i, j) == 0 ? 0 : 1;
			count--;
		}
	}
}

void OutToFile(uchar arr[][DIR][PIXELS])
{
	ofstream out("hashdata", ios::out | ios::trunc | ios::binary);
	if (out.is_open())
	{
		for (int i = 0; i < PIC; i++)
		{
			for (int j = 0; j < DIR; j++)
			{
				for (int k = 0; k < COLS; k++)
				{
					for (int l = 0; l < ROWS; l++)
					{
						out.write((char *)&arr[i][j][k*ROWS + l], sizeof(uchar));
					}
				}
			}
		}
	}
}

