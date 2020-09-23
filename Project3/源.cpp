#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

int main()
{
	cv::Mat srcMat = imread("E:\\1.jpg");
	cv::Mat shallowMat;
	cv::Mat deepMat;
	shallowMat = srcMat;
	srcMat.copyTo(deepMat);
	int height = srcMat.rows;
	int width = srcMat.cols;
	uchar threshold = 100;
	for (int j = 0; j < height; j++)
	{
		for (int i = 0; i < width; i++)
		{
			uchar average = (srcMat.at<Vec3b>(j, i)[0] + srcMat.at<Vec3b>(j, i)[1] + srcMat.at<Vec3b>(j, i)[2]) / 3;
			if (average > threshold)
			{
				average = 255;
			}
			else
			{
				average = 0;
			}
			srcMat.at<Vec3b>(j, i)[0] = average;
			srcMat.at<Vec3b>(j, i)[1] = average;
			srcMat.at<Vec3b>(j, i)[2] = average;
		}
	}
	imshow("shallow", shallowMat);
	imshow("deep", deepMat);
	waitKey(0);
	return 0;
}