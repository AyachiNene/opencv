/*
 *
 *
 *
 *
 *
 *
 */

#include "Header.h"

Mat img_bgr;

int main()
{
	uchar stdchar[PIC][DIR][PIXELS];
	ReadInFile(stdchar);

	Mat img = imread("01//41.png");
	img_bgr = img;
	Mat img_gray;
	ImageProcessing(img);
	threshold(img, img_gray, 128, 255, THRESH_BINARY_INV);

	vector<vector<Point>> contours;
	findContours(img_gray, contours, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	vector<Rect> rect = RectPushBack(contours, img);
	vector<Rect> dstrect = RectCombine(rect);
	sort(dstrect.begin(), dstrect.end(), pointascending);

	vector<META> metainfo = AddMetaInfo(dstrect);

	vector<Mat> dstMat = RectToMat(dstrect, img);
	vector<Mat> resizeMat = ResizeMat(dstMat);

	CharRecognize(resizeMat, stdchar, metainfo);
	//test(resizeMat, stdchar);
	waitKey(0);
	return 0;
}
