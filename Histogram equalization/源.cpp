#include<opencv2/opencv.hpp>
#include<iostream>
#include<cmath>

using namespace std;
using namespace cv;


int main()
{
	Mat srcMat = imread("E:\\6.jpg");
	Mat dstMat;

	if (srcMat.type() == CV_8UC1)
	{
		equalizeHist(srcMat, dstMat);
		
	}
	else if (srcMat.type() == CV_8UC3)
	{
		Mat channels[3];
		Mat singleMat[3];
		split(srcMat, channels);//三通道分离

		for (int i = 0; i < 3; i++)
		{
			equalizeHist(channels[i], singleMat[i]);
		}
		merge(singleMat, 3, dstMat);
	}

	imshow("原图", srcMat);
	imshow("直方图均衡", dstMat);

	waitKey(0);
	return 0;

}

