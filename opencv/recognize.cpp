#include "Header.h"

void test(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS])
{

#ifdef STDCHAR_LOOKUP

	for (int i = 0; i < PIC; i++)
	{
		for (int j = 0; j < DIR; j++)
		{
			for (int k = 0; k < COLS; k++)
			{
				for (int l = 0; l < ROWS; l++)
				{
					cout << (int)stdchar[i][j][k*ROWS + l] << " ";
				}
				cout << endl;
			}
			cout << endl;
		}
		cout << endl;
	}
#endif

}

void CharRecognize(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS], vector<META> metainfo)
{
	uchar scrarray[PIXELS];

	for (int i = 0; i != resizeMat.size(); i++)
	{
		int find[PIC] = { 0 };//此处设为数组可记录偏差信息,若为-1则跳过判定
		PerceptualHash(resizeMat[i], scrarray);
		for (int j = 0; j < PIC; j++)//针对一类图片的循环
		{
			for (int k = 0; k < DIR; k++)//针对10种字体的循环
			{
				for (int m = 0; m < PIXELS; m++)
				{
					if (stdchar[j][k][m] != scrarray[m])
					{
						find[j]++;
					}
				}
			}
		}
		if (!metainfo[i].capital)
		{
			for (int j = 0; j < 36; j++)
			{
				find[j] = INT_MAX;
			}
		}
		int result = MinIndex(find, PIC) + 1;
		char output = NumToChar(result);
		cout << output;
		int j = i + 1;//为什么要这样我也不知道
		if (metainfo[j].space == -1)
		{
			cout << endl;
		}
		else if (metainfo[j].space == 1)
		{
			cout << " ";
		}
	}
}

//B方案：进行待判定字符与10个模板比对综合判定
void CharRecognizeB(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS], vector<META> metainfo)
{
	uchar scrarray[PIXELS];

	for (int i = 0; i != resizeMat.size(); i++)
	{
		int find[PIC] = { 0 };//此处设为数组可记录偏差信息,若为-1则跳过判定
		PerceptualHash(resizeMat[i], scrarray);
		for (int j = 0; j < PIC; j++)//针对一类图片的循环
		{
			for (int k = 0; k < DIR; k++)//针对10种字体的循环
			{
				for (int m = 0; m < PIXELS; m++)
				{
					if (stdchar[j][k][m] != scrarray[m])
					{
						find[j]++;
					}
				}
			}
		}
		if (!metainfo[i].capital)
		{
			for (int j = 0; j < 36; j++)
			{
				find[j] = INT_MAX;
			}
		}
		int result = MinIndex(find, PIC) + 1;
		char output = NumToChar(result);
		cout << output;
		int j = i + 1;//为什么要这样我也不知道
		if (metainfo[j].space == -1)
		{
			cout << endl;
		}
		else if (metainfo[j].space == 1)
		{
			cout << " ";
		}
	}
}

//A方案：像素模板比对
void CharRecognizeA(vector<Mat> resizeMat, uchar stdchar[PIC][DIR][PIXELS])
{
	uchar scrarray[PIXELS];
	int find[DIR] = { 0 };//此处设为数组可记录偏差信息
	for (int i = 0; i != resizeMat.size(); i++)
	{
		int count[PIC] = { 0 };//记录符合的模板个数
		PerceptualHash(resizeMat[i], scrarray);
		for (int j = 0; j < PIC; j++)
		{
			for (int k = 0; k < DIR; k++)
			{
				find[k] = MAX_DEVIATION;
				for (int m = 0; m < PIXELS; m++)
				{
					if (stdchar[j][k][m] != scrarray[m])
					{
						find[k]--;
					}
				}
				if (find[k] > 0)
				{
					count[j]++;
				}
			}
		}
		int result = MaxIndex(count, PIC) + 1;
		char output = NumToChar(result);
		cout << output;
	}
}

char NumToChar(int result)
{
	char output;
	if (result > 0 && result <= 10)
	{
		output = result % 10 + '0';
	}
	else if (result > 10 && result <= 36)
	{
		output = result + 'A' - 11;
	}
	else if (result > 36 && result <= 62)
	{
		output = result + 'a' - 37;
	}
	else
	{
		output = '@';
	}
	return output;
}

//寻找数组中最大元素下标
int  MaxIndex(int a[], int n)
{
	int temp = a[0];
	int found;
	for (int i = 0; i < n; i++)
	{
		if (temp < a[i])
		{
			temp = a[i];
			found = i;
		}
	}
	return found;
}

//寻找数组中最小元素下标
int  MinIndex(int a[], int n)
{
	int temp = a[0];
	int found;
	for (int i = 0; i < n; i++)
	{
		if (temp > a[i])
		{
			temp = a[i];
			found = i;
		}
	}
	return found;
}