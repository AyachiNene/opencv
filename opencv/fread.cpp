#include "Header.h"

using namespace cv;
using namespace std;



/*int main()
{
	uchar test[PIC][DIR][PIXELS];
	for (int i = 0; i < PIC; i++)
	{
		for (int j = 0; j < DIR; j++)
		{
			char a[100];
			sprintf(a, "%02d\\%d.png", j + 1, i + 1);
			Mat img = imread(a);
			Mat img1;
			resize(img, img1, Size(ROWS, COLS));
			cvtColor(img1, img1, CV_BGR2GRAY);
			threshold(img1, img1, 128, 255, THRESH_BINARY);
			PerceptualHash(img1, test[i][j]);
		}
	}
	OutToFile(test);
	for (int i = 0; i < PIC; i++)
	{
		for (int j = 0; j < DIR; j++)
		{
			for (int k = 0; k < COLS; k++)
			{
				for (int l = 0; l < ROWS; l++)
				{
					cout << (int)test[i][j][k*ROWS + l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}

	waitKey(0);
}*/